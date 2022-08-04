#include "includes.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	static HINSTANCE originalCryptBaseHandle;
	static HMODULE originalBCryptHandle;

	char* fullPath = nullptr;
	FARPROC originalBCryptVerifySignature = nullptr;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

#if _DEBUG
		AllocConsole();
		freopen("CON", "w", stdout);
#endif

		if (MH_Initialize() != MH_OK)
		{
			std::cout << "MiniHook could not be initialized!" << std::endl;
			return -1;
		}

		fullPath = (char*)malloc(MAX_PATH);
		if (!ExpandEnvironmentStringsA("%WinDir%\\System32\\CryptBase.dll", fullPath, MAX_PATH))
		{
			std::cout << "Could not expand path (CryptBase)..." << std::endl;
			return -1;
		}

		std::cout << "Original CryptBase.dll located at: " << fullPath << std::endl;

		originalCryptBaseHandle = LoadLibraryA(fullPath);

		if (!originalCryptBaseHandle)
		{
			std::cout << "Could not load original CryptBase.dll!" << std::endl;
			return -1;
		}

		std::cout << "Successfully loaded original CryptBase.dll" << std::endl;

		func01 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction001");
		func02 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction002");
		func03 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction003");
		func04 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction004");
		func05 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction005");
		func28 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction028");
		func29 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction029");
		func34 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction034");
		func36 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction036");
		func40 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction040");
		func41 = (int (*)(void))GetProcAddress(originalCryptBaseHandle, "SystemFunction041");

		std::cout << "Trying to load original BCrypt.dll" << std::endl;

		if (!ExpandEnvironmentStringsA("%WinDir%\\System32\\bcrypt.dll", fullPath, MAX_PATH))
		{
			std::cout << "Could not expand path (BCrypt)..." << std::endl;
			return -1;
		}

		std::cout << "Original BCrypt.dll located at: " << fullPath << std::endl;

		originalBCryptHandle = LoadLibraryA(fullPath);
		free(fullPath);

		if (!originalBCryptHandle)
		{
			std::cout << "Could not load original BCrypt.dll!" << std::endl;
			return -1;
		}

		std::cout << "Successfully loaded original BCrypt.dll" << std::endl;

		originalBCryptVerifySignature = GetProcAddress(originalBCryptHandle, "BCryptVerifySignature");

		SYSTEM_INFO _info;
		GetSystemInfo(&_info);

		std::cout << "Page size: " << _info.dwPageSize << std::endl;

		DWORD old;

		if (VirtualProtect(originalBCryptVerifySignature, _info.dwPageSize, PAGE_EXECUTE_READWRITE, &old))
		{
			std::cout << "Memory unprotected..." << std::endl;

			if (!MH_CreateHook(originalBCryptVerifySignature, PatchedBCryptVerifySignature, (LPVOID*)originalBCrypt) == MH_OK)
			{
				std::cout << "Could not create hook for BCryptVerifySignature!" << std::endl;
				return -1;
			}

			std::cout << "Hooked BCryptVerifySignature to: " << &PatchedBCryptVerifySignature << " original: " << &originalBCrypt << std::endl;

			if (MH_EnableHook(originalBCryptVerifySignature) != MH_OK)
			{
				std::cout << "Could not enable BCryptVerifySignature hook!" << std::endl;
				return -1;
			}

			std::cout << "Enabled hooks..." << std::endl;
			return TRUE;
		}

		return TRUE;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary(originalCryptBaseHandle);
		FreeLibrary(originalBCryptHandle);
		return TRUE;
	}

	return TRUE;
}

EXPORT_C int SystemFunction001()
{
	return func01();
}

EXPORT_C int SystemFunction002()
{
	return func02();
}

EXPORT_C int SystemFunction003()
{
	return func03();
}

EXPORT_C int SystemFunction004()
{
	return func04();
}

EXPORT_C int SystemFunction005()
{
	return func05();
}

EXPORT_C int SystemFunction028()
{
	return func28();
}

EXPORT_C int SystemFunction029()
{
	return func29();
}

EXPORT_C int SystemFunction034()
{
	return func34();
}

EXPORT_C int SystemFunction036()
{
	return func36();
}

EXPORT_C int SystemFunction040()
{
	return func40();
}

EXPORT_C int SystemFunction041()
{
	return func41();
}

//#pragma comment(linker, "/export:SystemFunction001=CryptBase.SystemFunction001")
//
//#pragma comment(linker, "/export:SystemFunction002=CryptBase.SystemFunction002")
//
//#pragma comment(linker, "/export:SystemFunction003=CryptBase.SystemFunction003")
//
//#pragma comment(linker, "/export:SystemFunction004=CryptBase.SystemFunction004")
//
//#pragma comment(linker, "/export:SystemFunction005=CryptBase.SystemFunction005")
//
//#pragma comment(linker, "/export:SystemFunction028=CryptBase.SystemFunction028")
//
//#pragma comment(linker, "/export:SystemFunction029=CryptBase.SystemFunction029")
//
//#pragma comment(linker, "/export:SystemFunction034=CryptBase.SystemFunction034")
//
//#pragma comment(linker, "/export:SystemFunction036=CryptBase.SystemFunction036")
//
//#pragma comment(linker, "/export:SystemFunction040=CryptBase.SystemFunction040")
//
//#pragma comment(linker, "/export:SystemFunction041=CryptBase.SystemFunction041")