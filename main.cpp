#include <MyFunction.h>
#include <ImGuiManager.h>
#include <Camera.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_02_05";

/// <summary>
/// 軸並行境界箱
/// </summary>
struct AABB {
	Vector3 min;//!<最小点
	Vector3 max;//!<最大点
};


bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	///衝突判定
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;

}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const  Matrix4x4& viewportMatrix, uint32_t color) {


	Vector3 vertices[8];

	///上の四頂点
	vertices[0] = { aabb.max.x,aabb.max.y,aabb.max.z };//右上奥
	vertices[1] = { aabb.min.x,aabb.max.y,aabb.max.z };//左上奥

	vertices[2] = { aabb.max.x,aabb.max.y,aabb.min.z };//右上手前
	vertices[3] = { aabb.min.x,aabb.max.y,aabb.min.z };//左上手前

	///下の四頂点
	vertices[4] = { aabb.max.x,aabb.min.y,aabb.max.z };//右下奥
	vertices[5] = { aabb.min.x,aabb.min.y,aabb.max.z };//左下奥

	vertices[6] = { aabb.max.x,aabb.min.y,aabb.min.z };//右下手前
	vertices[7] = { aabb.min.x,aabb.min.y,aabb.min.z };//左下手前

	Vector3 NdcVertices[8];
	Vector3 screenVertices[8];
	for (int i = 0; i < 8; i++) {
		//スクリーン座標系まで変換をかける
		NdcVertices[i] = Transform(vertices[i], viewProjectionMatrix);
		screenVertices[i] = Transform(NdcVertices[i], viewportMatrix);
	}

	///描画する場所
	const int edges[12][2] = {
		{0, 1}, {1, 3}, {3, 2}, {2, 0}, //上面
		{4, 5}, {5, 7}, {7, 6}, {6, 4}, //下面
		{0, 4}, {1, 5}, {2, 6}, {3, 7}  //上面と下面をつなぐ線
	};

	///AABBを描画
	for (int i = 0; i < 12; i++) {
		Novice::DrawLine(
			static_cast<int>(screenVertices[edges[i][0]].x),
			static_cast<int>(screenVertices[edges[i][0]].y),
			static_cast<int>(screenVertices[edges[i][1]].x),
			static_cast<int>(screenVertices[edges[i][1]].y),
			color
		);
	}

}

/// <summary>
/// 最大最小を正しくする関数
/// </summary>
/// <param name="aabb"></param>
void NormalizeAABB(AABB& aabb) {
	aabb.min.x = (std::min)(aabb.min.x, aabb.max.x);
	aabb.max.x = (std::max)(aabb.min.x, aabb.max.x);
	aabb.min.y = (std::min)(aabb.min.y, aabb.max.y);
	aabb.max.y = (std::max)(aabb.min.y, aabb.max.y);
	aabb.min.z = (std::min)(aabb.min.z, aabb.max.z);
	aabb.max.z = (std::max)(aabb.min.z, aabb.max.z);
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

	AABB aabb1{
	.min{-0.5f,-0.5f,-0.5f},
	.max{0.0f,0.0f,0.0f}
	};
	AABB aabb2{
	.min{0.2f,0.2f,0.2f},
	.max{1.0f,1.0f,1.0f}
	};
	NormalizeAABB(aabb1);
	NormalizeAABB(aabb2);
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
		///minmaxを正しくする
		NormalizeAABB(aabb1);
		NormalizeAABB(aabb2);

		camera_->DrawImGui();

		ImGui::Begin("object");
		////カメラ
		ImGui::DragFloat3("aabb1.max", &aabb1.max.x, 0.01f);
		ImGui::DragFloat3("aabb1.min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("aabb2.max", &aabb2.max.x, 0.01f);
		ImGui::DragFloat3("aabb2.min", &aabb2.min.x, 0.01f);
		NormalizeAABB(aabb1);
		NormalizeAABB(aabb2);

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///


		///
		/// ↓描画処理ここから
		///
		//グリッド線の描画
		DrawGrid(camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix());
		////ライン
		//DrawLine(segment_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(segment_, triangle_) ? RED : WHITE);
		////三角形の描画
		//DrawTriangle(triangle_, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), WHITE);
		//
		DrawAABB(aabb1, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(aabb1, aabb2) ? RED : WHITE);
		//
		DrawAABB(aabb2, camera_->GetViewProjectionMatrix(), camera_->GetViewportMatrix(), IsCollision(aabb1, aabb2) ? RED : WHITE);

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
