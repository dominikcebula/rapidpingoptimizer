/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#include "DialogMain.h"
#include <iostream>
#include <sstream>
#include <CommCtrl.h>
#include "resource.h"
#include "common.h"

using namespace std;

#define LoadIco(HANDLE, IMAGE, COMPONENT) HANDLE=LoadBitmap(hInst, MAKEINTRESOURCE(IMAGE)); \
										  SendMessage(GetDlgItem(hDialog, COMPONENT), \
													  BM_SETIMAGE, \
													  IMAGE_BITMAP, \
													  reinterpret_cast<LPARAM>(HANDLE));
#define FreeIco(HANDLE) DeleteObject(HANDLE);

DialogMain::DialogMain(HINSTANCE hInst)
{
	this->hInst=hInst;
	this->changes=false;
	hDialog=CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DLGMAIN), NULL, DialogProc, reinterpret_cast<LPARAM>(this));
	
	stringstream ss;
	ss << "RapidPingOptimizer v" << VER;
	SetWindowText(hDialog, ss.str().c_str());

	InitIcons();

	interfaces=new ListViewInterfaces(hDialog);
}

void DialogMain::InitIcons()
{
	iconMain=LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));
	SetClassLong(hDialog, GCL_HICON, reinterpret_cast<LONG>(iconMain));
	
	LoadIco(bRefresh, IDB_REFRESH, IDC_BTN_REFRESH);
	LoadIco(bCheck, IDB_CHECK, IDC_BTN_CHECK_ALL);
	LoadIco(bUncheck, IDB_UNCHECK, IDC_BTN_UNCHECK_ALL);
	LoadIco(bArrowUp, IDB_ARROWUP, IDC_BTN_ENABLE_OPTIMIZATION);
	LoadIco(bArrowDown, IDB_ARROWDOWN, IDC_BTN_DISABLE_OPTIMIZATION);
	LoadIco(bAbout, IDB_ABOUT, IDC_BTN_ABOUT);
}

void DialogMain::FreeIcons()
{
	FreeIco(bAbout);
	FreeIco(bArrowDown);
	FreeIco(bArrowUp);
	FreeIco(bUncheck);
	FreeIco(bCheck);
	FreeIco(bRefresh);
	FreeIco(iconMain);
}

DialogMain::~DialogMain(void)
{
	delete interfaces;
	FreeIcons();
}

void DialogMain::OnBtnRefresh(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	interfaces->Refresh();
}

WPARAM DialogMain::run()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT_PTR CALLBACK DialogMain::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static DialogMain* dlg;

	switch (uMsg) {
	case WM_INITDIALOG:
		dlg=reinterpret_cast<DialogMain*>(lParam);
		break;
	case WM_CLOSE:
		if (dlg->changes)
			MsgBox("Remember that you must reboot your computer for the changes to take effect.\0");
		EndDialog(dlg->hDialog, 0);
		DestroyWindow(dlg->hDialog);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (wParam) {
			case IDC_BTN_REFRESH:
				dlg->OnBtnRefresh(hwndDlg, uMsg, wParam, lParam);
				break;
			case IDC_BTN_CHECK_ALL:
				dlg->interfaces->SelectAll();
				break;
			case IDC_BTN_UNCHECK_ALL:
				dlg->interfaces->UnselectAll();
				break;
			case IDC_BTN_ENABLE_OPTIMIZATION:
				dlg->changes=true;
				dlg->interfaces->optimize(1);
				dlg->interfaces->Refresh();
				break;
			case IDC_BTN_DISABLE_OPTIMIZATION:
				dlg->changes=true;
				dlg->interfaces->optimize(0);
				dlg->interfaces->Refresh();
				break;
			case IDC_BTN_ABOUT:
				DialogAbout about(dlg->hInst, dlg->hDialog);
				about.ShowModal();
				break;
		}
		break;
	}

	return 0;
}


