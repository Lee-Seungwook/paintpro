#include "stdafx.h"
#include "IppFeature.h"
#include "IppFilter.h"

const double PI = 3.14159265358979323846;
const float PI_F = 3.14159265358979323846f;



FeatureAPI api;

// �ι���
void IppEdgeRoberts(IppByteImage& img, IppByteImage& imgEdge)
{
	api.APIEdgeRoberts(img, imgEdge);
}

// ������
void IppEdgePrewitt(IppByteImage& img, IppByteImage& imgEdge)
{
	api.APIEdgePrewitt(img, imgEdge);
}

// �Һ�
void IppEdgeSobel(IppByteImage& img, IppByteImage& imgEdge)
{
	api.APIEdgeSobel(img, imgEdge);
}

// ĳ��
// igmSrc�� �Է� ����, imgEdge�� ����� ����� ����, sigam�� ����þ� ���͸����� ����� ǥ�� ���� ��, th _low * th_high�� �����׸��ý� ���� Ʈ��ŷ���� ����� �Ӱ谪
// �����׸��ý� ���� Ʈ��ŷ�� ���� ������ �˻��Ͽ� �������� �ƴ����� �Ǵ��ϴ� ���
void IppEdgeCanny(IppByteImage& imgSrc, IppByteImage& imgEdge, float sigma, float th_low, float th_high)
{
	api.APIEdgeCanny(imgSrc, imgEdge, sigma, th_low, th_high);
}

// ���� ��ȯ�� �̿��Ͽ� ���� ���� (img�� �Է� ����, lines�� ����� ���� ���е��� ������ ������ �����̳�, 
// threshold�� ���� �������� �Ǵ��ϱ� ���� �Ӱ谪, ���� �迭�� ������ ���� threshold ������ ũ�� �������� ����
void IppHoughLine(IppByteImage& img, std::vector<APILineParam>& lines, int threshold)
{
	
	api.APIHoughLine(img, lines, threshold);
}

// ���� �׸��� ���� �Լ�
// ������ ���� ��ǥ�� �� ��ǥ�� ����Ͽ� line ������ C�� ��� ���� �̿��Ͽ� ������ �׸���.
void IppDrawLine(IppByteImage& img, APILineParam line, BYTE c)
{
	api.APIDrawLine(img, line, c);
}

// x��ǥ�� 0�� ���� w - 1�� ��쿡 ���Ͽ� y��ǥ�� ���� ���(��Ʈ�� ù��° ��ǥ���� ������ ��ǥ���� �׷��̽����� �� c�� �̿��Ͽ� ������ �׸�
void IppDrawLine(IppByteImage& img, int x1, int y1, int x2, int y2, BYTE c)
{
	api.APIDrawLine(img, x1, y1, x2, y2, c);
}

// �ظ��� �ڳ� ���� ����
// img�� �Է� ����, corners�� ����� �ڳ� ����Ʈ ����, th�� �ظ��� �ڳ� ���� �Լ����� �ڳ� ���θ� ������ �� ����� �Ӱ谪
void IppHarrisCorner(IppByteImage& img, std::vector<APIPoint>& corners, double th)
{
	api.APIHarrisCorner(img, corners, th);
}
		
