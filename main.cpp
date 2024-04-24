#include <MyMath.h>

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
	closestPoint = Vector3Add(segment.origin,project);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Segment segment_{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point_{ -1.5f,0.6f,0.6f };
	Vector3 project_ = Project(Vector3Subtract(point_, segment_.origin), segment_.diff);
	Vector3 closestPoint_ = ClosestPoint(point_, segment_);

	//点の描画
	Sphere pointSphere_{ point_,0.01f };
	Sphere closestPointSphere_{ closestPoint_,0.01f };

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

		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		//DrawSphere(pointSphere_,)
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
