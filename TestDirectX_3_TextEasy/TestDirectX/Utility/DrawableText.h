#pragma once

#include "DeviceResources.h"
#include <string>

using namespace std;
using namespace D2D1;
using namespace Microsoft::WRL;

namespace TestDirectX{
	class DrawableText{
	public:
		DrawableText(wstring text, D2D1_POINT_2F position, float fontSize, ColorF color, WCHAR* font, shared_ptr<DeviceResources> deviceResources);
		void CreateResources();
		void RelearseResources();

		ComPtr<ID2D1SolidColorBrush> m_textBrush;
		ComPtr<IDWriteTextLayout> m_textLayout;
		ComPtr<IDWriteTextFormat> m_textFormat;
		D2D1_POINT_2F m_position;

		wstring m_text;

	private:
		shared_ptr<DeviceResources> m_deviceResources;
		ColorF m_color;
		float m_fontSize;
		WCHAR* m_fontName;
	};
}