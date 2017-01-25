#include <iostream>
#include <vector>
#include "Network1D.h"

const double Lambda(1.);

void myRand(double &x)
{
	x = double(rand() - RAND_MAX / 2) / double(RAND_MAX / 2);
}

void myRand2D(Matrix2D<double> *x)
{
	x->apply(myRand);
}

void sigmoide(double &x)
{
	x = 1 / (1 + exp(-x*Lambda));
}
void sigmoide2D(Matrix2D<double> *x)
{
	x->apply(sigmoide);
}

void der_sigmoide(double &x)
{
	x = Lambda * exp(-x*Lambda) / std::pow((1 + exp(-x*Lambda)), 2);
}

void der_sigmoide2D(Matrix2D<double> *x)
{
	x->apply(der_sigmoide);
}

Network1D::Network1D()
{
}

Network1D::Network1D(MatrixCoord<unsigned int> layerSize) : m_neurons(unsigned int(layerSize.size())), m_activated(unsigned int(layerSize.size()-1)),m_weights(unsigned int(layerSize.size()-1)), m_bias(unsigned int(layerSize.size() - 1))
{
	for (unsigned int i = 0; i < m_neurons.length(); i++)
		m_neurons[i] = new Matrix2D<double>(layerSize[i], 1);
	for (unsigned int i = 0; i < m_activated.length(); i++)
		m_activated[i] = new Matrix2D<double>(layerSize[i+1], 1);
	for (unsigned int i = 0; i < m_bias.length(); i++)
		m_bias[i] = new Matrix2D<double>(layerSize[i+1], 1);
	for (unsigned int i = 0; i < m_weights.length(); i++)
		m_weights[i] = new Matrix2D<double>(m_bias[i]->n(), m_neurons[i]->n());

	m_weights.apply(myRand2D);
	m_bias.apply(myRand2D);
}

Matrix2D<double> Network1D::train(Matrix2D<double>* input, Matrix2D<double>* output)
{
	*m_neurons[0] = *input;
	*m_activated[0] = (*m_weights[0]) * (*m_neurons[0]) + (*m_bias[0]);

	for (unsigned int i = 1; i < m_activated.length(); i++)
	{
		*m_neurons[i] = *m_activated[i - 1];

		sigmoide2D(m_neurons[i]);

		*m_activated[i] = (*m_weights[i]) * (*m_neurons[i]) + (*m_bias[i]);
	}
	Matrix2D<double> activated(*m_activated.last());

	activated.apply(der_sigmoide);
	
	return hadamard(((*m_neurons.last()) - (*output)), activated);
}

void Network1D::corrError(Matrix2D<double> error)
{
	Matrix<Matrix2D<double>* > delta((unsigned int)m_weights.length()), activated(m_activated);

	activated.apply(der_sigmoide2D);

	delta.last() = new Matrix2D<double>(error);

	for (int i = (int)delta.length() - 2; i >= 0; i--)
		delta[i] = new Matrix2D<double>(hadamard(m_weights[i + 1]->transp()*(*delta[i + 1]), (*activated[i])));

	for (unsigned int i = 0; i < m_weights.length(); i++)
	{
		*m_weights[i] += -Lambda * (*delta[i]) * m_neurons[i]->transp();
		*m_bias[i] += -Lambda * (*delta[i]);
	}
}

Network1D Network1D::getSubNetwork(int i, int j)
{
	if (j == -1)
		j = (int)m_neurons.length()-1;

	if (i > j)
		throw std::exception("i>j in sub network");

	MatrixCoord<unsigned int> layerSize;

	layerSize.init(unsigned int(j - i) + 1);

	for (int k = i; k <= j; k++)
		layerSize[k - i] = (unsigned int)m_neurons[k]->length();

	Network1D sub(layerSize);

	for (int k = i; k < j; k++)
	{
		sub.m_activated[k - i] = m_activated[k];
		sub.m_bias[k - i] = m_bias[k];
		sub.m_weights[k - i] = m_weights[k];
		sub.m_neurons[k - i] = m_neurons[k];
	}

	sub.m_neurons[j - i] = m_neurons[j];

	return sub;
}

double Network1D::train(Matrix<Matrix2D<double>* > inputs, Matrix<Matrix2D<double>* > outputs)
{
	Matrix2D<double> error((unsigned int)outputs.first()->length(),1);

	for (unsigned int i = 0; i < inputs.length(); i++)
	{
		unsigned int index(rand() % inputs.length());
		error += train(inputs[index], outputs[index]);
	}
	
	error /= (double)inputs.length();

	double mean(0);

	for (unsigned int i = 0; i < error.length(); i++)
		mean += error[i];

	mean /= (double)error.length();

	corrError(error);

	return mean;
}

Matrix2D<double> Network1D::process(Matrix2D<double> *input)
{
	m_neurons[0] = input;
	*m_activated[0] = (*m_weights[0]) * (*m_neurons[0]) + (*m_bias[0]);

	for (unsigned int i = 1; i < m_activated.length(); i++)
	{
		m_neurons[i] = m_activated[i - 1];

		sigmoide2D(m_neurons[i]);

		*m_activated[i] = (*m_weights[i]) * (*m_neurons[i]) + (*m_bias[i]);
	}

	return *m_neurons.last();
}

Network1D::~Network1D()
{
	for (unsigned int i = 0; i < m_neurons.length(); i++)
		delete m_neurons[i];
	for (unsigned int i = 0; i < m_activated.length(); i++)
		delete m_activated[i];
	for (unsigned int i = 0; i < m_bias.length(); i++)
		delete m_bias[i];
	for (unsigned int i = 0; i < m_weights.length(); i++)
		delete m_weights[i];
}
