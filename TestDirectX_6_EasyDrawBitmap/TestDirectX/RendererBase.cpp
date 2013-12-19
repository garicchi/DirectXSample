#include "pch.h"
#include "RendererBase.h"
#include "Common/DirectXHelper.h"

using namespace TestDirectX;
using namespace D2D1;
using namespace Microsoft::WRL;
using namespace Windows::ApplicationModel;
using namespace Platform;

//レンダラークラスのコンストラクタ 変数の初期化やリソースの確保などをします
RendererBase::RendererBase(const std::shared_ptr<DeviceResources>& deviceResources) :
m_deviceResources(deviceResources)
{
	m_lBitmap=make_shared<LoadableBitmap>(m_deviceResources,ref new String(L"Assets/sample.png"),RectF(0,0,100,100));
	//リソース確保
	CreateDeviceDependentResources();
}

//更新処理です　定期的に呼ばれるので変数の制御などはここでおこないます
void RendererBase::Update(DX::StepTimer const& timer)
{
	m_lBitmap->m_drawRect.right++;
	m_lBitmap->m_drawRect.left++;
}

// フレームを画面に描画します。
void RendererBase::Render()
{
	//デバイスコンテキストの確保
	ID2D1DeviceContext* context = m_deviceResources->GetD2DDeviceContext();
	
	context->BeginDraw(); //描画開始
	
	//Bitmapを描画
	context->DrawBitmap(m_lBitmap->m_bitmap.Get(),m_lBitmap->m_drawRect,1.0,D2D1_INTERPOLATION_MODE_LINEAR,0);

	context->EndDraw();	//描画終了
	
}

//リソースを確保するメソッドです コンストラクタからだけでなく、Mainクラスからも呼ばれます
void RendererBase::CreateDeviceDependentResources()
{
	m_lBitmap->LoadResources();
	
}

//リソースを解放するメソッドです Mainクラスから呼ばれます
void RendererBase::ReleaseDeviceDependentResources()
{
	m_lBitmap->ReleaseResources();
}