#include <Novice.h>
#include <Vector3.h>
#include <Matrix4x4.h>
#include<assert.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3";


static const int kRowHeight = 20;
static const int kColumnWidth = 60;
//4x4の行列の数値を表示する
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + (row + 1) * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}

}
//３次元ベクトルの数値を表示する
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 TranslateMatrix;

	TranslateMatrix.m[0][0] = 1;
	TranslateMatrix.m[0][1] = 0;
	TranslateMatrix.m[0][2] = 0;
	TranslateMatrix.m[0][3] = 0;

	TranslateMatrix.m[1][0] = 0;
	TranslateMatrix.m[1][1] = 1;
	TranslateMatrix.m[1][2] = 0;
	TranslateMatrix.m[1][3] = 0;

	TranslateMatrix.m[2][0] = 0;
	TranslateMatrix.m[2][1] = 0;
	TranslateMatrix.m[2][2] = 1;
	TranslateMatrix.m[2][3] = 0;

	TranslateMatrix.m[3][0] = translate.x;
	TranslateMatrix.m[3][1] = translate.y;
	TranslateMatrix.m[3][2] = translate.z;
	TranslateMatrix.m[3][3] = 1;

	return TranslateMatrix;
};

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 	ScaleMatrix;

	ScaleMatrix.m[0][0] = scale.x;
	ScaleMatrix.m[0][1] = 0;
	ScaleMatrix.m[0][2] = 0;
	ScaleMatrix.m[0][3] = 0;

	ScaleMatrix.m[1][0] = 0;
	ScaleMatrix.m[1][1] = scale.y;
	ScaleMatrix.m[1][2] = 0;
	ScaleMatrix.m[1][3] = 0;

	ScaleMatrix.m[2][0] = 0;
	ScaleMatrix.m[2][1] = 0;
	ScaleMatrix.m[2][2] = scale.z;
	ScaleMatrix.m[2][3] = 0;

	ScaleMatrix.m[3][0] = 0;
	ScaleMatrix.m[3][1] = 0;
	ScaleMatrix.m[3][2] = 0;
	ScaleMatrix.m[3][3] = 1;

	return ScaleMatrix;
};

//3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];


	assert(w != 0.0f);//bベクトルに対して基本的な操作を行う秒列ではｗ＝０にならない
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Vector3 translate{ 4.1f,2.6f,0.8f };
		Vector3 scale{ 1.5f,5.2f,7.3f };

		//make関数
		Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
		Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);

		Vector3 point = { 2.3f,3.8f,1.4f };
		Matrix4x4 transformMatrix = {
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
		};
		Vector3 transformed = Transform(point, transformMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, kRowHeight, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, kRowHeight * 6, scaleMatrix, "scaleMatrix");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
