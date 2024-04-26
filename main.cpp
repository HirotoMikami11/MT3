#include <MyMath.h>
#include <ImGuiManager.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_01";

float Vector3Distance(const Vector3 v1, const Vector3 v2) {

	float result = powf({ v2.x - v1.x }, 2) + powf({ v2.y - v1.y }, 2) + powf({ v2.z - v1.z }, 2);
	return result;
}

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	bool isCollision = false;

	float distance = Vector3Distance(s1.center, s2.center);

	if (distance <= powf(s1.radius + s2.radius,2)) {
		isCollision = true;

	}

	return isCollision;
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

	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0,0 };
	//Vector3 cameraTranslate = { 0.0f,3.0f,-12.0f };
	//Vector3 cameraRotate = { 0.35f,0,0 };


	Sphere sphereA_ = { {0,0,0},0.6f };
	Sphere sphereB_ = { {0.8f,0,1.0f},0.4f };



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

		IsCollision(sphereA_, sphereB_);


		ImGui::Begin("Window");
		//カメラ
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::End();

		ImGui::Begin("sphere");
		//カメラ
		ImGui::DragFloat3("sphereA_pos", &sphereA_.center.x, 0.01f);
		ImGui::DragFloat("sphereA_radius", &sphereA_.radius, 0.01f);

		ImGui::DragFloat3("sphereB_pos", &sphereB_.center.x, 0.01f);
		ImGui::DragFloat("sphereB_radius", &sphereB_.radius, 0.01f);

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

		
		DrawSphere(sphereA_, viewProjectionMatrix, viewportMatrix,  IsCollision(sphereA_, sphereB_)? RED: WHITE);
		DrawSphere(sphereB_, viewProjectionMatrix, viewportMatrix, IsCollision(sphereA_, sphereB_)? RED: WHITE);
		
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
