
#pragma once


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GAPI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GAPI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GAPI_EXPORTS
	#define GAPI_API __declspec(dllexport)
#else
	#define GAPI_API __declspec(dllimport)
#endif


enum GAPI_API ReturnCode
{
    RC_OK = 0,
    RC_CommandSyntaxError,
    RC_ParameterError,
    RC_ValueError,
    RC_NotImplemented,
};
