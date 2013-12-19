#pragma once

#include <string>
#include "DeviceResources.h"
#include "Common/StepTimer.h"
#include "Utility/DrawableText.h"

using namespace std;
using namespace Microsoft::WRL;

namespace TestDirectX
{
	// 描画するためのレンダラークラスです　Mainクラスから呼ばれます
	class RendererBase
	{
	public:
		RendererBase(const shared_ptr<DeviceResources>& deviceResources);
		virtual void CreateDeviceDependentResources();
		virtual void ReleaseDeviceDependentResources();
		virtual void Update(DX::StepTimer const& timer);
		virtual void Render();

	protected:
		// デバイス リソース
		shared_ptr<DeviceResources> m_deviceResources;

	    shared_ptr<DrawableText> m_drawableText;

	};
}