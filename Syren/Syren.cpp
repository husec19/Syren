// Syren.cpp : Defines the entry point for the console application.
// Syren Media Player -Audio Streaming Engine- (ASE) Command Line Demo Tool
// Deniz H.A, Sept, 2013

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>

typedef int (*df_openAudioFile)(LPWSTR pathToFile); 
typedef int (*df_openAudioStream)(LPWSTR url); 
typedef int (*df_openAudioPlaylist)(LPWSTR pathToDirectory); 

enum {
	   openFile = 0,
	   openPlaylist,
	   openStream
};

int _tmain(int argc, _TCHAR* argv[])
{
   df_openAudioFile playAudioFile;
   df_openAudioStream playAudioStream;
   df_openAudioPlaylist playAudioPlaylist;
   HINSTANCE syrenase;
   LPWSTR *szArgList;
   int nArgs;
   MSG msg;
   int playFlag = -1;  

   ZeroMemory(&msg, sizeof(msg));

   szArgList = CommandLineToArgvW(GetCommandLineW(), &nArgs);
   if(NULL == szArgList)
   {
      wprintf(L"CommandLineToArgvW failed\n");
      return (0);
   }

   if(nArgs < 3) {
wrongOption:
	   printf("\nSyren Media Player (ASE) Tool v1.10b, - Oct 3, 2013");
	   printf("\nUsage: Syren(.exe) -file <full pathname to file> -plist <directory> -stream <url:port>\n");
	   printf("\nOptions:\n\n");
	   printf(" -file audiofile.(-.M4A, -.MP3, -.WMA) -> exp: Syren -file bestcoast.mp3\n");
	   printf(" -plist <directory name> -> exp: Syren -plist C:\\myplaylist\n");	   
	   printf(" -stream <url> (AAC, MP3, WMA stations) -> for AAC streaming exp: Syren -stream http://208.77.21.13:19030 \n"); 	   
	   return (0);
   }

   if(!wcscmp(szArgList[1], L"-file")) playFlag = openFile;
   if(!wcscmp(szArgList[1], L"-plist")) playFlag = openPlaylist;
   if(!wcscmp(szArgList[1], L"-stream")) playFlag = openStream;

   if(playFlag == -1) goto wrongOption;
  
   // ** Load SyrenASE.DLL into process 
   syrenase = LoadLibrary((LPCWSTR)L"SyrenASE.dll");

   if(!syrenase)
       printf("*** SyrenASE.DLL was not found, library failed to load ***!\n");

   // ** Accessing to real functions via function pointer..
   // ** Now we can play the audio file or playlist with functions residing in SyrenASE.DLL
   if(playFlag == openFile) {
       playAudioFile = (df_openAudioFile) GetProcAddress(syrenase,"syrenOpenAudioFile");
       playAudioFile(szArgList[2]);
   }
   else if(playFlag == openPlaylist) {
       playAudioPlaylist = (df_openAudioPlaylist) GetProcAddress(syrenase,"syrenOpenAudioPlaylist");
       playAudioPlaylist(szArgList[2]);
   }
   else if(playFlag == openStream) {
       playAudioStream = (df_openAudioStream) GetProcAddress(syrenase,"syrenOpenAudioStream");
       playAudioStream(szArgList[2]);
   }

   // thread run Loop 
   while(GetMessage(&msg, NULL, 0, 0)) {
           
	   TranslateMessage(&msg);
       DispatchMessage(&msg);
   }

   LocalFree(szArgList);

	return (0);
}

