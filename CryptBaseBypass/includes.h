#pragma once

#include <windows.h>
#include <iostream>
#include "../vendor/MinHook/include/MinHook.h"

#define EXPORT_C extern "C" __declspec(dllexport)

///////////////////////////////////////////////
// Original CryptBase.dll functions exported //
///////////////////////////////////////////////
int (*func01)(void);
int (*func02)(void);
int (*func03)(void);
int (*func04)(void);
int (*func05)(void);
int (*func28)(void);
int (*func29)(void);
int (*func34)(void);
int (*func36)(void);
int (*func40)(void);
int (*func41)(void);
///////////////////////////////////////////////

// Original BCryptVerifySignature
int (*originalBCrypt)(void);

__int64 PatchedBCryptVerifySignature()
{
	std::cout << "Called BCryptVerifySignature..." << std::endl;
	return 0;
}