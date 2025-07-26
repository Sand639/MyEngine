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
#include "Engine/Window/Window.h"

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

	//�E�B���h�E�̍쐬
	Window window(hInstance);
	if (!window.Create("My DirectX12 Engine Window", SCREEN_WIDTH, SCREEN_HEIGHT)) {
		return -1;
	}

	// �E�B���h�E�̕\��
	window.Show(nCmdShow);

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