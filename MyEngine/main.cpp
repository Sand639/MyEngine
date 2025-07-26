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

	Engine::Run();  // ���C�����[�v����

	Engine::Finalize();  // �G���W���̏I������

	return 0;

}
