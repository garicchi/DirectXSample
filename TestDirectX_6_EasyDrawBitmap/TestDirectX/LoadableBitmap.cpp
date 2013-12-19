#include "pch.h"
#include "LoadableBitmap.h"
#include "Common/DirectXHelper.h"

using namespace TestDirectX;
using namespace std;
using namespace Platform;
using namespace D2D1;
using namespace Microsoft::WRL;
using namespace Windows::ApplicationModel;

LoadableBitmap::LoadableBitmap(shared_ptr<DeviceResources> deviceResources, String^ relativePath,D2D1_RECT_F drawRect)
:m_deviceResources(deviceResources), m_relativePath(relativePath), m_drawRect(drawRect)
{

}

void LoadableBitmap::LoadResources()
{
	//アプリがインストールされた場所を指す
	auto location = Package::Current->InstalledLocation;
	//ディレクトリ区切り文字「\\」を足す
	String^ path = String::Concat(location->Path, "\\");
	//ファイル名を相対パスで足す
	path = String::Concat(path, m_relativePath);

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
}

void LoadableBitmap::ReleaseResources()
{
	m_bitmap.Reset();
}