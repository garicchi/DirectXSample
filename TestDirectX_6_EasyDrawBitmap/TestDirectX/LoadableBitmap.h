#pragma once

#include <string>
#include "DeviceResources.h"
#include "Common/StepTimer.h"

namespace TestDirectX{

	class LoadableBitmap
	{
	public:
		LoadableBitmap(std::shared_ptr<DeviceResources>& deviceResources, Platform::String^ relativePath);

	protected:
		std::shared_ptr<DeviceResources> m_deviceResources;

		// Bitmap�����郊�\�[�X
		Microsoft::WRL::ComPtr<ID2D1Bitmap> m_bitmap;
	};

}