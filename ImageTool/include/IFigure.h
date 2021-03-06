#pragma once
#include "../stdafx.h"

namespace Figure
{
	class IFigure
	{
	public:
		virtual void Draw(Gdiplus::Graphics* g) = 0;
		virtual void Drag(const unsigned int x, const unsigned int y) = 0;
		virtual void SetPoint(const unsigned int index, const int x, const int y) = 0;
		virtual bool IsInBound(const unsigned int x, const unsigned int y) = 0;
		virtual Gdiplus::Rect GetSize() const = 0;

	protected:
		Gdiplus::Point m_pointOfBegin;
		Gdiplus::Point m_pointOfEnd;
	};
}