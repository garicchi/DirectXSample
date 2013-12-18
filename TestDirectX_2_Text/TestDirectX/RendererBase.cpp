#include "pch.h"
#include "RendererBase.h"
#include "Common/DirectXHelper.h"

using namespace TestDirectX;
using namespace D2D1;

//レンダラークラスのコンストラクタ 変数の初期化やリソースの確保などをします
RendererBase::RendererBase(const std::shared_ptr<DeviceResources>& deviceResources) :
m_deviceResources(deviceResources)
{
	m_text=L"I'm Love in it.";

	//リソース確保
	CreateDeviceDependentResources();
}

//更新処理です　定期的に呼ばれるので変数の制御などはここでおこないます
void RendererBase::Update(DX::StepTimer const& timer)
{
	m_deviceResources->GetDWriteFactory()->CreateTextLayout(
		m_text.c_str(),
		(uint32) m_text.length(),
		m_textFormat.Get(),
		240.0f, // 入力テキストの最大幅。
		50.0f, // 入力テキストの最大高さ。
		&m_textLayout
		
		);
}

// フレームを画面に描画します。
void RendererBase::Render()
{
	//デバイスコンテキストの確保
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();
	
	context->BeginDraw(); //描画開始

	context->DrawTextLayout(Point2F(100.0f,100.0f),
		m_textLayout.Get(),m_textBrush.Get());

	
	context->EndDraw();	//描画終了
	
}

//リソースを確保するメソッドです コンストラクタからだけでなく、Mainクラスからも呼ばれます
void RendererBase::CreateDeviceDependentResources()
{
	//テキスト使用するブラシを確保します
	m_deviceResources->GetD2DDeviceContext()->CreateSolidColorBrush(ColorF(ColorF::White), &m_textBrush);

	//テキストに使用するフォーマットを確保します
	m_deviceResources->GetDWriteFactory()->CreateTextFormat(
		L"Segoe UI",
		nullptr,
		DWRITE_FONT_WEIGHT_LIGHT,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		32.0f,
		L"en-US",
		&m_textFormat
		);

}

//リソースを解放するメソッドです Mainクラスから呼ばれます
void RendererBase::ReleaseDeviceDependentResources()
{
	m_textBrush.Reset();
	m_textLayout.Reset();
	m_textFormat.Reset();
}