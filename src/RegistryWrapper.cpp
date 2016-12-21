/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#include "RegistryWrapper.h"
#include "common.h"

RegistryException::RegistryException(const char* desc)
{
	this->desc=desc;
}

const char* RegistryException::what() const throw()
{
	return this->desc;
}

RegistryWrapper::RegistryWrapper(HKEY key, string subkey)
{
	this->key=key;
	this->subkey=subkey;
}

RegistryWrapper::~RegistryWrapper(void)
{
}

void RegistryWrapper::Open()
{
	if (RegOpenKey(key, subkey.c_str(), &skey)!=ERROR_SUCCESS)
		throw RegistryException("Failed to open registry key");
}

void RegistryWrapper::Close()
{
	RegCloseKey(skey);
}

PKeyList RegistryWrapper::GetKeyList()
{
	PKeyList list=new KeyList();
	CHAR buff[REGBUFFSIZE];
	LONG st;
	int idx=0;

	while ((st=RegEnumKey(skey, idx, buff, REGBUFFSIZE))==ERROR_SUCCESS) {
		string str(subkey);
		str.append(buff);
		str.append("\\");
		list->push_back(str);
		++idx;
	}

	if (st==ERROR_SUCCESS || st==ERROR_NO_MORE_ITEMS)
		return list;
	else {
		list->clear();
		delete list;
		throw RegistryException("Failed to read subkey list");
	}
}

void RegistryWrapper::SetVal(string field, DWORD val)
{
	if (RegSetValueEx(skey, field.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&val), sizeof(val))!=ERROR_SUCCESS)
		throw RegistryException("Failed to set value");
}

string RegistryWrapper::GetVal(string val)
{
	DWORD size=REGBUFFSIZE;
	CHAR buff[REGBUFFSIZE];
	if (RegQueryValueEx(skey, val.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(buff), &size)!=ERROR_SUCCESS)
		throw RegistryException("Failed to get value");
	else
		return string(buff);
}
