// WindowsProject3.cpp : C言語GUIサンプル2 Copyright (C) 2023 https://www.youtube.com/@ProgrammerCpp
#include <Windows.h>
#include "targetver.h"
#include "Resource.h"
#include <math.h>

BOOL 入力値取得
( _In_  HWND      hDlg      
, _In_  int       nIDDlgItem
, _Out_ double  * 入力値    
)
{
	char buf[256];
	if (GetDlgItemTextA(hDlg, nIDDlgItem, buf, sizeof buf)) {
		char* end;
		*入力値 = strtod(buf, &end);
		return end > buf;
	}
	else {
		*入力値 = 0;
		return FALSE;
	}
}
enum {
#define	演算子の記号と名前(記号, 名前) 名前,
#include "../ConsoleApplication2/演算子の記号と名前.h"
#undef	演算子の記号と名前
};
BOOL 演算子推定(HWND hDlg)
{
	double a, b, c;
	if (入力値取得(hDlg, IDC_EDIT1, &a)
	&&  入力値取得(hDlg, IDC_EDIT2, &b)
	&&  入力値取得(hDlg, IDC_EDIT3, &c)
	) {
		int f = 0;
		if (          a + b  == c) f |= 1 << 加算  ;
		if (          a - b  == c) f |= 1 << 減算  ;
		if (          a * b  == c) f |= 1 << 乗算  ;
		if (b &&      a / b  == c) f |= 1 << 除算  ;
		if (b && fmod(a,  b) == c) f |= 1 << 剰余算;
		if (f) {
			static const char 演算子記号列[] = {
#define	演算子の記号と名前(記号, 名前) 記号,
#include "../ConsoleApplication2/演算子の記号と名前.h"
#undef	演算子の記号と名前
				'\0'
			};
			char s[sizeof 演算子記号列], * p = s;
			for (int i = 0;; ++i) {
				const char ch = 演算子記号列[i];
				if (ch == '\0')
					break;
				if (f & (1 << i))
					*p++ = ch;
			}
			*p = '\0';
			SetDlgItemTextA(hDlg, IDC_STATIC_OPERATORS, s);
		}
		else
			SetDlgItemTextA(hDlg, IDC_STATIC_OPERATORS, "?");
		return TRUE;
	}
	else
		return FALSE;
}

INT_PTR CALLBACK DialogProc
( HWND   hDlg   
, UINT   message
, WPARAM wParam 
, LPARAM lParam 
)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		case IDC_EDIT1:
		case IDC_EDIT2:
		case IDC_EDIT3:
			if (HIWORD(wParam) == EN_CHANGE) {
				if (!演算子推定(hDlg))
					SetDlgItemTextA(hDlg, IDC_STATIC_OPERATORS, "");
			}
			return TRUE;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
}
int APIENTRY wWinMain
( _In_     HINSTANCE   hInstance    
, _In_opt_ HINSTANCE   hPrevInstance
, _In_     LPWSTR      lpCmdLine    
, _In_     int         nCmdShow     
)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	/*WINUSERAPI INT_PTR WINAPI*/DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */NULL
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc
	, /*_In_     LPARAM    dwInitParam   */0
	);
}
