#include <MyMath.h>
#include <ImGuiManager.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_01";

//平面
struct Plane {
	Vector3 normal;//法線
	float distance;//距離

};

//球体と平面の当たり判定
bool IsCollision(const Sphere& sphere, const Plane& plane) {

}
//垂直なベクトルを求める
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

//平面の描画
void DrawPlane(const Plane&plane,const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix,uint32_t color) {
	//座標
	Vector3 center = Vector3Multiply(plane.distance, plane.normal);	//中心座標
	Vector3 perpendiculars[4];										//垂直


}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	//Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	//Vector3 cameraRotate = { 0.26f,0,0 };
	Vector3 cameraTranslate = { 0.0f,3.0f,-12.0f };
	Vector3 cameraRotate = { 0.35f,0,0 };


	Sphere sphere_ = { {0,0,0},0.6f };




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

		//各種行列の計算
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight),
			0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);



		ImGui::Begin("Window");
		//カメラ
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::End();

		ImGui::Begin("sphere");


		ImGui::End();


		///
		/// ↑更新処理ここまで
		///


		///
		/// ↓描画処理ここから
		///
		//グリッド線の描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		//スフィアの描画
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
