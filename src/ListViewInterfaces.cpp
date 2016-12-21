/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#include "ListViewInterfaces.h"
#include <Commctrl.h>
#include <iostream>
#include <sstream>
#include <string>
#include "resource.h"
#include "common.h"
#include "RegistryWrapper.h"
#include "NetworkOptimizer.h"

using namespace std;

ListViewInterfaces::ListViewInterfaces(HWND hDialog)
{
	this->hDialog=hDialog;
	hList=GetDlgItem(this->hDialog, IDC_IF_LIST);
	ListView_SetExtendedListViewStyle(hList, LVS_EX_CHECKBOXES);

	LVCOLUMN col;

	memset(&col, 0, sizeof(col));
	col.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;
	col.fmt=LVCFMT_LEFT;
	col.cx=450;
	col.pszText=const_cast<CHAR*>("Network interface name\0");
	col.cchTextMax=17;
	ListView_InsertColumn(hList, 0, &col);

	col.cx=160;
	col.pszText=const_cast<CHAR*>("Status\0");
	col.cchTextMax=7;
	ListView_InsertColumn(hList, 1, &col);

	col.cx=240;
	col.pszText=const_cast<CHAR*>("GUID\0");
	col.cchTextMax=5;
	ListView_InsertColumn(hList, 2, &col);

	this->Refresh();
}

void ListViewInterfaces::optimize(DWORD onoff)
{
	int count=ListView_GetItemCount(hList)-1;
	CHAR buff[BUFFSIZE];
	while (count>=0) {
		if (ListView_GetCheckState(hList, count)==false) {
			--count;
			continue;
		}

		ListView_GetItemText(hList, count, 2, reinterpret_cast<LPSTR>(buff), BUFFSIZE);
		string guid(buff);
		NetworkOptimizer opt(guid);
		opt.optimize(onoff);

		--count;
	}
}

void ListViewInterfaces::SelectAll(void)
{
	int count=ListView_GetItemCount(hList);
	while (count>=0)
		ListView_SetCheckState(hList, count--, true);
}

void ListViewInterfaces::UnselectAll(void)
{
	int count=ListView_GetItemCount(hList);
	while (count>=0)
		ListView_SetCheckState(hList, count--, false);
}

void ListViewInterfaces::Refresh(void)
{
	ListView_DeleteAllItems(hList);

	RegistryWrapper reg(HKEY_LOCAL_MACHINE, KEY_DESCRIPTIONS);
	string val;
	LVITEM item;

	try {
		reg.Open();
		PKeyList list=reg.GetKeyList();
		for (KeyList::size_type i=0;i<list->size();i++) {
			RegistryWrapper subkey(HKEY_LOCAL_MACHINE, (*list)[i].c_str());
			subkey.Open();

			val=subkey.GetVal("Description");
			memset(&item, 0, sizeof(item));
			item.mask=LVIF_TEXT | LVCF_SUBITEM;
			item.iItem=i;
			item.iSubItem=0;
			item.pszText=const_cast<LPSTR>(val.c_str());
			item.cchTextMax=val.length();
			ListView_InsertItem(hList, &item);

			val=subkey.GetVal("ServiceName");

			NetworkOptimizer optimizer(val);
			if (optimizer.optimized())
				ListView_SetItemText(hList, i, 1, const_cast<CHAR*>("Optimization Enabled\0"))
			else
				ListView_SetItemText(hList, i, 1, const_cast<CHAR*>("Optimization Disabled\0"));


			ListView_SetItemText(hList, i, 2, const_cast<CHAR*>(val.c_str()));

			subkey.Close();
		}

		list->clear();
		delete list;
		reg.Close();
	}
	catch (exception& e) {
		WrnBox(e.what());
	}
}
