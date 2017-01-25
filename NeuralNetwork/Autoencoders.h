#pragma once
#include <vector>
#include "Network1D.h"

class Autoencoders
{
public:
	Autoencoders(Matrix<Matrix2D<double>* > & database, MatrixCoord<unsigned int> &layerSize);
	void minimizeError(double threshold=0.1,bool printError=false);
	void extract();
	void rebuild();
	Matrix2D<double> getDream(Matrix2D<double> *data);
	Matrix2D<double> getAleaDream();
	~Autoencoders();

private:
	Network1D m_network;

	Matrix<Matrix2D<double>* > m_database;
	
	Network1D m_extractedNetwork;
	
	MatrixCoord<unsigned int> m_layerSize;
};

