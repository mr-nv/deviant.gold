#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include "Protection.h"
#include "Injector.h"
#include "D:\lib\cryptopp\osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include "D:\lib\cryptopp\cryptlib.h"
using CryptoPP::Exception;
#include "Xor.h"
int main()
{
	//Protection::ErasePEHeaderFromMemory();
	Protection::ProctectTricks();
	if (Protection::checkdebug())
		exit(-1);
	std::string hwidotvet;
	std::string cheat;
	SetConsoleTitleA("MultiPurpose loader ");
	std::string hwid = Protection::hwid().c_str();
	std::cout << "You want copy hwid? y/n " << '\n';
	std::cin >> hwidotvet;
	if (hwidotvet == "y")
		Protection::toClipboard(hwid.c_str());
	std::cout << "Select Cheat:" << '\n';
	printf(("1 - CS:GO[PAID] \n"));
	printf(("2 - CS:GO[FREE] \n"));
	std::cin >> cheat;
	std::string key = /*48160653375770156294656980818014*/XorStr<0xDF, 33, 0xD35F431D>("\xEB\xD8\xD0\xD4\xD3\xD2\xD0\xD5\xD4\xDF\xDC\xDD\xDC\xDC\xDC\xDB\xD9\xC2\xC8\xC6\xC5\xC1\xC3\xCF\xCF\xC8\xC1\xCB\xC3\xCC\xCC\xCA" + 0xD35F431D).s;
	std::string iv = /*9727089038717736*/XorStr<0xCC, 17, 0xA9DEDD5>("\xF5\xFA\xFC\xF8\xE0\xE9\xEB\xE3\xE7\xED\xE1\xE6\xEF\xEE\xE9\xED" + 0xA9DEDD5).s;
	std::string otvet = Protection::GetUrlData(/*/loader/login.php?hwid=*/XorStr<0x3E, 24, 0x7F6CA5>("\x11\x53\x2F\x20\x26\x26\x36\x6A\x2A\x28\x2F\x20\x24\x65\x3C\x25\x3E\x70\x38\x26\x3B\x37\x69" + 0x7F6CA5).s + hwid + /*&cheat=*/XorStr<0xBE, 8, 0xBA4E9AC3>("\x98\xDC\xA8\xA4\xA3\xB7\xF9" + 0xBA4E9AC3).s + "1");
	std::string otvet_decrypted = Protection::decrypt(otvet, key, iv);
	std::string temp(getenv("TEMP"));
	typedef int * (*MyDownloadToUrl)(void*, const char*, const char*, DWORD, void*);
	HINSTANCE LibHnd = LoadLibrary("Urlmon.dll");
	MyDownloadToUrl MyDownloadFunction = (MyDownloadToUrl)GetProcAddress(LibHnd, "URLDownloadToFileA");
	if (cheat == "2")
	{
		temp += "\\";
		temp += "discordmp.dll";
		MyDownloadFunction(0, "http://multipurpose.pro/free.dll", temp.c_str(), 0, 0);
		inject(temp.c_str());
		std::cout << "Successful connect\n";

	}
	else if (cheat == "1") {
		if (otvet_decrypted == /*user-active-true*/XorStr<0x4E, 17, 0x1BFEF4B9>("\x3B\x3C\x35\x23\x7F\x32\x37\x21\x3F\x21\x3D\x74\x2E\x29\x29\x38" + 0x1BFEF4B9).s) {
			std::cout << /*You are authenticated!*/XorStr<0xC5, 23, 0xE3A451B5>("\x9C\xA9\xB2\xE8\xA8\xB8\xAE\xEC\xAC\xBB\xBB\xB8\xB4\xBC\xA7\xBD\xB6\xB7\xA3\xBD\xBD\xFB" + 0xE3A451B5).s << '\n';
			temp += "\\";
			temp += "discordmp.dll";
			MyDownloadFunction(0,  /*http://multipurpose.pro/loader/notacheat.dll*/XorStr<0xE2, 45, 0x5939FCD4>("\x8A\x97\x90\x95\xDC\xC8\xC7\x84\x9F\x87\x98\x84\x9E\x9A\x82\x81\x9D\x80\x91\xDB\x86\x85\x97\xD6\x96\x94\x9D\x99\x9B\x8D\x2F\x6F\x6D\x77\x65\x66\x6E\x62\x69\x7D\x24\x6F\x60\x61" + 0x5939FCD4).s, temp.c_str(), 0, 0);
			inject(temp.c_str());

		}
		else if (otvet_decrypted == /*user-active-false*/XorStr<0x88, 18, 0xBDD28036>("\xFD\xFA\xEF\xF9\xA1\xEC\xED\xFB\xF9\xE7\xF7\xBE\xF2\xF4\xFA\xE4\xFD" + 0xBDD28036).s) {
			std::cout << /*Failed Authencating!*/XorStr<0xC, 21, 0xC24967DB>("\x4A\x6C\x67\x63\x75\x75\x32\x52\x61\x61\x7E\x72\x76\x7A\x7B\x6F\x75\x73\x79\x3E" + 0xC24967DB).s << '\n';
		}
		else if (otvet_decrypted == /*user-active-banned*/XorStr<0xE9, 19, 0x14F9D2F1>("\x9C\x99\x8E\x9E\xC0\x8F\x8C\x84\x98\x84\x96\xD9\x97\x97\x99\x96\x9C\x9E" + 0x14F9D2F1).s) {
			std::cout << /*Your HWID banned!*/XorStr<0x41, 18, 0x44123AAE>("\x18\x2D\x36\x36\x65\xE\x10\x1\xD\x6A\x29\x2D\x23\x20\x2A\x34\x70" + 0x44123AAE).s << '\n';
		}
		else
			std::cout << /*Failed Authencating!*/XorStr<0xED, 21, 0x9990CE7>("\xAB\x8F\x86\x9C\x94\x96\xD3\xB5\x80\x82\x9F\x9D\x97\x99\x9A\x88\x94\x90\x98\x21" + 0x9990CE7).s << '\n';
	}
	Sleep(3000);
	exit(0);
	return 0;
}
