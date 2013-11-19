#include "Cube.h"

const unsigned CubeNumTriangles = 12;

const unsigned CubeNumVertices = 8;

const float CubeVertices[][3] = {
	{-1.0f,-1.0f,-1.0f},
	{-1.0f, 1.0f,-1.0f},
	{ 1.0f, 1.0f,-1.0f},
	{ 1.0f,-1.0f,-1.0f},
	{-1.0f,-1.0f, 1.0f},
	{ 1.0f,-1.0f, 1.0f},
	{ 1.0f, 1.0f, 1.0f},
	{-1.0f, 1.0f, 1.0f}};

const float CubeTextureCoordinates[][2] = {
	{0.0f,1.0f},
	{0.0f,0.0f},
	{1.0f,0.0f},
	{1.0f,1.0f},
	{0.0f,0.0f},
	{0.0f,1.0f},
	{0.0f,0.0f},
	{0.0f,1.0f}};

const unsigned CubeIndices[] = {
	0,1,2, 2,3,0, 4,5,6,
	6,7,4, 0,3,5, 5,4,0,
	3,2,6, 6,5,3, 2,1,7,
	7,6,2, 1,0,4, 4,7,1};

const float CubeDefaultColours[][4] = {
	{1.0f,0.0f,0.0f,1.0f},
	{0.0f,1.0f,0.0f,1.0f},
	{0.0f,0.0f,1.0f,1.0f},
	{1.0f,1.0f,1.0f,1.0f},
	{0.0f,0.0f,1.0f,1.0f},
	{0.0f,1.0f,0.0f,1.0f},
	{1.0f,0.0f,0.0f,1.0f},
	{1.0f,1.0f,1.0f,1.0f}};
