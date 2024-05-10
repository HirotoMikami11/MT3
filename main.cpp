#include <MyFunction.h>
#include <ImGuiManager.h>
#include <Camera.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_02";

/// <summary>
/// 平面
/// </summary>
struct Plane {
	Vector3 normal;	//!<法線
	float distance;	//!<距離
};

/// <summary>
/// 球体と平面の衝突判定
/// </summary>
/// <param name="sphere"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool IsCollision(const Sphere& sphere, const Plane& plane) {

	bool isCollison = false;
	//平面と中心点との距離を求める
	float Distance = Vector3Dot(plane.normal, sphere.center) - plane.distance;
	//絶対値を取る
	Distance = Abs(Distance);

	//衝突していたらtrue
	if (Distance <= sphere.radius) {
		isCollison = true;
	}

	return isCollison;

}
/// <summary>
/// 垂直なベクトルを求める
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}


void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	//1.中心点を決める
	Vector3 center = Vector3Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];

	//2.法線と垂直なベクトルを一つ求める
	perpendiculars[0] = Vector3Normalize(Perpendicular(plane.normal));

	//3.[2]の逆ベクトルを求める
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	//4.[2]と法線とのクロス積を求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	//5.[4]の逆ベクトルを決める
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };
	//6.[2]~[5]のベクトルを中心点にそれぞれ定数倍捨て足すと4頂点が出来上がる
	Vector3 points[4];
	for (int32_t i = 0; i < 4; i++){
		Vector3 extend = Vector3Multiply(2.0f, perpendiculars[i]);
		Vector3 point = Vector3Add(center, extend);
		points[i] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine(
		static_cast<int>(points[0].x),
		static_cast<int>(points[0].y),
		static_cast<int>(points[3].x),
		static_cast<int>(points[3].y),
		color
	);	
	Novice::DrawLine(
		static_cast<int>(points[0].x),
		static_cast<int>(points[0].y),
		static_cast<int>(points[2].x),
		static_cast<int>(points[2].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(points[1].x),
		static_cast<int>(points[1].y),
		static_cast<int>(points[2].x),
		static_cast<int>(points[2].y),
		color
	);
	Novice::DrawLine(
		static_cast<int>(points[1].x),
		static_cast<int>(points[1].y),
		static_cast<int>(points[3].x),
		static_cast<int>(points[3].y),
		color
	);
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


	Sphere sphere_ = { {0.12f,0,0},0.6f };
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

		ImGui::Begin("sphere");
		////カメラ
		ImGui::DragFloat3("plane_normal", &plane_.normal.x, 0.01f);
		ImGui::DragFloat("plane_distance", &plane_.distance, 0.01f);
		ImGui::DragFloat3("sphere_pos", &sphere_.center.x, 0.01f);
		ImGui::DragFloat("sphere_radius", &sphere_.radius, 0.01f);



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


		DrawSphere(sphere_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(sphere_,plane_) ? RED : WHITE);
		DrawPlane(plane_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(),WHITE);

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
