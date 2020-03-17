#include<Siv3D.hpp>
using namespace std;

//極座標の角度を変化させるのに使用。5乗がいい感じ。
double x5(double x)
{
	return pow(x, 5);
}

void Main()
{
	//4種類のアニメーションを定義。それぞれ円の数は(2 , 5, 10, 50)。
	vector<vector<Circle>> c(4, vector<Circle>());
	c[0].resize(2);
	c[1].resize(5);
	c[2].resize(10);
	c[3].resize(50);

	//基準となる位置を決める。
	OffsetCircular pos(Vec2(200, 150), 100, 0);

	//極座標の角度を決定させるのに使用する変数。
	double t = 0;

	//文字フォントを定義。Processingと似ている。
	Font text(30, Typeface::Bold);

	//各円の位置と半径を指定。
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < c[i].size(); j++)
		{
			//4ブロックにわけたい。左上、右上、左下、右下の順になるように。
			pos.setCenter(200 + 400 * (i % 2), 150 + 300 * (i > 1));
			c[i][j].setCenter(pos);
			c[i][j].setR(25);
		}

	while (System::Update())
	{
		//円の位置を更新。それぞれの円について、一つ先の円の位置で再設定する。
		for (int i = 0; i < 4; i++)
			for (int j = c[i].size() - 1; j > 0; j--)
				c[i][j].setCenter(c[i][j - 1].center);

		pos.theta = x5(t);	//基準となる角度はこれ
		t += 0.02;			//円の回転速度に関わる。0.02あたりがちょうどよい。

		//各アニメーションについて、基準となる円(0番目)の位置を更新。
		for (auto i : step(4))
		{
			pos.setCenter(200 + 400 * (i % 2), 150 + 300 * (i > 1));
			c[i][0].setCenter(pos);
		}

		//各アニメーションの中心に円の数を表示。
		text(ToString(2)).draw(Arg::center(200, 150));
		text(ToString(5)).draw(Arg::center(600, 150));
		text(ToString(10)).draw(Arg::center(200, 450));
		text(ToString(50)).draw(Arg::center(600, 450));

		//円を表示。
		for (auto i : c)
		{
			for (auto j : i)
				j.draw();
		}

		//角度は[-PI PI]としたいので、tの値を調整
		if (pow(Math::Pi, 1.0 / 5.0) < t)
			t = -1 * pow(Math::Pi, 1.0 / 5.0);
	}

	return;
}