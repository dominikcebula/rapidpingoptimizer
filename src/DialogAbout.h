/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#ifndef _DIALOG_ABOUT_H_
#define _DIALOG_ABOUT_H_

#include <Windows.h>

class DialogAbout
{
private:
	HINSTANCE hInst;
	HWND hParent;
public:
	DialogAbout(HINSTANCE hInst, HWND hParent);

	INT_PTR ShowModal();
	static INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif


