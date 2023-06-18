// WindowsProject1.cpp : C言語GUIサンプル Copyright (C) 2023 https://www.youtube.com/@ProgrammerCpp
#define _CRT_RAND_S
#include <Windows.h>
#include "targetver.h"
#include "Resource.h"
#include <stdio.h>

int 乱数(int 最小, int 最大)
{
	unsigned n;
	const int err = rand_s(&n);
	if (err) {
		fprintf(stderr, "rand_s関数が失敗しました。\n");
		exit(EXIT_FAILURE);
	}
	else
		return (int)((1. + 最大 - 最小) * n / (1. + UINT_MAX) + 最小);
}
int 足し算(int a, int b) { return a + b; }
int 引き算(int a, int b) { return a - b; }
int 掛け算(int a, int b) { return a * b; }
void 問題設定(HWND hDlg)
{
	static const struct {
		char 記号;
		int (*計算)(int a, int b);
	} 演算[] =
	{ {'+', 足し算}
	, {'-', 引き算}
	, {'*', 掛け算}
	};
	const int a = 乱数(10, 99);
	const int b = 乱数(10, 99);
	const int c = 乱数(0, _countof(演算) - 1);
	SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, "答えを入力してください。");
	char buf[sizeof "99 + 99 = "];
	sprintf_s(buf, sizeof buf, "%d %c %d = ", a, 演算[c].記号, b);
	SetDlgItemTextA(hDlg, IDC_STATIC_FORMULA, buf);
	SetPropA(hDlg, "計算結果", (HANDLE)(INT_PTR)(*演算[c].計算)(a, b));
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT1), TRUE);
	SetDlgItemTextA(hDlg, IDOK, "入力");
	SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
}
void 結果表示(HWND hDlg)
{
	BOOL translated;
	const int 入力値 = GetDlgItemInt(hDlg, IDC_EDIT1, &translated, TRUE);
	if (translated) {
		const int 計算結果 = (int)(INT_PTR)GetPropA(hDlg, "計算結果");
		if (入力値 == 計算結果)
			SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, "正解です。");
		else {
			char buf[sizeof "不正解です。答えは 9999 です。"];
			sprintf_s(buf, sizeof buf, "不正解です。答えは %d です。", 計算結果);
			SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, buf);
		}
	}
	else
		SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, "数値が入力されませんでした。");
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT1), FALSE);
	SetDlgItemTextA(hDlg, IDOK, "もう一度");
	SetFocus(GetDlgItem(hDlg, IDOK));
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
		問題設定(hDlg);
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			if (IsWindowEnabled(GetDlgItem(hDlg, IDC_EDIT1)))
				結果表示(hDlg);
			else
				問題設定(hDlg);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
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
