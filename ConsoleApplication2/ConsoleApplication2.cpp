#include <stdio.h>
#include <math.h>

enum {
#define	演算子の記号と名前(記号, 名前) 名前,
#include "演算子の記号と名前.h"
#undef	演算子の記号と名前
};
int どのような計算をしたのか推理(double a, double b, double c)
{
	int f = 0;
	if (          a + b  == c) f |= 1 << 加算  ;
	if (          a - b  == c) f |= 1 << 減算  ;
	if (          a * b  == c) f |= 1 << 乗算  ;
	if (b &&      a / b  == c) f |= 1 << 除算  ;
	if (b && fmod(a,  b) == c) f |= 1 << 剰余算;
	return f;
}
int main()
{
	double a, b, c;
	while (scanf_s("%lf%lf%lf", &a, &b, &c) == 3) {
		const int f = どのような計算をしたのか推理(a, b, c);
		if (f) {
			static const char 演算子記号列[] = {
#define	演算子の記号と名前(記号, 名前) 記号,
#include "演算子の記号と名前.h"
#undef	演算子の記号と名前
				'\0'
			};
			for (int i = 0;;++i) {
				const char ch = 演算子記号列[i];
				if (ch == '\0')
					break;
				if (f & (1 << i))
					putchar(ch);
			}
			putchar('\n');
		}
		else
			printf("?\n");
	}
}
/*
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q11281548371
1152019011さん

2023/6/16 18:42

5回答

大学のc言語の課題です。
どうしてもわからなかったので教えていただきたいです。

利用者から二つの値と計算結果を受け取りどのような計算をしたのか特定するプログラムを作成せよ。
なお、計算は加算、減算、乗算、除算、剰余算に対応すること
入力と出力の例：
入力 → 出力
・４ ３ １２ → *
・ー４ ３ ー１２ → *
・４ ３ ７ → +
・４ ３ １ → ー
・３ ４ ー１ → ー
・４ ３ １ → ％

・２.４ ２ ４.８ → *
・４ ３ ２８ → ？

C言語関連・114閲覧
*/
