/*******************************************************************************
* タイトル:		ウィンドウプログラム
* プログラム名:	Window.h
* 作成者:		Sand639/大槻　海斗	(https://github.com/Sand639)
* 作成日:		2025/07/27
* 説明:			ウィンドウクラス
********************************************************************************/
#pragma once
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include <windows.h>
#include <string>

/*******************************************************************************
 クラス名:	Window
 説明　:	ウィンドウクラス
			このクラスはウィンドウの作成、管理、イベント処理を行います。
*******************************************************************************/
class Window {
private:
	HINSTANCE m_hInstance = nullptr;			// アプリケーションのインスタンスハンドル
	HWND m_hwnd = nullptr;						// ウィンドウハンドル
	std::string m_className = "MyWindowClass";	// ウィンドウクラス名

public:

	//コンストラクタ
	Window() = delete;
	Window(HINSTANCE hInstance);
	// デストラクタ
	~Window();

	// ウィンドウの作成
	bool Create(const std::string& title, int width, int height);
	// ウィンドウのメッセージ処理
	void Show(int nCmdShow);
	// ウィンドウハンドルを取得
	HWND GetHWND() const { return m_hwnd; }
	// インスタンスハンドルを取得
	HINSTANCE GetHInstance() const { return m_hInstance; }

	/// <summary>
	/// ウィンドウプロシージャとして、ウィンドウメッセージを処理します。
	/// </summary>
	/// <param name="hwnd">メッセージを受信するウィンドウのハンドル。</param>
	/// <param name="msg">処理するメッセージの識別子。</param>
	/// <param name="wParam">メッセージに関連する追加情報（ワードパラメータ）。</param>
	/// <param name="lParam">メッセージに関連する追加情報（ロングパラメータ）。</param>
	/// <returns>メッセージの処理結果を示す値（LRESULT型）。</returns>
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};