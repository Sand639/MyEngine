/*******************************************************************************
* �^�C�g��:		���C���v���O����
* �v���O������:	main.cpp
* �쐬��:		Sand639/��΁@�C�l	(https://github.com/Sand639)
* �쐬��:		2025/07/26
********************************************************************************/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include <windows.h>
#include "Engine/Core/Engine.h"

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/*******************************************************************************
 �֐���:	int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmd, _In_ int nCmdShow)
 �����@:	hInstance: �A�v���P�[�V�����̃C���X�^���X�n���h��
			hPrevInstance: �O�̃C���X�^���X�̃n���h���i�g�p���Ȃ��j
			lpCmd: �R�}���h���C������
			nCmdShow: �E�B���h�E�̕\�����
 �߂�l:	����I��: int�^�� 0
			�ُ�I��: int�^�� -1
 �����@:	���C���֐�
*******************************************************************************/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmd, _In_ int nCmdShow) {

	// �E�B���h�E�N���X��
	const char* CLASS_NAME = "MyWindowClass";
	// �E�B���h�E�^�C�g��
	const char* WINDOW_NAME = "My DirectX12 Engine Window�Q�[��";

	// �E�B���h�E�N���X�̓o�^
	WNDCLASSEX wc = {};             // WNDCLASSEX�\���̂̏�����
	wc.cbSize = sizeof(WNDCLASSEX); // �\���̂̃T�C�Y��ݒ�
	wc.style = 0;                   // �E�B���h�E�X�^�C���̐ݒ�
	wc.lpfnWndProc = WndProc;       // �E�B���h�E�v���V�[�W���̃|�C���^
	wc.cbClsExtra = 0;              // �N���X�̒ǉ����̃T�C�Y
	wc.cbWndExtra = 0;              //  �E�B���h�E�̒ǉ����̃T�C�Y
	wc.hInstance = hInstance;       // �A�v���P�[�V�����̃C���X�^���X�n���h��
	wc.hIcon = nullptr;             // �A�C�R���̃n���h���inullptr�̓f�t�H���g�A�C�R�����g�p�j
	wc.lpszClassName = CLASS_NAME;  // �N���X��
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);    // �J�[�\���̎�ސݒ�
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  // �E�B���h�E�̔w�i�F�̐ݒ�
	wc.lpszMenuName = nullptr;      // ���j���[���inullptr�̓��j���[�Ȃ��j
	wc.hIconSm = nullptr;           // �������A�C�R���̃n���h���inullptr�̓f�t�H���g�A�C�R�����g�p�j

	// wc��Windows�֓o�^
	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, "�E�B���h�E�N���X�̓o�^�Ɏ��s���܂���", "�G���[", MB_ICONERROR);
		return -1;
	}

	// �E�B���h�E�̐���
	HWND hwnd = CreateWindowEx(
		0,  // �g���X�^�C���i�Ȃ��j
		CLASS_NAME, // �N���X��
		WINDOW_NAME,  // �E�B���h�E�̃^�C�g��
		WS_OVERLAPPEDWINDOW,    // �E�B���h�E�X�^�C���i�I�[�o�[���b�v�E�B���h�E�j
		CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT,	// �E�B���h�E�̈ʒu�ƃT�C�Y�i�f�t�H���g�ʒu�A��1280�A����720�j
		nullptr, nullptr, hInstance, nullptr	// �e�E�B���h�E�A���j���[�A�C���X�^���X�n���h���A�ǉ��f�[�^�inullptr�͂Ȃ��j
	);

	// �E�B���h�E�̐����Ɏ��s�����ꍇ�̃G���[�n���h�����O
	if (!hwnd) {
		MessageBox(nullptr, "�E�B���h�E�̐����Ɏ��s���܂���", "�G���[", MB_ICONERROR);
		return -1;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hwnd, nCmdShow);
	// �E�B���h�E�̍X�V
	UpdateWindow(hwnd);

	Engine::Initialize();  // �G���W���̏�����

	// ���b�Z�[�W���[�v
	MSG msg = {};
	while (true) {
		// ���b�Z�[�W������ꍇ�͏���
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

		Engine::Update();  // �Q�[�����W�b�N����
		Engine::Draw();    // �`�揈��
	}

	Engine::Finalize();  // �G���W���̏I������

	return static_cast<int>(msg.wParam);

}

/*******************************************************************************
 �֐���:	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 �����@:	hwnd: �E�B���h�E�n���h��
			uMsg: ���b�Z�[�W�̎��ʎq
			wParam: ���b�Z�[�W�Ɋ֘A����ǉ����
			lParam: ���b�Z�[�W�Ɋ֘A����ǉ����
 �߂�l:	 ���b�Z�[�W�̏�������
 �����@:	�E�B���h�E�v���V�[�W��
			�E�B���h�E�ɑ����郁�b�Z�[�W����������֐�
*******************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ���b�Z�[�W�ɉ������������s��
	switch (uMsg) {
	case WM_DESTROY:    // �E�B���h�E���j�������Ƃ��̏���
		PostQuitMessage(0);  // �E�B���h�E�̏I������
		return 0;
	}

	// ���̑��̃��b�Z�[�W������
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}