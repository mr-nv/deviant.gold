#include "Protection.h"
#include <Tlhelp32.h>
#include <algorithm>
#include <vector>
#include "D:\lib\cryptopp\osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include "D:\lib\cryptopp\cryptlib.h"
using CryptoPP::Exception;
#include "D:\lib\cryptopp\aes.h"
#include "D:\lib\cryptopp\modes.h"
#include <winsock.h>
#include <wininet.h>
#include "D:\lib\cryptopp\base64.h"
using CryptoPP::Base64Decoder;
using CryptoPP::Base64Encoder;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;
#pragma comment(lib, "Wininet")
#include "md5.h"
namespace Protection
{

	std::string GetUrlData(std::string url)
	{
		std::string request_data = "";

		HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

		if (!hIntSession)
		{
			return request_data;
		}

		HINTERNET hHttpSession = InternetConnectA(hIntSession, "multipurpose.pro", 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);

		if (!hHttpSession)
		{
			return request_data;
		}

		HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str()
			, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

		if (!hHttpSession)
		{
			return request_data;
		}

	const char* szHeaders = "Content-Type: text/html\r\nUser-Agent: MultiPurpose";
		char szRequest[1024] = { 0 };

		if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szRequest, strlen(szRequest)))
		{
			return request_data;
		}

		CHAR szBuffer[1024] = { 0 };
		DWORD dwRead = 0;

		while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
		{
			request_data.append(szBuffer, dwRead);
		}

		InternetCloseHandle(hHttpRequest);
		InternetCloseHandle(hHttpSession);
		InternetCloseHandle(hIntSession);

		return request_data;
	}
	DWORD GetVolumeID()
	{
		DWORD VolumeSerialNumber;

		BOOL GetVolumeInformationFlag = GetVolumeInformationA(
			"c:\\",
			0,
			0,
			&VolumeSerialNumber,
			0,
			0,
			0,
			0
		);

		if (GetVolumeInformationFlag)
			return VolumeSerialNumber;

		return 0;
	}
	std::string hwid()
	{
		std::string localhwid;
		HW_PROFILE_INFO hwProfileInfo;

		if (GetCurrentHwProfile(&hwProfileInfo))
			localhwid += hwProfileInfo.szHwProfileGuid;

		localhwid += "multipurpose.";
		int regs[4] = { 0 };
		char vendor[13];
		__cpuid(regs, 0);              // mov eax,0; cpuid
		memcpy(vendor, &regs[1], 4);   // copy EBX
		memcpy(vendor + 4, &regs[2], 4); // copy ECX
		memcpy(vendor + 8, &regs[3], 4); // copy EDX
		vendor[12] = '\0';
		localhwid += vendor;
		localhwid += std::to_string(GetVolumeID());
		return md5(localhwid);
	}
	void toClipboard(const char* output) {

		const size_t len = strlen(output) + 1;
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem), output, len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
	}
	BOOL WINAPI IsDebug()
	{
		HANDLE hProcess = NULL;
		PROCESSENTRY32 Pe32 = { 0 };
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}
		Pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hProcessSnap, &Pe32))
		{
			do
			{
				if (_stricmp("csrss.exe", Pe32.szExeFile) == 0)
				{
					HANDLE hProcess = OpenProcess(
						PROCESS_ALL_ACCESS,
						FALSE,
						Pe32.th32ProcessID
					);

					if (hProcess)
					{
						return TRUE;
					}
					else
					{
						return FALSE;
					}
					CloseHandle(hProcess);
				}
			} while (Process32Next(hProcessSnap, &Pe32));
		}
		CloseHandle(hProcessSnap);
	}
	BOOL AD_CheckRemoteDebuggerPresent()
	{
		FARPROC Func_addr;
		HMODULE hModule = GetModuleHandle("kernel32.dll");

		if (hModule == INVALID_HANDLE_VALUE)
			return false;

		(FARPROC&)Func_addr = GetProcAddress(hModule, "CheckRemoteDebuggerPresent");

		if (Func_addr != NULL) {
			__asm {
				push  eax;
				push  esp;
				push  0xffffffff;
				call  Func_addr;
				test  eax, eax;
				je    choke_false;
				pop    eax;
				test  eax, eax
					je    choke_false;
				jmp    choke_true;
			}
		}

	choke_true:
		return true;

	choke_false:
		return false;
	}
	BOOL AD_PEB_IsDebugged()
	{
		__asm {
			xor eax, eax
			mov ebx, fs:[30h]
			mov al, byte ptr[ebx + 2]
		}
	}
	BOOL AD_PEB_NtGlobalFlags()
	{
		__asm {
			mov eax, fs:[30h]
			mov eax, [eax + 68h]
			and eax, 0x70
		}
	}
#pragma comment(lib,"ntdll.lib")

	extern "C" NTSTATUS NTAPI NtQueryInformationProcess(HANDLE hProcess, ULONG InfoClass, PVOID Buffer, ULONG Length, PULONG ReturnLength);

#define NtCurrentProcess() (HANDLE)-1

	void NTAPI __stdcall TLS_CALLBACK(PVOID DllHandle, DWORD dwReason, PVOID Reserved)
	{
		HANDLE DebugPort = NULL;
		if (!NtQueryInformationProcess(NtCurrentProcess(), 7, &DebugPort, sizeof(HANDLE), NULL))
		{
			if (DebugPort)
			{
				exit(-1);
			}
		}
	}

#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__tls_callback")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#endif

	EXTERN_C
