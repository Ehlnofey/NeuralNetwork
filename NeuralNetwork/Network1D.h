#pragma once

#include "Matrix2D.h"
#include "Matrix.h"
#include "MatrixCoord.h"

class Network1D
{
public:
	Network1D();
	Network1D(MatrixCoord<unsigned int> layerSize);
	Matrix2D<double> train(Matrix2D<double>* input, Matrix2D<double>* output);
	double train(Matrix<Matrix2D<double>* > inputs, Matrix<Matrix2D<double>* > outputs);
	Matrix2D<double> process(Matrix2D<double> *input);
	void corrError(Matrix2D<double> error);
	Network1D getSubNetwork(int i, int j=-1);
	~Network1D();

private:
	Matrix<Matrix2D<double>* > m_neurons,m_activated,m_weights,m_bias;
};

