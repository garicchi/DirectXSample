#include "pch.h";
#include "DrawableText.h"

using namespace TestDirectX;

DrawableText::DrawableText(wstring text, D2D1_POINT_2F position, float fontSize, ColorF color, WCHAR* fontName, shared_ptr<DeviceResources> deviceResources) 
:m_text(text),m_position(position),m_color(color),m_fontSize(fontSize),m_fontName(fontName), m_deviceResources(deviceResources){
	
}


void DrawableText::CreateResources(){
	

	//�e�L�X�g�g�p����u���V���m�ۂ��܂�
	m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(m_color, &m_textBrush);

	//�e�L�X�g�Ɏg�p����t�H�[�}�b�g���m�ۂ��܂�
	m_deviceResources->GetDWriteFactory()->CreateTextFormat(
	    m_fontName,
		nullptr,
		DWRITE_FONT_WEIGHT_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,

		m_fontSize,
		L"ja-JP",
		&m_textFormat
		);
	m_deviceResources->GetDWriteFactory()->CreateTextLayout(
		m_text.c_str(),
		(uint32) m_text.length(),
		m_textFormat.Get(),
		240.0f, // ���̓e�L�X�g�̍ő啝�B
		50.0f, // ���̓e�L�X�g�̍ő卂���B
		&m_textLayout

		);
}

void DrawableText::RelearseResources(){
	m_textBrush.Reset();
	m_textFormat.Reset();
	m_textLayout.Reset();
}