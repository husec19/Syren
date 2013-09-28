// Syren.cpp : Defines the entry point for the console application.
// Syren Media Player -Audio Streaming Engine- (ASE) Command Line Test Tool
// Deniz H.A, Sept, 2013

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

typedef int (*df_playAudioFile)(LPWSTR); 

int _tmain(int argc, _TCHAR* argv[])
{
   df_playAudioFile playAudioFile;
   HINSTANCE syrenase;
   LPWSTR *szArgList;
   int nArgs;
   MSG msg;
 
   szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);
   if( NULL == szArgList )
   {
      wprintf(L"CommandLineToArgvW failed\n");
      return 0;
   }

   if(nArgs < 2) {

	   printf("\nSyren Media Player ASE Test Tool v1.0b - (c) Alex G, Sept 2013");
	   printf("\nUsage: Syren(.exe) audiofile.[wma, mp3] \n");

	   return (0);
   }

   // ** Load SyrenASE.DLL into process 
   syrenase = LoadLibrary((LPCWSTR)L"SyrenASE.dll");

   if (syrenase != 0);
 //  printf("library loaded!\n");
   else
   printf("*** SyrenASE.DLL, library failed to load ***!\n");

   // ** Accessing the real function via function pointer..  
   playAudioFile = (df_playAudioFile) GetProcAddress(syrenase,"syrenPlayAudioFile");

   // ** Now we can play the audio file with syrenPlayAudioFile function which resides in SyrenASE.DLL
   playAudioFile((LPWSTR)szArgList[1]);

   ZeroMemory(&msg, sizeof(msg));

   // process Run Loop 
   while (GetMessage(&msg, NULL, 0, 0))
   {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
   }

   LocalFree(szArgList);

	return 0;
}

