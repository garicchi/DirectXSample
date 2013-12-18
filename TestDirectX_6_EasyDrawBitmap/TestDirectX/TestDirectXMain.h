#pragma once

#include "Common\StepTimer.h"
#include "DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "RendererBase.h"

// Direct2D および 3D コンテンツを画面上で描画します。
namespace TestDirectX
{
	class TestDirectXMain : public IDeviceNotify
	{
	public:
		TestDirectXMain(const std::shared_ptr<DeviceResources>& deviceResources);
		~TestDirectXMain();
		void CreateWindowSizeDependentResources();
		void Update();
		bool Render();

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		// デバイス リソースへのキャッシュされたポインター。
		std::shared_ptr<DeviceResources> m_deviceResources;

		// TODO: これを独自のコンテンツ レンダラーで置き換えます。
		std::unique_ptr<RendererBase> m_rendererBase;

		// ループ タイマーを描画しています。
		DX::StepTimer m_timer;
	};
}