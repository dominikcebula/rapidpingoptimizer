/*
 * RapidPingOptimizer
 *
 * Dominik Cebula
 * dominikcebula@gmail.com
 *
 * Licensed under GNU General Public License v2
 *
 */

#ifndef _REGISTRYWRAPPER_H_
#define _REGISTRYWRAPPER_H_

#include <Windows.h>
#include <string>
#include <vector>

using namespace std;

#define REGBUFFSIZE 512

typedef vector<string> KeyList;
typedef KeyList* PKeyList;

class RegistryException : public exception {
private:
	const char *desc;
public:
	RegistryException(const char* desc);
	virtual const char* what() const throw();
};

class RegistryWrapper
{
private:
	HKEY key;
	HKEY skey;
	string subkey;
public:
	RegistryWrapper(HKEY key, string subkey);
	~RegistryWrapper(void);

	void Open();
	void Close();
	PKeyList GetKeyList();
	void SetVal(string field, DWORD val);
	string GetVal(string val);
};

#endif
