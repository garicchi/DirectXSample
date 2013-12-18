#pragma once

#include <string>
#include "DeviceResources.h"
#include "Common/StepTimer.h"

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

		wstring m_text;

		//テキストを描画するためのリソース
		ComPtr<ID2D1SolidColorBrush>  m_textBrush;	//ブラシ
		ComPtr<IDWriteTextLayout> m_textLayout;		//テキストレイアウト
		ComPtr<IDWriteTextFormat> m_textFormat;		//テキストフォーマット

	};
}