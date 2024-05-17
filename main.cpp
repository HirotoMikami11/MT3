#include <MyFunction.h>
#include <ImGuiManager.h>
#include <Camera.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_04";
/// <summary>
/// 三角形
/// </summary>
struct Triangle {
	Vector3 vertices[3];//!<頂点
};

bool IsCollision(const Segment& segment, const Vector3& normal, const float& distance) {
	//segmentのo=origin,b=diff

	//衝突しているかどうか
	bool isCollision = false;

	float dot = Vector3Dot(segment.diff, normal);

	//線と平面が並行の時
	//b・n＝0の時0除算なので衝突しない
	if (dot == 0.0f) {
		return false;
	}

	float t = (distance - (Vector3Dot(segment.origin, normal))) / dot;

	if (t > 0 && t < 1) {
		isCollision = true;
	}

	return isCollision;

}
Vector3 MakeCollisionPoint(const Segment& segment, const Vector3& normal, const float& distance) {
	//segmentのo=origin,b=diff

	//衝突点
	Vector3 CollisionPoint;

	//平面と線の衝突判定と同様
	float dot = Vector3Dot(segment.diff, normal);
	
	///衝突したら衝突点を計算するのでdotが0にはならないはず
	assert(dot != 0.0f);

	float t = (distance - (Vector3Dot(segment.origin, normal))) / dot;

	//p=o+tb
	//衝突点=origin+t*diff
	CollisionPoint = Vector3Add(segment.origin, Vector3Multiply(t, segment.diff));

	return CollisionPoint;

}
bool IsCollision(const Segment& segment, const Triangle& triangle) {

	//衝突しているかどうか
	bool isCollision = false;

	//
	///	線と三角形の存在する平面との衝突判定を行う
	//

	//三角形の中心座標
	Vector3 TriangleCenter = {
		(triangle.vertices[0].x + triangle.vertices[1].x + triangle.vertices[2].x) / 3,
		(triangle.vertices[0].y + triangle.vertices[1].y + triangle.vertices[2].y) / 3,
		(triangle.vertices[0].z + triangle.vertices[1].z + triangle.vertices[2].z) / 3
	};

	//平面を作るのに必要な値を作る
	//距離
	float distance = Vector3Distance(TriangleCenter, { 0,0,0 });
	//法線ベクトル
	Vector3 normal = Cross(Vector3Subtract(triangle.vertices[1], triangle.vertices[0]), Vector3Subtract(triangle.vertices[2], triangle.vertices[1]));


	//
	///	線と三角形の存在する平面とが衝突していたら衝突点が内側か調べる
	//

	if (IsCollision(segment, normal, distance)) {
		//衝突点pを計算
		Vector3 p = MakeCollisionPoint(segment, normal, distance);

		//各辺を結んだベクトル
		Vector3 v01 = Vector3Subtract(triangle.vertices[1], triangle.vertices[0]);
		Vector3 v12 = Vector3Subtract(triangle.vertices[2], triangle.vertices[1]);
		Vector3 v20 = Vector3Subtract(triangle.vertices[0], triangle.vertices[2]);

		//頂点と衝突点Pを結んだベクトル
		Vector3 vp[3];
		for (int i = 0; i < 3; i++) {
			vp[i] = Vector3Subtract(p, triangle.vertices[i]);
		}

		//クロス積
		Vector3 cross01 = Cross(v01, vp[1]);
		Vector3 cross12 = Cross(v12, vp[2]);
		Vector3 cross20 = Cross(v20, vp[0]);

		//全ての小さい三角形のクロス積と法線が同じ方法を向いていたら衝突
		if (
			Vector3Dot(cross01, normal) >= 0.0f &&
			Vector3Dot(cross12, normal) >= 0.0f &&
			Vector3Dot(cross20, normal) >= 0.0f
			) {
			isCollision = true;
		}
	}
	return isCollision;
}




/// <summary>
/// 三角形を描画
/// </summary>
/// <param name="triangle"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 ndcPos[3];
	Vector3 screenPos[3];

	//スクリーン座標系まで変換をかける
	for (int i = 0; i < 3; i++) {
		ndcPos[i] = Transform(triangle.vertices[i], viewProjectionMatrix);
		screenPos[i] = Transform(ndcPos[i], viewportMatrix);
	}

	Novice::DrawTriangle(
		static_cast<int>(screenPos[0].x),
		static_cast<int>(screenPos[0].y),
		static_cast<int>(screenPos[1].x),
		static_cast<int>(screenPos[1].y),
		static_cast<int>(screenPos[2].x),
		static_cast<int>(screenPos[2].y),
		color, kFillModeWireFrame);


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

	Segment segment_ =
	{ {0.0f,0.5f,0.0f},
		{0.0f,0.5f,2.0f} };
	Triangle triangle_ = {
		{{-1,0,0}
		,{0,1,0}
		,{1,0,0}
		}
	};

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
		ImGui::DragFloat3("Triangle.v0", &triangle_.vertices[0].x, 0.01f);
		ImGui::DragFloat3("Triangle.v1", &triangle_.vertices[1].x, 0.01f);
		ImGui::DragFloat3("Triangle.v2", &triangle_.vertices[2].x, 0.01f);
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
		DrawLine(segment_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(segment_, triangle_) ? RED : WHITE);
		//三角形の描画
		DrawTriangle(triangle_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), WHITE);

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
