#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
namespace Protection
{
	extern bool checkdebug();
	extern inline void ErasePEHeaderFromMemory();
	extern void ProctectTricks();
	extern 	std::string hwid();
	extern void toClipboard(const char* output);
	extern std::string GetUrlData(std::string url);
	extern std::string encrypt(const std::string& str_in, const std::string& key, const std::string& iv);
	extern std::string decrypt(const std::string& str_in, const std::string& key, const std::string& iv);
}