#pragma once

namespace TestDirectX
{
	// MVP マトリックスを頂点シェーダーに送信するために使用する定数バッファー。
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 model;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	// 頂点シェーダーへの頂点ごとのデータの送信に使用します。
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}