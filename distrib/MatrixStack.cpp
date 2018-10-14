#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
	Matrix4f init_matrix(0.0);
	init_matrix = init_matrix.identity();
	m_matrices.push_back(init_matrix);
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
	m_matrices.clear();
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack
	return m_matrices.at(m_matrices.size()-1);
}

void MatrixStack::push( const Matrix4f& m )
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
	m_matrices[m_matrices.size() - 1] = m_matrices.at(m_matrices.size() - 1)* m;
	m_matrices.insert(m_matrices.end() - 1, m);
}

void MatrixStack::pop()
{
	// Remove the top element from the stack
	Matrix4f temp1 = m_matrices.at(m_matrices.size() - 1);
	Matrix4f temp2 = m_matrices.at(m_matrices.size() - 2);
	m_matrices.pop_back();
	m_matrices.pop_back();
	m_matrices.push_back(temp1*(temp2.inverse()));
}
