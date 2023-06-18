//Visual Studio 2005, 2008, 2010, 2012, 2013, 2015, 2017, 2019, 2022用サンプル Copyright (C) 2023 https://www.youtube.com/@ProgrammerCpp
#define _CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
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
int main()
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
	puts("答えを入力してください。");
	printf("%d %c %d = ", a, 演算[c].記号, b);
	const int 計算結果 = (*演算[c].計算)(a, b);
	int 入力値;
	if (scanf_s("%d", &入力値) == 1) {
		if (入力値 == 計算結果)
			puts("正解です。");
		else
			printf("不正解です。答えは %d です。\n", 計算結果);
	}
	else {
		fprintf(stderr, "数値が入力されませんでした。\n");
		exit(EXIT_FAILURE);
	}
}
/*
https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q12281607027
1252022072さん

2023/6/17 22:03

1回答

乱数を使って2桁の整数(10～99)を二つ作り，それらを用いた演算を出題するプログラムをF01-1作成せよ．ただし演算は足し算，引き算，
かけ算の三種類から乱数を使ってランダムに選ばれるものとする．また乱数で作った0，1，2をそれぞれ足し算，引き算，かけ算に割り当てる.
実行例1：出題される問題は毎回変わる，正解(この場合は「12」)を入力した場合
$ ./F01-1
答えを入力してください。
95 - 83 = 12
正解です。


実行例2：間違えた場合
$ ./F01-1
答えを入力してください。
86 * 61 = 5236


このようなプログラムを作りたいのですがどうやって作ればいいでしょうか？
*/
