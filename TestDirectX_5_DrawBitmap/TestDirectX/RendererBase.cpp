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
	
	//Bitmapを描画
	context->DrawBitmap(m_bitmap.Get(),&RectF(100,100,200,200),1.0,D2D1_INTERPOLATION_MODE_LINEAR,0);

	context->EndDraw();	//描画終了
	
}

//リソースを確保するメソッドです コンストラクタからだけでなく、Mainクラスからも呼ばれます
void RendererBase::CreateDeviceDependentResources()
{
	//アプリがインストールされた場所を指す
	auto location = Package::Current->InstalledLocation;
	//ディレクトリ区切り文字「\\」を足す
	String^ path = String::Concat(location->Path, "\\");
	//ファイル名を相対パスで足す
	path = String::Concat(path, "Assets/sample.png");

	//BitmapDecorder
	ComPtr<IWICBitmapDecoder> wicBitmapDecoder;
	
	//BitmapDecorderを作る(ファイルパスを指定)
	m_deviceResources->GetWicImagingFactory()->CreateDecoderFromFilename(
		path->Data(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&wicBitmapDecoder
		);
	
	//BitmapFrame
	ComPtr<IWICBitmapFrameDecode> wicBitmapFrame;
	
	//BitmapDecorderからBitmapFrameを作る
	wicBitmapDecoder->GetFrame(0, &wicBitmapFrame);
		
	//FormatConverter
	ComPtr<IWICFormatConverter> wicFormatConverter;
	
	//WicImaginfFactoryからFormatConverterを作る
	m_deviceResources->GetWicImagingFactory()->CreateFormatConverter(&wicFormatConverter);

	//FormatConverterをイニシャライズ(BitmapFrameを使う)
	wicFormatConverter->Initialize(
		wicBitmapFrame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0,
		WICBitmapPaletteTypeCustom  // The BGRA format has no palette so this value is ignored.
		);
		

	double dpiX = 96.0f;
	double dpiY = 96.0f;
	
	//FormatConverterからdpiを取得
	wicFormatConverter->GetResolution(&dpiX, &dpiY);
	
	//ID2D1Bitmapリソースを生成(FormatConverterから)
	m_deviceResources->GetD2DDeviceContext()->CreateBitmapFromWicBitmap(
		wicFormatConverter.Get(),
		BitmapProperties(
		PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
		static_cast<float>(dpiX),
		static_cast<float>(dpiY)
		),
		&m_bitmap
		);

	//リソースの解放
	wicBitmapDecoder.Reset();
	wicFormatConverter.Reset();
	
}

//リソースを解放するメソッドです Mainクラスから呼ばれます
void RendererBase::ReleaseDeviceDependentResources()
{
	m_bitmap.Reset();
}