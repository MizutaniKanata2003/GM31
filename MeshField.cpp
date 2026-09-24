#include "main.h"
#include "renderer.h"
#include "MeshField.h"
#include "audio.h"

float g_FieldHeight[ 21 ][ 21 ] =
{
	// z = 0 : 外周の山
	{2.2f, 2.4f, 2.7f, 2.9f, 3.0f, 2.8f, 2.6f, 2.4f, 2.3f, 2.2f, 2.1f, 2.2f, 2.4f, 2.6f, 2.8f, 3.0f, 2.9f, 2.7f, 2.5f, 2.3f, 2.2f},

	// z = 1
	{2.3f, 2.6f, 2.9f, 3.0f, 3.0f, 2.9f, 2.6f, 2.3f, 2.1f, 2.0f, 2.0f, 2.1f, 2.3f, 2.6f, 2.9f, 3.0f, 3.0f, 2.9f, 2.6f, 2.4f, 2.3f},

	// z = 2
	{2.5f, 2.8f, 3.0f, 3.0f, 2.9f, 2.7f, 2.4f, 2.1f, 1.9f, 1.8f, 1.8f, 1.9f, 2.1f, 2.4f, 2.7f, 2.9f, 3.0f, 3.0f, 2.9f, 2.7f, 2.5f},

	// z = 3
	{2.7f, 3.0f, 3.0f, 2.9f, 2.7f, 2.4f, 2.0f, 1.7f, 1.5f, 1.4f, 1.4f, 1.5f, 1.7f, 2.0f, 2.4f, 2.7f, 2.9f, 3.0f, 3.0f, 2.9f, 2.7f},

	// z = 4
	{2.9f, 3.0f, 2.9f, 2.7f, 2.4f, 2.0f, 1.6f, 1.3f, 1.1f, 1.0f, 1.0f, 1.1f, 1.3f, 1.6f, 2.0f, 2.4f, 2.7f, 2.9f, 3.0f, 3.0f, 2.9f},

	// z = 5
	{2.8f, 2.9f, 2.7f, 2.4f, 2.0f, 1.6f, 1.2f, 0.9f, 0.7f, 0.6f, 0.6f, 0.7f, 0.9f, 1.2f, 1.6f, 2.0f, 2.4f, 2.7f, 2.9f, 2.9f, 2.8f},

	// z = 6
	{2.6f, 2.7f, 2.4f, 2.0f, 1.6f, 1.2f, 0.8f, 0.5f, 0.4f, 0.3f, 0.3f, 0.4f, 0.5f, 0.8f, 1.2f, 1.6f, 2.0f, 2.4f, 2.7f, 2.7f, 2.6f},

	// z = 7
	{2.4f, 2.3f, 2.1f, 1.7f, 1.3f, 0.9f, 0.5f, 0.3f, 0.2f, 0.1f, 0.1f, 0.2f, 0.3f, 0.5f, 0.9f, 1.3f, 1.7f, 2.1f, 2.3f, 2.4f, 2.4f},

	// z = 8 : 開始地点の平地の上端
	{2.3f, 2.1f, 1.9f, 1.5f, 1.1f, 0.7f, 0.4f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.7f, 1.1f, 1.5f, 1.9f, 2.1f, 2.3f, 2.3f},

	// z = 9
	{2.2f, 2.0f, 1.8f, 1.4f, 1.0f, 0.6f, 0.3f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.6f, 1.0f, 1.4f, 1.8f, 2.0f, 2.2f, 2.2f},

	// z = 10 : プレイヤーの開始位置は g_FieldHeight[10][10] == 0.0f
	{2.1f, 2.0f, 1.8f, 1.4f, 1.0f, 0.6f, 0.3f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.6f, 1.0f, 1.4f, 1.8f, 2.0f, 2.1f, 2.1f},

	// z = 11
	{2.2f, 2.0f, 1.8f, 1.4f, 1.0f, 0.6f, 0.3f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.6f, 1.0f, 1.4f, 1.8f, 2.0f, 2.2f, 2.2f},

	// z = 12 : 開始地点の平地の下端
	{2.3f, 2.1f, 1.9f, 1.5f, 1.1f, 0.7f, 0.4f, 0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.2f, 0.7f, 1.1f, 1.5f, 1.9f, 2.1f, 2.3f, 2.3f},

	// z = 13
	{2.4f, 2.3f, 2.1f, 1.7f, 1.3f, 0.9f, 0.5f, 0.3f, 0.2f, 0.1f, 0.1f, 0.2f, 0.3f, 0.5f, 0.9f, 1.3f, 1.7f, 2.1f, 2.3f, 2.4f, 2.4f},

	// z = 14
	{2.6f, 2.7f, 2.4f, 2.0f, 1.6f, 1.2f, 0.8f, 0.5f, 0.4f, 0.3f, 0.3f, 0.4f, 0.5f, 0.8f, 1.2f, 1.6f, 2.0f, 2.4f, 2.7f, 2.7f, 2.6f},

	// z = 15
	{2.8f, 2.9f, 2.7f, 2.4f, 2.0f, 1.6f, 1.2f, 0.9f, 0.7f, 0.6f, 0.6f, 0.7f, 0.9f, 1.2f, 1.6f, 2.0f, 2.4f, 2.7f, 2.9f, 2.9f, 2.8f},

	// z = 16
	{2.9f, 3.0f, 2.9f, 2.7f, 2.4f, 2.0f, 1.6f, 1.3f, 1.1f, 1.0f, 1.0f, 1.1f, 1.3f, 1.6f, 2.0f, 2.4f, 2.7f, 2.9f, 3.0f, 3.0f, 2.9f},

	// z = 17
	{2.7f, 3.0f, 3.0f, 2.9f, 2.7f, 2.4f, 2.0f, 1.7f, 1.5f, 1.4f, 1.4f, 1.5f, 1.7f, 2.0f, 2.4f, 2.7f, 2.9f, 3.0f, 3.0f, 2.9f, 2.7f},

	// z = 18
	{2.5f, 2.8f, 3.0f, 3.0f, 2.9f, 2.7f, 2.4f, 2.1f, 1.9f, 1.8f, 1.8f, 1.9f, 2.1f, 2.4f, 2.7f, 2.9f, 3.0f, 3.0f, 2.9f, 2.7f, 2.5f},

	// z = 19
	{2.3f, 2.6f, 2.9f, 3.0f, 3.0f, 2.9f, 2.6f, 2.3f, 2.1f, 2.0f, 2.0f, 2.1f, 2.3f, 2.6f, 2.9f, 3.0f, 3.0f, 2.9f, 2.6f, 2.4f, 2.3f},

	// z = 20 : 外周の山
	{2.2f, 2.4f, 2.7f, 2.9f, 3.0f, 2.8f, 2.6f, 2.4f, 2.3f, 2.2f, 2.1f, 2.2f, 2.4f, 2.6f, 2.8f, 3.0f, 2.9f, 2.7f, 2.5f, 2.3f, 2.2f},
};
void MeshField::Init()
{
	m_Layer = 1;
	{
		VERTEX_3D vertex[ 21 ][ 21 ];

		for ( int x = 0; x < 21; x++ )
		{
			for ( int z = 0; z < 21; z++ )
			{
				vertex[ x ][ z ].Position = XMFLOAT3( ( x - 10 ) * 10.0f, g_FieldHeight[ z ][ x ], ( z - 10 ) * -10.0f );
				vertex[ x ][ z ].Normal = XMFLOAT3( 0.0f, 1.0f, 0.0f );
				vertex[ x ][ z ].Diffuse = XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
				vertex[ x ][ z ].TexCoord = XMFLOAT2( x, z );

			}
		}
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( VERTEX_3D ) * 21 * 21;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );
	}
	// インデックスバッファ生成
	{
		unsigned int index[ ( 22 * 2 ) * 20 - 2 ];

		int i = 0;
		for ( int x = 0; x < 20; x++ )
		{
			for ( int z = 0; z < 21; z++ )
			{
				index[ i ] = x * 21 + z;
				i++;

				index[ i ] = ( x + 1 ) * 21 + z;
				i++;
			}

			if ( x == 19 )
				break;

			// 縮退ポリゴン
			index[ i ] = ( x + 1 ) * 21 + 20;
			i++;

			index[ i ] = ( x + 1 ) * 21;
			i++;

		}
		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( unsigned int ) * ( ( 22 * 2 ) * 20 - 2 );
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = index;

		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &m_IndexBuffer );
	}
	//　テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile( L"asset\\texture\\field.jpg", WIC_FLAGS_NONE, &metadata, image );
	CreateShaderResourceView( Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture );
	assert( m_Texture );

	// シェーダー読み込み
	Renderer::CreateVertexShader( &m_VertexShader, &m_VertexLayout, "shader\\LitVS.cso" );
	Renderer::CreatePixelShader( &m_PixelShader, "shader\\LitPS.cso" );

	// BGM再生
	Audio* bgm = AddComponent<Audio>( this );
	bgm->Load( "asset\\bgm\\bgm.wav" );
	bgm->Play( true );
}

void MeshField::Update() { GameObject::Update(); }

void MeshField::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout( m_VertexLayout );

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader( m_VertexShader, NULL, 0 );
	Renderer::GetDeviceContext()->PSSetShader( m_PixelShader, NULL, 0 );

	// マトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling( m_Scale.x, m_Scale.y, m_Scale.z );
	rot = XMMatrixRotationRollPitchYaw( m_Rotation.x, m_Rotation.y, m_Rotation.z );
	trans = XMMatrixTranslation( m_Position.x, m_Position.y, m_Position.z );
	world = scale * rot * trans;

	Renderer::SetWorldMatrix( world );

	//　マテリアル設定
	MATERIAL material{};
	material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.TextureEnable = true;
	Renderer::SetMaterial( material );

	// 頂点バッファ設定
	UINT stride = sizeof( VERTEX_3D );
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer( m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources( 0, 1, &m_Texture );

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed( ( 22 * 2 ) * 20 - 2, 0, 0 );

	GameObject::Draw();
}

void MeshField::Uninit()
{
	m_Texture->Release();

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}