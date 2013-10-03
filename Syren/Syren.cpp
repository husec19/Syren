// Syren.cpp : Defines the entry point for the console application.
// Syren Media Player -Audio Streaming Engine- (ASE) Command Line Demo Tool
// Deniz H.A, Sept, 2013

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

typedef int (*df_playAudioFile)(LPWSTR pathToFile); 
typedef int (*df_playAudioList)(LPWSTR pathToDirectory); 

int _tmain(int argc, _TCHAR* argv[])
{
   df_playAudioFile playAudioFile;
   df_playAudioList playAudioList;
   HINSTANCE syrenase;
   LPWSTR *szArgList;
   int nArgs;
   MSG msg;
   bool playFlag = false;  

   ZeroMemory(&msg, sizeof(msg));

   szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);
   if(NULL == szArgList)
   {
      wprintf(L"CommandLineToArgvW failed\n");
      return 0;
   }

   if((nArgs > 1) && wcscmp(szArgList[1], L"-plist") == 0) playFlag = true;
	
   if(nArgs < 2 || (nArgs==2 && playFlag)) {

	   printf("\nSyren Media Player (ASE) Tool v1.01b, - October 2013");
	   printf("\nUsage: Syren(.exe) -plist <directory name> or single audiofile.[-.M4A, -.MP3, -.WMA]\n");	   
	   return (0);
   }
  
   // ** Load SyrenASE.DLL into process 
   syrenase = LoadLibrary((LPCWSTR)L"SyrenASE.dll");

   if(!syrenase)
       printf("*** SyrenASE.DLL, library failed to load ***!\n");

   // ** Accessing to real functions via function pointer..
   // ** Now we can play the audio file or playlist with functions residing in SyrenASE.DLL
   if(!playFlag) {
       playAudioFile = (df_playAudioFile) GetProcAddress(syrenase,"syrenPlayAudioFile");
       playAudioFile(szArgList[1]);
   }
   else {
       playAudioList = (df_playAudioList) GetProcAddress(syrenase,"syrenPlayAudioList");
       playAudioList(szArgList[2]);
   }

   // thread run Loop 
   while (GetMessage(&msg, NULL, 0, 0)) {
           
	   TranslateMessage(&msg);
       DispatchMessage(&msg);
   }

   LocalFree(szArgList);

	return (0);
}

