/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#include "DialogAbout.h"
#include "common.h"
#include "resource.h"

DialogAbout::DialogAbout(HINSTANCE hInst, HWND hParent)
{
	this->hInst=hInst;
	this->hParent=hParent;
}

INT_PTR DialogAbout::ShowModal()
{
	return DialogBox(this->hInst, MAKEINTRESOURCE(IDD_DLGABOUT), this->hParent, DialogProc);
}

INT_PTR CALLBACK DialogAbout::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HFONT font=NULL;

	switch (uMsg) {
	case WM_INITDIALOG:
		font=CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Tahoma\0");
		SendMessage(GetDlgItem(hwndDlg, IDC_STATIC_TITLE), WM_SETFONT, reinterpret_cast<WPARAM>(font), 0);
		break;
	case WM_DESTROY:
		if (font!=NULL)
			DeleteObject(font);
		break;
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case IDOK:
			SendMessage(hwndDlg, WM_CLOSE, 0, 0);
			break;
		}
		break;
	}

	return 0;
}
