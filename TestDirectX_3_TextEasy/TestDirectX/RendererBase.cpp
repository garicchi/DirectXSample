#include "pch.h"
#include "RendererBase.h"
#include "Common/DirectXHelper.h"

using namespace TestDirectX;
using namespace D2D1;

//レンダラークラスのコンストラクタ 変数の初期化やリソースの確保などをします
RendererBase::RendererBase(const std::shared_ptr<DeviceResources>& deviceResources) :
m_deviceResources(deviceResources)
{
	m_drawableText = new DrawableText(L"さむい", Point2F(100.0f, 100.0f), 60.0f, ColorF(ColorF::DarkOrange), L"segoe UI", m_deviceResources);
	//リソース確保
	CreateDeviceDependentResources();
}

//更新処理です　定期的に呼ばれるので変数の制御などはここでおこないます
void RendererBase::Update(DX::StepTimer const& timer)
{
	m_drawableText->m_position = Point2F(++m_drawableText->m_position.x,0);
}

// フレームを画面に描画します。
void RendererBase::Render()
{
	//デバイスコンテキストの確保
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();
	
	context->BeginDraw(); //描画開始

	context->DrawTextLayout(m_drawableText->m_position,
		m_drawableText->m_textLayout.Get(),m_drawableText->m_textBrush.Get());
	
	context->EndDraw();	//描画終了
	
}

//リソースを確保するメソッドです コンストラクタからだけでなく、Mainクラスからも呼ばれます
void RendererBase::CreateDeviceDependentResources()
{
	m_drawableText->CreateResources();

}

//リソースを解放するメソッドです Mainクラスから呼ばれます
void RendererBase::ReleaseDeviceDependentResources()
{
	m_drawableText->RelearseResources();
	
}