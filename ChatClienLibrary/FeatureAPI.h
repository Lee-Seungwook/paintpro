#pragma once

#include "..\ImageTool\IppImage\IppImage.h"

#include "..\ImageTool\stdafx.h"
#include <vector>

#ifdef _DLL_FEATURE_
#define DLL_FEATURE _declspec(dllexport)
#else		FEATURE
#define DLL_FEATURE __declspec(dllimport)
#endif // _DLL_FEATURE_

class APILineParam
{
public:
	double rho;
	double ang;
	int vote; // ������ �迭���� ������ ���� ����

public:
	APILineParam() : rho(0), ang(0), vote(0) {}
	APILineParam(double r, double a, int v) : rho(r), ang(a), vote(v) {}
};

inline bool operator< (const APILineParam& lhs, const APILineParam& rhs) // ������ ������(���� �迭�� ���� ���ϱ� ���ؼ�)
{
	return lhs.vote > rhs.vote;
}

class APIPoint
{
public:
	int x;
	int y;

public:
	APIPoint() : x(0), y(0) {}
	APIPoint(int _x, int _y) : x(_x), y(_y) {}
};

class DLL_FEATURE FeatureAPI
{
public:
	void APIEdgeRoberts(IppByteImage& img, IppByteImage& imgEdge);
	void APIEdgePrewitt(IppByteImage& img, IppByteImage& imgEdge);
	void APIEdgeSobel(IppByteImage& img, IppByteImage& imgEdge);
	void APIEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high);
		 
	void APIHoughLine(IppByteImage& img, std::vector<APILineParam>& lines, int threshold = 60);
	void APIDrawLine(IppByteImage& img, APILineParam line, BYTE c);
	void APIDrawLine(IppByteImage& img, int x1, int y1, int x2, int y2, BYTE c);
		 
	void APIHarrisCorner(IppByteImage& img, std::vector<APIPoint>& corners, double th);
};