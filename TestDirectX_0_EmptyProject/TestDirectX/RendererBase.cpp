#include "pch.h"
#include "RendererBase.h"
#include "Common/DirectXHelper.h"

using namespace TestDirectX;
using namespace D2D1;

//レンダラークラスのコンストラクタ 変数の初期化やリソースの確保などをします
RendererBase::RendererBase(const std::shared_ptr<DeviceResources>& deviceResources) :
m_deviceResources(deviceResources)
{
	

	//リソース確保
	CreateDeviceDependentResources();
}

//更新処理です　定期的に呼ばれるので変数の制御などはここでおこないます
void RendererBase::Update(DX::StepTimer const& timer)
{
	
}

// フレームを画面に描画します。
void RendererBase::Render()
{
	//デバイスコンテキストの確保
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();
	
	context->BeginDraw(); //描画開始

	//この中に描画処理を書きます

	
	context->EndDraw();	//描画終了
	
}

//リソースを確保するメソッドです コンストラクタからだけでなく、Mainクラスからも呼ばれます
void RendererBase::CreateDeviceDependentResources()
{
	
}

//リソースを解放するメソッドです Mainクラスから呼ばれます
void RendererBase::ReleaseDeviceDependentResources()
{
	
}