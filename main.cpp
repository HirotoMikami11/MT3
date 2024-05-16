#include <MyFunction.h>
#include <ImGuiManager.h>
#include <Camera.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_04";

bool IsCollision(const Segment& segment, const Plane& plane) {
	//segmentのo=origin,b=diff


	//衝突しているかどうか
	bool isCollision = false;

	float dot = Vector3Dot(segment.diff, plane.normal);

	//線と平面が並行の時
	//b・n＝0の時0除算なので衝突しない

	if (dot == 0.0f) {
		return false;
	}

	float t = (plane.distance - (Vector3Dot(segment.origin, plane.normal))) / dot;

	if (t >= 0 && t <= 1) {
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

	Camera* camera_ = new Camera(kWindowWidth, kWindowHeight);

	Segment segment_ = { {-0.45f,0.7f,0.0f},{1.0f,0.5f,0.0f} };
	Plane plane_ = { {0,1,0},1.0f };


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

		camera_->Update(keys, preKeys);



		camera_->DrawImGui();

		ImGui::Begin("object");
		////カメラ
		ImGui::DragFloat3("plane_normal", &plane_.normal.x, 0.01f);
		plane_.normal = Vector3Normalize(plane_.normal);
		ImGui::DragFloat("plane_distance", &plane_.distance, 0.01f);
		ImGui::DragFloat3("segment_.origin", &segment_.origin.x, 0.01f);
		ImGui::DragFloat3("segment_.diff", &segment_.diff.x, 0.01f);



		ImGui::End();


		///
		/// ↑更新処理ここまで
		///


		///
		/// ↓描画処理ここから
		///
		//グリッド線の描画
		DrawGrid(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix());
		//ライン
		DrawLine(segment_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(segment_, plane_) ? RED : WHITE);
		//スフィアの描画
		DrawPlane(plane_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), WHITE);

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