#ifdef _M_X64
#pragma const_seg (".CRT$XLB")
		const
#else
#pragma data_seg (".CRT$XLB")
#endif

		PIMAGE_TLS_CALLBACK _tls_callback[] = { TLS_CALLBACK, 0 };
#pragma data_seg ()
#pragma const_seg ()
	inline bool Int2DCheck()
	{
		__try
		{
			__asm
			{
				int 0x2d
				xor eax, eax
				add eax, 2
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}

		return true;
	}

	bool IsDebuggerProcces()
	{
		return false;
	}
	bool vmcheck()
	{
		unsigned int time1 = 0;
		unsigned int time2 = 0;
		__asm
		{
			RDTSC
			MOV time1, EAX
			RDTSC
			MOV time2, EAX

		}
		if ((time2 - time1) > 100)
		{
			return true;
		}
	}
	DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
	{
		PCONTEXT ctx = ep->ContextRecord;

		ctx->Ebx = -1; // Not running VPC
		ctx->Eip += 4; // skip past the "call VPC" opcodes
		return EXCEPTION_CONTINUE_EXECUTION;
		// we can safely resume execution since we skipped faulty instruction
	}

	// High level language friendly version of IsInsideVPC()
	bool IsInsideVPC()
	{
		bool rc = false;

		__try
		{
			_asm push ebx
			_asm mov  ebx, 0 // It will stay ZERO if VPC is running
			_asm mov  eax, 1 // VPC function number

							 // call VPC 
			_asm __emit 0Fh
			_asm __emit 3Fh
			_asm __emit 07h
			_asm __emit 0Bh

			_asm test ebx, ebx
			_asm setz[rc]
				_asm pop ebx
		}
		// The except block shouldn't get triggered if VPC is running!!
		__except (IsInsideVPC_exceptionFilter(GetExceptionInformation()))
		{
		}

		return rc;
	}
	bool IsInsideVMWare()
	{
		bool rc = true;

		__try
		{
			__asm
			{
				push   edx
				push   ecx
				push   ebx

				mov    eax, 'VMXh'
				mov    ebx, 0 // any value but not the MAGIC VALUE
				mov    ecx, 10 // get VMWare version
				mov    edx, 'VX' // port number

				in     eax, dx // read port
							   // on return EAX returns the VERSION
							   cmp    ebx, 'VMXh' // is it a reply from VMWare?
							   setz[rc] // set return value

							   pop    ebx
							   pop    ecx
							   pop    edx
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			rc = false;
		}

		return rc;
	}
	void ProctectTricks()
	{
		OutputDebugString(TEXT("%s%s%s%s%s%s%s%s%s%s%s")
			TEXT("%s%s%s%s%s%s%s%s%s%s%s%s%s")
			TEXT("%s%s%s%s%s%s%s%s%s%s%s%s%s")
			TEXT("%s%s%s%s%s%s%s%s%s%s%s%s%s"));
		char str[] = { 0x09 ,0x04 ,0x19 ,0x19 ,0x31 ,0x3E ,0x26 ,0x39 ,0x15 ,0x0B ,0x24 ,0x3E ,0x23 ,0x67 ,0x2E ,0x2F ,0x28 ,0x3F ,0x2D ,0x37, 0 };
		for (int i = 0; str[i] != 0; i++)
			str[i] ^= 0x4A;
	}
	inline void ErasePEHeaderFromMemory()
	{
		DWORD OldProtect = 0;

		// Get base address of module
		char *pBaseAddr = (char*)GetModuleHandle(NULL);

		// Change memory protection
		VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
			PAGE_READWRITE, &OldProtect);

		// Erase the header
		ZeroMemory(pBaseAddr, 4096);
	}
	bool checkdebug()
	{
		SetLastError(0);
		OutputDebugStringA("Suck dick :)");
		if (IsDebuggerPresent())
			return true;
		if (GetLastError() != 0)
			return true;
		if (*(BYTE*)IsDebug == 0xCC || *(BYTE*)IsDebug == 0x64)
		{
			return true;
		}
		else if (IsDebug())
		{
			return true;
		}
		else
		{
			return false;
		}
		if (Int2DCheck())
			return true;
		if (AD_PEB_IsDebugged())
			return true;
		if (AD_PEB_NtGlobalFlags())
			return true;
		if (AD_CheckRemoteDebuggerPresent())
			return true;
		if (IsDebuggerProcces())
			return true;
		if (IsInsideVPC())
			return true;
		if (IsInsideVMWare())
			true;
		if (vmcheck())
			true;
		return false;
	}
	std::string encrypt(const std::string& str_in, const std::string& key, const std::string& iv)
	{
		std::string str_out;
		CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption encryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());

		CryptoPP::StringSource encryptor(str_in, true,
			new CryptoPP::StreamTransformationFilter(encryption,
				new CryptoPP::Base64Encoder(
					new CryptoPP::StringSink(str_out),
					false // do not append a newline
				)
			)
		);
		return str_out;
	}

	std::string decrypt(const std::string& str_in, const std::string& key, const std::string& iv)
	{
		std::string str_out;

		CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption decryption((byte*)key.c_str(), key.length(), (byte*)iv.c_str());

		CryptoPP::StringSource decryptor(str_in, true,
			new CryptoPP::Base64Decoder(
				new CryptoPP::StreamTransformationFilter(decryption,
					new CryptoPP::StringSink(str_out)
				)
			)
		);
		return str_out;
	}

}