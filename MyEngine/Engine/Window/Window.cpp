/*******************************************************************************
* �^�C�g��:		�E�B���h�E�v���O����
* �v���O������:	Window.cpp
* �쐬��:		Sand639/��΁@�C�l	(https://github.com/Sand639)
* �쐬��:		2025/07/27
* ����:		    �E�B���h�E�N���X
********************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "Window.h"
#include <stdexcept>

/*******************************************************************************
 �֐���:	Window::Window(HINSTANCE hInstance)
 �����@:	HINSTANCE hInstance
			�A�v���P�[�V�����̃C���X�^���X�n���h��
 �߂�l:	void
 �����@:	�R���X�g���N�^
			�E�B���h�E�N���X�̃C���X�^���X�����������܂��B
			�E�B���h�E�N���X����ݒ肵�A�C���X�^���X�n���h����ۑ����܂��B
			���̊֐��̓E�B���h�E�̍쐬�O�ɌĂяo�����K�v������܂��B
*******************************************************************************/
Window::Window(HINSTANCE hInstance)
	: m_hInstance(hInstance) {}

/*******************************************************************************
 �֐���:	Window::~Window()
 �����@:	void
 �߂�l:	void
 �����@:	�f�X�g���N�^
			�E�B���h�E�̔j���ƃN���X�̓o�^�������s���܂��B
			�E�B���h�E�����݂���ꍇ�́ADestroyWindow���Ăяo���Ĕj�����܂��B
			�܂��AUnregisterClassA���g�p���ăE�B���h�E�N���X��o�^�������܂��B
*******************************************************************************/
Window::~Window() {
	// �E�B���h�E�����݂���ꍇ�͔j��
	if (m_hwnd) {
		DestroyWindow(m_hwnd);	// �E�B���h�E��j��
	}
	// �E�B���h�E�N���X�̓o�^����
	UnregisterClassA(m_className.c_str(), m_hInstance);
}

/*******************************************************************************
 �֐���:	Window::Create(const std::string& title, int width, int height)
 �����@:	const std::string& title
			�E�B���h�E�̃^�C�g��
			int width
			�E�B���h�E�̕�
			int height
			�E�B���h�E�̍���
 �߂�l:	bool
			���������ꍇ�� true�A���s�����ꍇ�� false
 �����@:	�E�B���h�E���쐬����֐�
			�E�B���h�E�N���X��o�^���ACreateWindowExA���g�p���ăE�B���h�E���쐬���܂��B
			���������ꍇ�� true ��Ԃ��A���s�����ꍇ�� false ��Ԃ��܂��B
 *******************************************************************************/
bool Window::Create(const std::string& title, int width, int height) {

	// �E�B���h�E�N���X�\���̂̐ݒ�
	WNDCLASSEX wc = {};             // WNDCLASSEX�\���̂̏�����
	wc.cbSize = sizeof(WNDCLASSEX); // �\���̂̃T�C�Y��ݒ�
	wc.style = 0;                   // �E�B���h�E�X�^�C���̐ݒ�
	wc.lpfnWndProc = WndProc;       // �E�B���h�E�v���V�[�W���̃|�C���^
	wc.cbClsExtra = 0;              // �N���X�̒ǉ����̃T�C�Y
	wc.cbWndExtra = 0;              //  �E�B���h�E�̒ǉ����̃T�C�Y
	wc.hInstance = m_hInstance;       // �A�v���P�[�V�����̃C���X�^���X�n���h��
	wc.hIcon = nullptr;             // �A�C�R���̃n���h���inullptr�̓f�t�H���g�A�C�R�����g�p�j
	wc.lpszClassName = m_className.c_str();  // �N���X��
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);    // �J�[�\���̎�ސݒ�
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  // �E�B���h�E�̔w�i�F�̐ݒ�
	wc.lpszMenuName = nullptr;      // ���j���[���inullptr�̓��j���[�Ȃ��j
	wc.hIconSm = nullptr;           // �������A�C�R���̃n���h���inullptr�̓f�t�H���g�A�C�R�����g�p�j


	//�ݒ肵���\���̂�Windows�֓o�^
	if (!RegisterClassExA(&wc)) {
		MessageBoxA(nullptr, "�E�B���h�E�N���X�o�^���s", "�G���[", MB_ICONERROR);
		return false;
	}

	//�E�B���h�E�T�C�Y�̒���
	RECT rc = {
		0, 0,		//����	�i��0    �c0 )
		width, height };	//�E���@�i��1280 �c720�j

	//�`��̈悪width * height�ɂȂ�悤�ɃT�C�Y�������遫
	//�E�B���h�E�̃T�C�Y�����֐�
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX), FALSE);

	// �E�B���h�E�̐���
	m_hwnd = CreateWindowExA(
		0	// �g���X�^�C���i�Ȃ��j
		, m_className.c_str(),	// �N���X��
		title.c_str(),			// �E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW,	// �E�B���h�E�X�^�C���i�I�[�o�[���b�v�E�B���h�E
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,	// �E�B���h�E�̈ʒu�ƃT�C�Y�ݒ�
		nullptr, nullptr, m_hInstance, nullptr	// �e�E�B���h�E�A���j���[�A�C���X�^���X�n���h���A�ǉ��f�[�^�inullptr�͂Ȃ��j
	);

	// �E�B���h�E�̐����Ɏ��s�����ꍇ�̃G���[�n���h�����O
	if (!m_hwnd) {
		MessageBoxA(nullptr, "�E�B���h�E�쐬���s", "�G���[", MB_ICONERROR);
		return false;
	}

	return true;
}

/*******************************************************************************
 �֐���:	Window::Show(int nCmdShow)
 �����@:	int nCmdShow
			�E�B���h�E�̕\�����
 �߂�l:	void
 �����@:	�E�B���h�E��\������֐�
			ShowWindow��UpdateWindow���g�p���āA�E�B���h�E��\�����܂��B
			nCmdShow�̓E�B���h�E�̕\����Ԃ��w�肵�܂��B
*******************************************************************************/
void Window::Show(int nCmdShow) {
	::ShowWindow(m_hwnd, nCmdShow);	// �E�B���h�E�̕\��
	::UpdateWindow(m_hwnd);			// �E�B���h�E�̍X�V
}

/*******************************************************************************
 �֐���:	Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
 �����@:	HWND hwnd
			�E�B���h�E�̃n���h��
			UINT msg
			���b�Z�[�W���ʎq
			WPARAM wParam
			���[�h�p�����[�^
			LPARAM lParam
			�����O�p�����[�^
 �߂�l:	LRESULT
			���b�Z�[�W�̏������ʂ������l
 �����@:	�E�B���h�E�v���V�[�W���Ƃ��āA�E�B���h�E���b�Z�[�W���������܂��B
 *******************************************************************************/
 LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}