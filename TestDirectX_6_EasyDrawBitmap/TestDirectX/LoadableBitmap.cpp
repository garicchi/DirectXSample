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
	//�A�v�����C���X�g�[�����ꂽ�ꏊ���w��
	auto location = Package::Current->InstalledLocation;
	//�f�B���N�g����؂蕶���u\\�v�𑫂�
	String^ path = String::Concat(location->Path, "\\");
	//�t�@�C�����𑊑΃p�X�ő���
	path = String::Concat(path, m_relativePath);

	//BitmapDecorder
	ComPtr<IWICBitmapDecoder> wicBitmapDecoder;

	//BitmapDecorder�����(�t�@�C���p�X���w��)
	m_deviceResources->GetWicImagingFactory()->CreateDecoderFromFilename(
		path->Data(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&wicBitmapDecoder
		);

	//BitmapFrame
	ComPtr<IWICBitmapFrameDecode> wicBitmapFrame;

	//BitmapDecorder����BitmapFrame�����
	wicBitmapDecoder->GetFrame(0, &wicBitmapFrame);

	//FormatConverter
	ComPtr<IWICFormatConverter> wicFormatConverter;

	//WicImaginfFactory����FormatConverter�����
	m_deviceResources->GetWicImagingFactory()->CreateFormatConverter(&wicFormatConverter);

	//FormatConverter���C�j�V�����C�Y(BitmapFrame���g��)
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

	//FormatConverter����dpi���擾
	wicFormatConverter->GetResolution(&dpiX, &dpiY);

	//ID2D1Bitmap���\�[�X�𐶐�(FormatConverter����)
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