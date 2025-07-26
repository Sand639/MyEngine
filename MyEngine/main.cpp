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

	// ウィンドウクラス名
	const char* CLASS_NAME = "MyWindowClass";
	// ウィンドウタイトル
	const char* WINDOW_NAME = "My DirectX12 Engine Windowゲーム";

	// ウィンドウクラスの登録
	WNDCLASSEX wc = {};             // WNDCLASSEX構造体の初期化
	wc.cbSize = sizeof(WNDCLASSEX); // 構造体のサイズを設定
	wc.style = 0;                   // ウィンドウスタイルの設定
	wc.lpfnWndProc = WndProc;       // ウィンドウプロシージャのポインタ
	wc.cbClsExtra = 0;              // クラスの追加情報のサイズ
	wc.cbWndExtra = 0;              //  ウィンドウの追加情報のサイズ
	wc.hInstance = hInstance;       // アプリケーションのインスタンスハンドル
	wc.hIcon = nullptr;             // アイコンのハンドル（nullptrはデフォルトアイコンを使用）
	wc.lpszClassName = CLASS_NAME;  // クラス名
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);    // カーソルの種類設定
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  // ウィンドウの背景色の設定
	wc.lpszMenuName = nullptr;      // メニュー名（nullptrはメニューなし）
	wc.hIconSm = nullptr;           // 小さいアイコンのハンドル（nullptrはデフォルトアイコンを使用）

	// wcをWindowsへ登録
	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, "ウィンドウクラスの登録に失敗しました", "エラー", MB_ICONERROR);
		return -1;
	}

	// ウィンドウの生成
	HWND hwnd = CreateWindowEx(
		0,  // 拡張スタイル（なし）
		CLASS_NAME, // クラス名
		WINDOW_NAME,  // ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,    // ウィンドウスタイル（オーバーラップウィンドウ）
		CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT,	// ウィンドウの位置とサイズ（デフォルト位置、幅1280、高さ720）
		nullptr, nullptr, hInstance, nullptr	// 親ウィンドウ、メニュー、インスタンスハンドル、追加データ（nullptrはなし）
	);

	// ウィンドウの生成に失敗した場合のエラーハンドリング
	if (!hwnd) {
		MessageBox(nullptr, "ウィンドウの生成に失敗しました", "エラー", MB_ICONERROR);
		return -1;
	}

	// ウィンドウの表示
	ShowWindow(hwnd, nCmdShow);
	// ウィンドウの更新
	UpdateWindow(hwnd);

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