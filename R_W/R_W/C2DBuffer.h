#pragma once
#include <d3d9.h>
#include <list>
#include <vector>
#include <d3dx9.h>
#include "DXTemplateUtility.h"

/*********************************************************
大量に描画したい時用クラス
弾幕とか
エネミー祭りとか
そんな感じ
*********************************************************/

class C2DBuffer
{
    static IDirect3DVertexBuffer9* vBuff;
    static std::list<C2DBuffer*> drawObjectList;		// 描画対象リスト
    static std::vector<float>      drawBuffer;
    static IDirect3DVertexDeclaration9 *decl;	// 共通頂点宣言
    static ID3DXEffect *effect;					// 共通エフェクト
    static int scW, scH;			// スクリーンサイズ
    static tComPtr< IDirect3DTexture9> tex;		// テクスチャ
    
    IDirect3DVertexBuffer9*         g_pVBBox;
    IDirect3DIndexBuffer9*          g_pIBBox;

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
    void copy( const C2DBuffer &r );

public:
    C2DBuffer();
    C2DBuffer( const C2DBuffer &r );
    ~C2DBuffer();

    C2DBuffer &operator =( const C2DBuffer &r ) { copy(r); return *this; }

    //effect等作成
    static void begin_first( IDirect3DDevice9* dev );

    // 後片付け
    static void end_last();

    // 板ポリサイズ指定
    void setSize( int w, int h );

    // スクリーンサイズ指定
    static void setScreenSize( int w, int h );

    // ピボット指定
    void setPivot( float x, float y );
    void setPivotCenter();
    void getPivot( float *x, float *y );

    // 姿勢指定
    void setPos( float x, float y );
    void getPos( float *x, float *y );
    void setRotate( float deg );
    float getRotate();
    void setScale( float sx, float sy );
    void getScale( float *sx, float *sy );

    // テクスチャ設定
    static void setTexture( tComPtr<IDirect3DTexture9> tex, bool isResize );

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
