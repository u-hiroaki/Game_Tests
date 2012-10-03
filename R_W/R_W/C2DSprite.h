#ifndef ___C_2D_SPRITE___
#define ___C_2D_SPRITE___

#include <d3d9.h>
#include <list>
#include <d3dx9.h>
#include "DXTemplateUtility.h"
class C2DSprite
{
    static IDirect3DVertexBuffer9* vBuff;
    static std::list<C2DSprite*> drawObjectList;		// 描画対象リスト
    static IDirect3DVertexDeclaration9 *decl;	// 共通頂点宣言
    static ID3DXEffect *effect;					// 共通エフェクト

    tComPtr< IDirect3DTexture9> tex;		// テクスチャ
    int scW, scH;			// スクリーンサイズ
    int polyW, polyH;		// 板ポリゴンサイズ
    float pivotX, pivotY;	// ピボット座標
    float posX, posY, posZ;	// 位置
    float rad;				// 回転角度（ラジアン）
    float scaleX, scaleY;	// スケール
    float uvLeft, uvTop;	// UV左上座標
    float uvW, uvH;			// UV幅高
    float alpha;			// 透過度
    bool bActivity;			// アクティブ

    // コピー
    void copy( const C2DSprite &r );

public:
    C2DSprite();
    C2DSprite( int screenWidth, int screenHeight );
    C2DSprite( const C2DSprite &r );
    ~C2DSprite();

    C2DSprite &operator =( const C2DSprite &r ) { copy(r); return *this; }

    // 共通頂点バッファ作成
    static void begin_first( IDirect3DDevice9* dev );

    // 後片付け
    static void end_last();

    // 板ポリサイズ指定
    void setSize( int w, int h );

    // スクリーンサイズ指定
    void setScreenSize( int w, int h );

    // ピボット指定
    void setPivot( float x, float y );
    void getPivot( float *x, float *y );

    // 姿勢指定
    void setPos( float x, float y );
    void getPos( float *x, float *y );
    void setRotate( float deg );
    float getRotate();
    void setScale( float sx, float sy );
    void getScale( float *sx, float *sy );

    // テクスチャ設定
    void setTexture( tComPtr<IDirect3DTexture9> tex, bool isResize );

    // UV切り取り指定
    void setUV( float l, float t, float w, float h );
    void getUV_LT( float *l, float *t );
    void getUV_WH( float *w, float *h );

    // α設定
    void setAlpha( float a );
    float getAlpha();

    // プライオリティ設定
    void setPriority( float z );
    float getPriority();

    // アクティビティ設定
    void setActivity( bool isActive );
    bool getActivity();

    // 描画リストに積む
    void draw();

    // 描画リストを一気に描画
    static void drawAll( IDirect3DDevice9 *dev );

    // 描画リストクリア
    static void clearDrawList();
};

#endif//___C_2D_SPRITE___