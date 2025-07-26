/*******************************************************************************
* �^�C�g��:		�E�B���h�E�v���O����
* �v���O������:	Window.h
* �쐬��:		Sand639/��΁@�C�l	(https://github.com/Sand639)
* �쐬��:		2025/07/27
* ����:			�E�B���h�E�N���X
********************************************************************************/
#pragma once
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include <windows.h>
#include <string>

/*******************************************************************************
 �N���X��:	Window
 �����@:	�E�B���h�E�N���X
			���̃N���X�̓E�B���h�E�̍쐬�A�Ǘ��A�C�x���g�������s���܂��B
*******************************************************************************/
class Window {
private:
	HINSTANCE m_hInstance = nullptr;			// �A�v���P�[�V�����̃C���X�^���X�n���h��
	HWND m_hwnd = nullptr;						// �E�B���h�E�n���h��
	std::string m_className = "MyWindowClass";	// �E�B���h�E�N���X��

public:

	//�R���X�g���N�^
	Window() = delete;
	Window(HINSTANCE hInstance);
	// �f�X�g���N�^
	~Window();

	// �E�B���h�E�̍쐬
	bool Create(const std::string& title, int width, int height);
	// �E�B���h�E�̃��b�Z�[�W����
	void Show(int nCmdShow);
	// �E�B���h�E�n���h�����擾
	HWND GetHWND() const { return m_hwnd; }
	// �C���X�^���X�n���h�����擾
	HINSTANCE GetHInstance() const { return m_hInstance; }

	/// <summary>
	/// �E�B���h�E�v���V�[�W���Ƃ��āA�E�B���h�E���b�Z�[�W���������܂��B
	/// </summary>
	/// <param name="hwnd">���b�Z�[�W����M����E�B���h�E�̃n���h���B</param>
	/// <param name="msg">�������郁�b�Z�[�W�̎��ʎq�B</param>
	/// <param name="wParam">���b�Z�[�W�Ɋ֘A����ǉ����i���[�h�p�����[�^�j�B</param>
	/// <param name="lParam">���b�Z�[�W�Ɋ֘A����ǉ����i�����O�p�����[�^�j�B</param>
	/// <returns>���b�Z�[�W�̏������ʂ������l�iLRESULT�^�j�B</returns>
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};