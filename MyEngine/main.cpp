/*******************************************************************************
* タイトル:		メインプログラム
* プログラム名:	main.cpp
* 作成者:		Sand639/大槻　海斗	(https://github.com/Sand639)
* 作成日:		2025/07/26
********************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include <windows.h>
#include "Engine/Core/Engine.h"
#include "Engine/Window/Window.h"

/*******************************************************************************
* グローバル変数
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*******************************************************************************
 関数名:	int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmd, _In_ int nCmdShow)
 引数　:	hInstance: アプリケーションのインスタンスハンドル
			hPrevInstance: 前のインスタンスのハンドル（使用しない）
			lpCmd: コマンドライン引数
			nCmdShow: ウィンドウの表示状態
 戻り値:	正常終了: int型の 0
			異常終了: int型の -1
 説明　:	メイン関数
*******************************************************************************/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmd, _In_ int nCmdShow) {

	//ウィンドウの作成
	Window window(hInstance);
	if (!window.Create("My DirectX12 Engine Window", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return -1;
	}

	// ウィンドウの表示
	window.Show(nCmdShow);

	Engine::Initialize();  // エンジンの初期化

	Engine::Run();  // メインループ処理

	Engine::Finalize();  // エンジンの終了処理

	return 0;

}
