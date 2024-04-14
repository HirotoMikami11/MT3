#include <MyMath.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_00_05";

//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 AffineMatrix = { 0 };

	AffineMatrix.m[0][0] = scale.x * (std::cosf(rotate.y) * std::cosf(rotate.z));
	AffineMatrix.m[0][1] = std::sinf(rotate.z);
	AffineMatrix.m[0][2] = -(std::sinf(rotate.y));
	AffineMatrix.m[0][3] = 0;

	AffineMatrix.m[1][0] = -(std::sinf(rotate.z));
	AffineMatrix.m[1][1] = scale.y * (std::cosf(rotate.x) * std::cosf(rotate.z));
	AffineMatrix.m[1][2] = std::sinf(rotate.x);
	AffineMatrix.m[1][3] = 0;

	AffineMatrix.m[2][0] = std::sinf(rotate.y);
	AffineMatrix.m[2][1] = -(std::sinf(rotate.x));
	AffineMatrix.m[2][2] = scale.z * (std::cosf(rotate.x) * std::cosf(rotate.y));
	AffineMatrix.m[2][3] = 0;

	AffineMatrix.m[3][0] = translate.x;
	AffineMatrix.m[3][1] = translate.y;
	AffineMatrix.m[3][2] = translate.z;
	AffineMatrix.m[3][3] = 1;

	return AffineMatrix;


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

		Vector3 scale{ 1.2f,0.79f,-2.1f };
		Vector3 rotate{ 0.4f,1.43f,-0.8f };
		Vector3 translate{2.7f,-4.15f,1.57f};
		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

		///
		/// ↑更新処理ここまで
		///

		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatix");

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
