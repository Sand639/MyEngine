/*******************************************************************************
* タイトル:		ウィンドウプログラム
* プログラム名:	Window.cpp
* 作成者:		Sand639/大槻　海斗	(https://github.com/Sand639)
* 作成日:		2025/07/27
* 説明:		    ウィンドウクラス
********************************************************************************/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "Window.h"
#include <stdexcept>

/*******************************************************************************
 関数名:	Window::Window(HINSTANCE hInstance)
 引数　:	HINSTANCE hInstance
			アプリケーションのインスタンスハンドル
 戻り値:	void
 説明　:	コンストラクタ
			ウィンドウクラスのインスタンスを初期化します。
			ウィンドウクラス名を設定し、インスタンスハンドルを保存します。
			この関数はウィンドウの作成前に呼び出される必要があります。
*******************************************************************************/
Window::Window(HINSTANCE hInstance)
	: m_hInstance(hInstance) {}

/*******************************************************************************
 関数名:	Window::~Window()
 引数　:	void
 戻り値:	void
 説明　:	デストラクタ
			ウィンドウの破棄とクラスの登録解除を行います。
			ウィンドウが存在する場合は、DestroyWindowを呼び出して破棄します。
			また、UnregisterClassAを使用してウィンドウクラスを登録解除します。
*******************************************************************************/
Window::~Window() {
	// ウィンドウが存在する場合は破棄
	if (m_hwnd) {
		DestroyWindow(m_hwnd);	// ウィンドウを破棄
	}
	// ウィンドウクラスの登録解除
	UnregisterClassA(m_className.c_str(), m_hInstance);
}

/*******************************************************************************
 関数名:	Window::Create(const std::string& title, int width, int height)
 引数　:	const std::string& title
			ウィンドウのタイトル
			int width
			ウィンドウの幅
			int height
			ウィンドウの高さ
 戻り値:	bool
			成功した場合は true、失敗した場合は false
 説明　:	ウィンドウを作成する関数
			ウィンドウクラスを登録し、CreateWindowExAを使用してウィンドウを作成します。
			成功した場合は true を返し、失敗した場合は false を返します。
 *******************************************************************************/
bool Window::Create(const std::string& title, int width, int height) {

	// ウィンドウクラス構造体の設定
	WNDCLASSEX wc = {};             // WNDCLASSEX構造体の初期化
	wc.cbSize = sizeof(WNDCLASSEX); // 構造体のサイズを設定
	wc.style = 0;                   // ウィンドウスタイルの設定
	wc.lpfnWndProc = WndProc;       // ウィンドウプロシージャのポインタ
	wc.cbClsExtra = 0;              // クラスの追加情報のサイズ
	wc.cbWndExtra = 0;              //  ウィンドウの追加情報のサイズ
	wc.hInstance = m_hInstance;       // アプリケーションのインスタンスハンドル
	wc.hIcon = nullptr;             // アイコンのハンドル（nullptrはデフォルトアイコンを使用）
	wc.lpszClassName = m_className.c_str();  // クラス名
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);    // カーソルの種類設定
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  // ウィンドウの背景色の設定
	wc.lpszMenuName = nullptr;      // メニュー名（nullptrはメニューなし）
	wc.hIconSm = nullptr;           // 小さいアイコンのハンドル（nullptrはデフォルトアイコンを使用）


	//設定した構造体をWindowsへ登録
	if (!RegisterClassExA(&wc)) {
		MessageBoxA(nullptr, "ウィンドウクラス登録失敗", "エラー", MB_ICONERROR);
		return false;
	}

	//ウィンドウサイズの調整
	RECT rc = {
		0, 0,		//左上	（横0    縦0 )
		width, height };	//右下　（横1280 縦720）

	//描画領域がwidth * heightになるようにサイズ調整する↓
	//ウィンドウのサイズ調整関数
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX), FALSE);

	// ウィンドウの生成
	m_hwnd = CreateWindowExA(
		0	// 拡張スタイル（なし）
		, m_className.c_str(),	// クラス名
		title.c_str(),			// ウィンドウのタイトル
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル（オーバーラップウィンドウ
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,	// ウィンドウの位置とサイズ設定
		nullptr, nullptr, m_hInstance, nullptr	// 親ウィンドウ、メニュー、インスタンスハンドル、追加データ（nullptrはなし）
	);

	// ウィンドウの生成に失敗した場合のエラーハンドリング
	if (!m_hwnd) {
		MessageBoxA(nullptr, "ウィンドウ作成失敗", "エラー", MB_ICONERROR);
		return false;
	}

	return true;
}

/*******************************************************************************
 関数名:	Window::Show(int nCmdShow)
 引数　:	int nCmdShow
			ウィンドウの表示状態
 戻り値:	void
 説明　:	ウィンドウを表示する関数
			ShowWindowとUpdateWindowを使用して、ウィンドウを表示します。
			nCmdShowはウィンドウの表示状態を指定します。
*******************************************************************************/
void Window::Show(int nCmdShow) {
	::ShowWindow(m_hwnd, nCmdShow);	// ウィンドウの表示
	::UpdateWindow(m_hwnd);			// ウィンドウの更新
}

/*******************************************************************************
 関数名:	Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
 引数　:	HWND hwnd
			ウィンドウのハンドル
			UINT msg
			メッセージ識別子
			WPARAM wParam
			ワードパラメータ
			LPARAM lParam
			ロングパラメータ
 戻り値:	LRESULT
			メッセージの処理結果を示す値
 説明　:	ウィンドウプロシージャとして、ウィンドウメッセージを処理します。
 *******************************************************************************/
 LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}