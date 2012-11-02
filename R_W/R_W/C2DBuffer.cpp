#include "C2DBuffer.h"
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "d3dx9.lib")

	std::list<C2DBuffer*> C2DBuffer::drawObjectList;
	IDirect3DVertexDeclaration9 *C2DBuffer::decl;
	ID3DXEffect *C2DBuffer::effect;
    int C2DBuffer::scH = 600;
    int C2DBuffer::scW = 800;

	C2DBuffer::C2DBuffer( int screenWidth, int screenHeight ) :
		tex(),
		polyW(128), polyH(128),
		pivotX(), pivotY(),
		posX(), posY(), posZ(),
		rad(),
		scaleX(1.0f), scaleY(1.0f),
		uvLeft(), uvTop(),
		uvW(1.0f), uvH(1.0f),
		alpha(1.0f),
		bActivity(true)
	{
		setScreenSize( screenWidth, screenHeight );
	}

	C2DBuffer::C2DBuffer() :
		tex(),
		polyW(128), polyH(128),
		pivotX(), pivotY(),
		posX(), posY(), posZ(),
		rad(),
		scaleX(1.0f), scaleY(1.0f),
		uvLeft(), uvTop(),
		uvW(1.0f), uvH(1.0f),
		alpha(1.0f),
		bActivity(true)
	{
		setScreenSize( 640, 480 );
	}

	C2DBuffer::C2DBuffer( const C2DBuffer &r ) {
		copy( r );
	}

	C2DBuffer::~C2DBuffer() {}

	// コピー
	void C2DBuffer::copy( const C2DBuffer &r ) {
		tex = r.tex;
		polyW = r.polyW;
		polyH = r.polyH;
		pivotX = r.pivotX;
		pivotY = r.pivotY;
		posX = r.posX;
		posY = r.posY;
		posZ = r.posZ;
		rad = r.rad;
		scaleX = r.scaleX;
		scaleY = r.scaleY;
		uvLeft = r.uvLeft;
		uvTop = r.uvTop;
		uvW = r.uvW;
		uvH = r.uvH;
		alpha = r.alpha;
		scW = r.scW;
		scH = r.scH;
		bActivity = r.bActivity;
	}

	// 共通頂点バッファ作成
	void C2DBuffer::begin_first( IDirect3DDevice9* dev ) {

		// シェーダ作成
		if (effect == 0) {
			ID3DXBuffer *error = 0;
			if ( FAILED( D3DXCreateEffectFromFile( dev, L"Shader\\sample.fx", 0, 0, 0, 0, &effect, &error) ) ) {
				OutputDebugStringA( (const char*)error->GetBufferPointer());
				return;
			}
		}

		// 頂点宣言作成
		if (decl == 0) {
			D3DVERTEXELEMENT9 elems[] = {
				{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
				{0, sizeof(float) * 3, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
				D3DDECL_END()
			};
			dev->CreateVertexDeclaration( elems, &decl );
		}
	}

	// 後片付け
	void C2DBuffer::end_last() {
		if (effect)
			effect->Release();
		if (decl)
			decl->Release();
	}

	// 板ポリサイズ指定
	void C2DBuffer::setSize( int w, int h ) {
		polyW = w;
		polyH = h;
	}

	// スクリーンサイズ指定
	void C2DBuffer::setScreenSize( int w, int h ) {
		scW = w;
		scH = h;
	}

	// ピボット指定
	void C2DBuffer::setPivot( float x, float y ) {
		pivotX = x;
		pivotY = y;
	}
    void C2DBuffer::setPivotCenter()
    {
        this->pivotX = this->polyH/2;
        this->pivotY= this->polyH/2;
    }

	void C2DBuffer::getPivot( float *x, float *y ) {
		*x = pivotX;
		*y = pivotY;
	}

	// 姿勢指定
	void C2DBuffer::setPos( float x, float y ) {
        posX = x;
		posY = y;
	}

	void C2DBuffer::getPos( float *x, float *y ) {
		*x = posX;
		*y = posY;
	}

	void C2DBuffer::setRotate( float deg ) {
		// ラジアンに変換
		rad = deg / 180.0f * 3.1415926535f;
	}

	float C2DBuffer::getRotate() {
		// デグリーで返す
		return rad / 3.14159265f * 180.0f;
	}

	void C2DBuffer::setScale( float sx, float sy ) {
		scaleX = sx;
		scaleY = sy;
	}

	void C2DBuffer::getScale( float *sx, float *sy ) {
		*sx = scaleX;
		*sy = scaleY;
	}

	// テクスチャ設定
	void C2DBuffer::setTexture( tComPtr<IDirect3DTexture9> tex, bool isResize ) {

        this->tex = tex;
		if (isResize == true) {
			D3DSURFACE_DESC desc;
            tex.GetPtr()->GetLevelDesc( 0, &desc );
			setSize( desc.Width, desc.Height );
		}
	}

	// UV切り取り指定
	void C2DBuffer::setUV( float l, float t, float w, float h ) {
		uvLeft = l;
		uvTop = t;
		uvW = w;
		uvH = h;
	}

	void C2DBuffer::getUV_LT( float *l, float *t ) {
		*l = uvLeft;
		*t = uvTop;
	}

	void C2DBuffer::getUV_WH( float *w, float *h ) {
		*w = uvW;
		*h = uvH;
	}

	// α設定
	void C2DBuffer::setAlpha( float a ) {
		alpha = a;
	}

	float C2DBuffer::getAlpha() {
		return alpha;
	}

	// アクティビティ設定
	void C2DBuffer::setActivity( bool isActive ) {
		bActivity = isActive;
	}

	bool C2DBuffer::getActivity() {
		return bActivity;
	}

	// プライオリティ設定
	void C2DBuffer::setPriority( float z ) {
		posZ = z;
	}

	float C2DBuffer::getPriority() {
		return posZ;
	}

	// 描画リストに積む
	void C2DBuffer::draw() {
		drawObjectList.push_back( this );
	}

	// 描画リストを一気に描画
	void C2DBuffer::drawAll( IDirect3DDevice9 *dev ) {
		if (effect == 0 || decl == 0)
			return;	// 描画不可

		// 頂点バッファ・頂点宣言設定
		dev->SetVertexDeclaration( decl );

		// 2D描画用射影変換行列
		D3DXMATRIX proj;
		D3DXMatrixIdentity( &proj );
		proj._41 = -1.0f;
		proj._42 =  1.0f;
		proj._11 =  2.0f / scW;
		proj._22 = -2.0f / scH;
		// シェーダ開始
		UINT numPass = 0;
		effect->SetTechnique( "Tech" );
		effect->Begin(&numPass, 0);
		effect->BeginPass(0);

		// 描画リストに登録されているスプライトを一気に描画する
		std::list<C2DBuffer*>::iterator it = drawObjectList.begin();
		for (; it != drawObjectList.end(); it++) {
			C2DBuffer* sp = (*it);
			if (sp->bActivity == false)
				continue;

			D3DXMATRIX world, scale, rot;
			D3DXMatrixScaling( &world, (float)sp->polyW, (float)sp->polyH, 1.0f );	// ポリゴンサイズに
			D3DXMatrixScaling( &scale, sp->scaleX, sp->scaleY, 1.0f );	// ローカルスケール
			D3DXMatrixRotationZ( &rot, sp->rad );						// 回転
			world._41 = -sp->pivotX;		// ピボット分オフセット
			world._42 = -sp->pivotY;
			world = world * scale * rot;
			world._41 += sp->posX + sp->pivotX;	// ピボット分オフセット
			world._42 += sp->posY + sp->pivotY;
            float posv[] = 
            {
                {0.0f,0.0f,0.0f,1.0f}
                {1.0f,0.0f,0.0f,1.0f}
                {0.0f,1.0f,0.0f,1.0f}
                {1.0f,1.0f,0.0f,1.0f}
            };


			effect->SetMatrix( "proj", &proj );
            effect->SetTexture( "tex", sp->tex.GetPtr() );
			effect->SetFloat( "uv_left"  , sp->uvLeft );
			effect->SetFloat( "uv_top"   , sp->uvTop );
			effect->SetFloat( "uv_width" , sp->uvW );
			effect->SetFloat( "uv_height", sp->uvH );
			effect->SetFloat( "alpha"    , sp->alpha );
			effect->CommitChanges();
			dev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
		}

		effect->EndPass();
		effect->End();
	}

	// 描画リストクリア
	void C2DBuffer::clearDrawList() {
		drawObjectList.clear();
	}
