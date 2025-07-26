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

	// メッセージループ
	MSG msg = {};
	while (true) {
		// メッセージがある場合は処理
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			break;
		}

		Engine::Update();  // ゲームロジック処理
		Engine::Draw();    // 描画処理
	}

	Engine::Finalize();  // エンジンの終了処理

	return static_cast<int>(msg.wParam);

}

/*******************************************************************************
 関数名:	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 引数　:	hwnd: ウィンドウハンドル
			uMsg: メッセージの識別子
			wParam: メッセージに関連する追加情報
			lParam: メッセージに関連する追加情報
 戻り値:	 メッセージの処理結果
 説明　:	ウィンドウプロシージャ
			ウィンドウに送られるメッセージを処理する関数
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// メッセージに応じた処理を行う
	switch (uMsg) {
	case WM_DESTROY:    // ウィンドウが破棄されるときの処理
		PostQuitMessage(0);  // ウィンドウの終了処理
		return 0;
	}

	// その他のメッセージを処理
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}