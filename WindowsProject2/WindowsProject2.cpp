// WindowsProject2.cpp : C++GUIサンプル Copyright (C) 2023 https://www.youtube.com/@ProgrammerCpp
#define _CRT_RAND_S
#include <Windows.h>
#include "targetver.h"
#include "Resource.h"
#include <sstream>
#include <stdexcept>

static const struct {
	char 記号;
	int (*計算)(int a, int b);
} 演算[] =
{ {'+', [](int a, int b) { return a + b; }}
, {'-', [](int a, int b) { return a - b; }}
, {'*', [](int a, int b) { return a * b; }}
};
class formula {
	int a;
	int b;
	int c;
public:
	formula
	( int a
	, int b
	, int c
	)
		: a(a)
		, b(b)
		, c(c)
	{
	}
	std::string to_string() const
	{
		return (std::ostringstream() << a << ' ' << 演算[c].記号 << ' ' << b << " = ").str();
	}
	int 計算結果() const noexcept
	{
		return (*演算[c].計算)(a, b);
	}
};
void 問題設定(HWND hDlg)
{
	const auto 乱数 = [](int 最小, int 最大)
	{
		unsigned n;
		const int err = rand_s(&n);
		if (err)
			throw std::runtime_error("rand_s関数が失敗しました。");
		else
			return static_cast<int>((1. + 最大 - 最小) * n / (1. + UINT_MAX) + 最小);
	};
	const formula 新しい式
		( 乱数(10, 99                )
		, 乱数(10, 99                )
		, 乱数( 0, _countof(演算) - 1)
		);
	SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, "答えを入力してください。");
	SetDlgItemTextA(hDlg, IDC_STATIC_FORMULA, 新しい式.to_string().c_str());
	SetPropA(hDlg, "計算結果", HANDLE(static_cast<INT_PTR>(新しい式.計算結果())));
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT1), true);
	SetDlgItemTextA(hDlg, IDOK, "入力");
	SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
}
void 結果表示(HWND hDlg)
{
	BOOL translated;
	const int 入力値 = GetDlgItemInt(hDlg, IDC_EDIT1, &translated, true);
	if (translated) {
		const int 計算結果 = static_cast<int>(INT_PTR(GetPropA(hDlg, "計算結果")));
		if (入力値 == 計算結果)
			SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, "正解です。");
		else
			SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, (std::ostringstream() << "不正解です。答えは " << 計算結果 << " です。").str().c_str());
	}
	else
		SetDlgItemTextA(hDlg, IDC_STATIC_MESSAGE, "数値が入力されませんでした。");
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT1), false);
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
		return false;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			if (IsWindowEnabled(GetDlgItem(hDlg, IDC_EDIT1)))
				結果表示(hDlg);
			else
				問題設定(hDlg);
			return true;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		default:
			return false;
		}
	default:
		return false;
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
	UNREFERENCED_PARAMETER(lpCmdLine    );
	UNREFERENCED_PARAMETER(nCmdShow     );
	/*WINUSERAPI INT_PTR WINAPI*/DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */nullptr
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc
	, /*_In_     LPARAM    dwInitParam   */0
	);
}
