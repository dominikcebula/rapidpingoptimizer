/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#ifndef _DIALOGMAIN_H_
#define _DIALOGMAIN_H_

#include <Windows.h>
#include "ListViewInterfaces.h"
#include "DialogAbout.h"

class DialogMain {
private:
	ListViewInterfaces* interfaces;
	HINSTANCE hInst;
	HWND hDialog;
	HICON iconMain;
	HBITMAP bRefresh, bCheck, bUncheck, bArrowUp, bArrowDown, bAbout;
	bool changes;

	static INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnBtnRefresh(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitIcons();
	void FreeIcons();
public:
	DialogMain(HINSTANCE hInst);
	~DialogMain(void);
	WPARAM run();
};

#endif
