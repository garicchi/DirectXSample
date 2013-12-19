#pragma once

#include <string>
#include "DeviceResources.h"
#include "Common/StepTimer.h"

using namespace std;

namespace TestDirectX
{

	class LoadableBitmap
	{
	public:
		LoadableBitmap(shared_ptr<DeviceResources> deviceResources, Platform::String^ relativePath,D2D1_RECT_F drawRect);
		void LoadResources();
		void ReleaseResources();

		D2D1_RECT_F m_drawRect;

		// Bitmap‚ª“ü‚éƒŠƒ\[ƒX
		Microsoft::WRL::ComPtr<ID2D1Bitmap> m_bitmap;

		Platform::String^ m_relativePath;
	protected:
		shared_ptr<DeviceResources> m_deviceResources;

		
	};

}