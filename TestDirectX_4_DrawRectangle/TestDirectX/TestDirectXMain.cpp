#include "pch.h"
#include "TestDirectXMain.h"
#include "Common\DirectXHelper.h"

using namespace TestDirectX;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// アプリケーションの読み込み時にアプリケーション資産を読み込んで初期化します。
TestDirectXMain::TestDirectXMain(const std::shared_ptr<DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources)
{
	// デバイスが失われたときや再作成されたときに通知を受けるように登録します
	m_deviceResources->RegisterDeviceNotify(this);

	// TODO: これをアプリのコンテンツの初期化で置き換えます。
	
	m_rendererBase = std::unique_ptr<RendererBase>(new RendererBase(m_deviceResources));

	// TODO: 既定の可変タイムステップ モード以外のモードが必要な場合は、タイマー設定を変更してください。
	// 例: 60 FPS 固定タイムステップ更新ロジックでは、次を呼び出します:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

TestDirectXMain::~TestDirectXMain()
{
	// デバイスの通知を登録解除しています
	m_deviceResources->RegisterDeviceNotify(nullptr);
}

// ウィンドウのサイズが変更される (デバイスの方向が変更されるなど) 場合に、 アプリケーションの状態を更新します。
void TestDirectXMain::CreateWindowSizeDependentResources() 
{
	// TODO: これをアプリのコンテンツのサイズに依存する初期化で置き換えます。
}

// アプリケーション状態をフレームごとに 1 回更新します。
void TestDirectXMain::Update() 
{
	// シーン オブジェクトを更新します。
	m_timer.Tick([&]()
	{
		// TODO: これをアプリのコンテンツの更新関数で置き換えます。
	
		m_rendererBase->Update(m_timer);
	});
}

// 現在のアプリケーション状態に応じて現在のフレームを描画します。
// フレームが描画され、表示準備が完了すると、true を返します。
bool TestDirectXMain::Render() 
{
	// 初回更新前にレンダリングは行わないようにしてください。
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// ビューポートをリセットして全画面をターゲットとします。
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// レンダー ターゲットを画面にリセットします。
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// バック バッファーと深度ステンシル ビューをクリアします。
	context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// シーン オブジェクトを描画します。
	// TODO: これをアプリのコンテンツのレンダリング関数で置き換えます。
	
	m_rendererBase->Render();

	return true;
}

// デバイス リソースを解放する必要が生じたことをレンダラーに通知します。
void TestDirectXMain::OnDeviceLost()
{
	
	m_rendererBase->ReleaseDeviceDependentResources();
}

// デバイス リソースの再作成が可能になったことをレンダラーに通知します。
void TestDirectXMain::OnDeviceRestored()
{
	
	m_rendererBase->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
