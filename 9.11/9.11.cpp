#include <windows.h>
#include <tchar.h>
#include <time.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hList, hButton, hEdit;

TCHAR str[50];
TCHAR str_radio_box1[50];
TCHAR str_radio_box2[50];
TCHAR str_radio_box3[50];

int rand_time = 0, min = 10, max = 20;
int num = 0, num_min = -10, num_max = 10;
int mas[50];
long long result = 0;


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

void RandNum() {
	num = num_min + rand() % (num_max - num_min + 1);
	if (num == 0) {
		num = num_min + rand() % (num_max - num_min + 1);
	}
	wsprintf(str, TEXT("%d"), num);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));
	switch (message)
	{
	case WM_INITDIALOG: {
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hButton = GetDlgItem(hWnd, IDC_BUTTON1);
		hEdit = GetDlgItem(hWnd, IDC_EDIT1);
	}
					  break;

	case WM_COMMAND: {
		if (LOWORD(wParam) == IDC_BUTTON1) {
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			rand_time = min + rand() % (max - min + 1);

			for (int i = 0; i < rand_time; i++) {
				SendMessage(hList, LB_ADDSTRING, 0, LPARAM(str));
				RandNum();
				mas[i] = num;
			}
		}

		if (LOWORD(wParam) == IDC_RADIO1) {
			for (int i = 0; i < rand_time - 1; i++) {
				result += mas[i];
			}
			wsprintf(str_radio_box1, TEXT("%d"), result);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str_radio_box1));
			result = 0;
		}

		if (LOWORD(wParam) == IDC_RADIO2) {
			result = mas[0];
			for (int i = 1; i < rand_time - 1; i++) {
				result *= mas[i];
			}
			wsprintf(str_radio_box2, TEXT("%d"), result);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str_radio_box2));
			result = 0;
		}

		if (LOWORD(wParam) == IDC_RADIO3) {
			for (int i = 0; i < rand_time - 1; i++) {
				result += mas[i];
			}
			result /= rand_time;

			double rez = 123.23;

			wsprintf(str_radio_box3, TEXT("%d"), result);
			SendMessage(hEdit, WM_SETTEXT, 0, LPARAM(str_radio_box3));
			result = 0;
		}

	}
				   break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALS