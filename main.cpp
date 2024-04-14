#include <MyMath.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_01_00";

// 1.透視投射行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

	Matrix4x4 perspectiveFovMatrix = { 0 };
	perspectiveFovMatrix.m[0][0] = (1 / aspectRatio) * (1 / tanf(fovY / 2));
	perspectiveFovMatrix.m[1][1] = (1 / tanf(fovY / 2));
	perspectiveFovMatrix.m[2][2] =
		farClip / (farClip - nearClip);
	perspectiveFovMatrix.m[2][3] = 1;
	perspectiveFovMatrix.m[3][2] =
		(-nearClip * farClip) / (farClip - nearClip);

	return perspectiveFovMatrix;
};
// 2.正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 OrthographicMatrix = { 0 };
	OrthographicMatrix.m[0][0] = (2 / (right - left));
	OrthographicMatrix.m[1][1] = (2 / (top - bottom));
	OrthographicMatrix.m[2][2] = (1 / (farClip - nearClip));
	OrthographicMatrix.m[3][0] = ((left + right) / (left - right));
	OrthographicMatrix.m[3][1] = ((top + bottom) / (bottom - top));
	OrthographicMatrix.m[3][2] = (nearClip / (nearClip - farClip));
	OrthographicMatrix.m[3][3] = 1;

	return OrthographicMatrix;

}

//　3.ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width,
	float height, float minDepth, float maxDepth) {

	assert(minDepth <= maxDepth);

	Matrix4x4 ViewportMatrix = { 0 };
	ViewportMatrix.m[0][0] = width / 2;
	ViewportMatrix.m[1][1] = -(height / 2);
	ViewportMatrix.m[2][2] = maxDepth - minDepth;
	ViewportMatrix.m[3][0] = left + (width / 2);
	ViewportMatrix.m[3][1] = top + (height / 2);
	ViewportMatrix.m[3][2] = minDepth;
	ViewportMatrix.m[3][3] = 1;

	return ViewportMatrix;
}



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
		// 正射影行列
		Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(
			-160.f, 160.f, 200.0f, 300.0f, 0.0f, 1000.0f);
		// 透視投射行列
		Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(
			0.63f, 1.33f, 0.1f, 1000.0f);

		//　ビューポート行列
		Matrix4x4 viewportMatrix = MakeViewportMatrix(
			100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);


		///
		/// ↑更新処理ここまで
		///

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight * 6, perspectiveFovMatrix, " perspectiveFovMatrix");
		MatrixScreenPrintf(0, kRowHeight * 6 * 2, viewportMatrix, "viewportMatrix");

		///
		/// ↓描画処理ここから
		///

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
