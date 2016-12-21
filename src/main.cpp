/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#include <Windows.h>
#include <Commctrl.h>
#include "DialogMain.h"
#include "common.h"

#ifdef _DEBUG
	#include <crtdbg.h>
#endif

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
	WPARAM ret=0;
	{
		INITCOMMONCONTROLSEX controls;
		controls.dwSize=sizeof(INITCOMMONCONTROLSEX);
		controls.dwICC=ICC_LISTVIEW_CLASSES;
		InitCommonControlsEx(&controls);

		DialogMain dialog(hThisInstance);
		ret=dialog.run();
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return ret;
}
