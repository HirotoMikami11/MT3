#include <MyFunction.h>
#include <ImGuiManager.h>
#include <Camera.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;

	Camera* camera_=new Camera(kWindowWidth, kWindowHeight);

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

		camera_->Update(keys,preKeys);

		IsCollision(sphereA_, sphereB_);


		camera_->DrawImGui();

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
		DrawGrid(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix());
		//スフィアの描画


		DrawSphere(sphereA_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(sphereA_, sphereB_) ? RED : WHITE);
		DrawSphere(sphereB_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(sphereA_, sphereB_) ? RED : WHITE);

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

	delete camera_;
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
