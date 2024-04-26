#include <MyMath.h>
#include <ImGuiManager.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_00";

/// <summary>
/// 直線
/// </summary>
struct Line {
	Vector3 origin;	//!<始点
	Vector3 diff;	//!<終点への差分ベクトル
};

/// <summary>
/// 半直線
/// </summary>
struct Ray {
	Vector3 origin;	//!<始点
	Vector3 diff;	//!<終点への差分ベクトル
};

/// <summary>
/// 線分
/// </summary>
struct Segment {
	Vector3 origin;	//!<始点
	Vector3 diff;	//!<終点への差分ベクトル
};

Vector3 Project(const Vector3& v1, const Vector3& v2) {
	Vector3 project;

	project = Vector3Multiply(Vector3Dot(v1, Vector3Normalize(v2)), Vector3Normalize(v2));
	return project;
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {


	Vector3 closestPoint;
	Vector3 project = Project(Vector3Subtract(point, segment.origin), segment.diff);
	closestPoint = Vector3Add(segment.origin, project);
	return closestPoint;
}


void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 start = segment.origin;
	Vector3 end = Vector3Add(segment.origin, segment.diff);

	//ワールド
	Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
	Matrix4x4 startWorldViewprojectionMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);

	Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
	Matrix4x4 endWorldViewprojectionMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);

	//temp
	Vector3 startTemp = Transform(start, startWorldViewprojectionMatrix);
	Vector3 screenStart = Transform(startTemp, viewportMatrix);
	Vector3 endTemp = Transform(end, endWorldViewprojectionMatrix);
	Vector3 screenEnd = Transform(endTemp, viewportMatrix);


	Novice::DrawLine(
		static_cast<int>(screenStart.x),
		static_cast<int>(screenStart.y),
		static_cast<int>(screenEnd.x),
		static_cast<int>(screenEnd.y),
		color);


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

	Segment segment_{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point_{ -1.5f,0.6f,0.6f };
	Vector3 project_ = Project(Vector3Subtract(point_, segment_.origin), segment_.diff);
	Vector3 closestPoint_ = ClosestPoint(point_, segment_);



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

		//点の描画
		project_ = Project(Vector3Subtract(point_, segment_.origin), segment_.diff);
		closestPoint_ = ClosestPoint(point_, segment_);

		Sphere pointSphere_{ point_,0.01f };
		Sphere closestPointSphere_{ closestPoint_,0.01f };

		//線分の計算
		Vector3 start = Transform(Transform(segment_.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Vector3Add(segment_.origin, segment_.diff), viewProjectionMatrix), viewportMatrix);

		ImGui::Begin("Window");
		//カメラ
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("Point", &point_.x, 0.01f);
		ImGui::DragFloat3("Segment oeigin", &segment_.origin.x, 0.01f);
		ImGui::DragFloat3("segment diff", &segment_.diff.x, 0.01f);
		ImGui::InputFloat3("Project", &project_.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//グリッド線の描画
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		//線分の描画
		DrawLine(segment_,viewProjectionMatrix,viewportMatrix,WHITE);

		//点の描画
		DrawSphere(pointSphere_, viewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(closestPointSphere_, viewProjectionMatrix, viewportMatrix, BLACK);

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
