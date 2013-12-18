#pragma once

#include <string>
#include "DeviceResources.h"
#include "Common/StepTimer.h"



namespace TestDirectX
{
	// 描画するためのレンダラークラスです　Mainクラスから呼ばれます
	class RendererBase
	{
	public:
		RendererBase(const std::shared_ptr<DeviceResources>& deviceResources);
		virtual void CreateDeviceDependentResources();
		virtual void ReleaseDeviceDependentResources();
		virtual void Update(DX::StepTimer const& timer);
		virtual void Render();

	protected:
		// デバイス リソース
		std::shared_ptr<DeviceResources> m_deviceResources;

		D2D1_RECT_F m_rectSize;

		// ライン描画するためのリソース
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>    m_rectBrush;

	};
}