/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#ifndef _LISTVIEWINTERFACES_H_
#define _LISTVIEWINTERFACES_H_

#include <Windows.h>

#define KEY_DESCRIPTIONS "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\NetworkCards\\"
#define ListViewWarning WrnBox("Failed to load network interfaces list.")

class ListViewInterfaces
{
private:
	HWND hDialog;
	HWND hList;
public:
	ListViewInterfaces(HWND hDialog);

	void Refresh(void);
	void SelectAll(void);
	void UnselectAll(void);
	void optimize(DWORD onoff);
};

#endif
