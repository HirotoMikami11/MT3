#include <MyMath.h>
#include <imgui.h>

const char kWindowTitle[] = "LE1A_16_ミカミ_ヒロト_MT3_01_02";

struct Sphere {
	Vector3 center;		//!<中心点
	float radius;		//!<半径
};

/// <summary>
/// グリッド線を引く関数
/// </summary>
/// <param name="viewProjectionMatrix">ビュー行列*プロジェクション行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;										//Gridの半分の幅
	const uint32_t kSubdvision = 10;										//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdvision);	//1つ分の長さ

	///奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdvision; ++xIndex) {
		//ワールド座標系上の始点と終点を求める
		float pos_x = -kGridHalfWidth + xIndex * kGridEvery;
		Vector3 startPos = { pos_x,0,-kGridHalfWidth };
		Vector3 endPos = { pos_x,0,kGridHalfWidth };


		//スクリーン座標系まで変換をかける
		//スクリーン座標系まで変換をかける
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
		Matrix4x4 startWorldViewProjectionMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Vector3 startNdcPos = Transform(startPos, startWorldViewProjectionMatrix);

		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
		Matrix4x4 endWorldViewProjectionMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);
		Vector3 endNdcPos = Transform(endPos, endWorldViewProjectionMatrix);

		Vector3 screenStartPos = Transform(startNdcPos, viewportMatrix);

		Vector3 screenEndPos = Transform(endNdcPos, viewportMatrix);
		//描画する
		Novice::DrawLine(
			static_cast<int>(screenStartPos.x),
			static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x),
			static_cast<int>(screenEndPos.y),
			(xIndex == kSubdvision / 2) ? 0x000000FF : 0xAAAAAAFF);

	}

	///左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdvision; ++zIndex) {
		//ワールド座標系上の始点と終点を求める
		float pos_z = -kGridHalfWidth + zIndex * kGridEvery;
		Vector3 startPos = { -kGridHalfWidth ,0,pos_z };
		Vector3 endPos = { kGridHalfWidth ,0,pos_z };


		//スクリーン座標系まで変換をかける
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
		Matrix4x4 startWorldViewProjectionMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Vector3 startNdcPos = Transform(startPos, startWorldViewProjectionMatrix);

		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
		Matrix4x4 endWorldViewProjectionMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);
		Vector3 endNdcPos = Transform(endPos, endWorldViewProjectionMatrix);

		Vector3 screenStartPos = Transform(startNdcPos, viewportMatrix);

		Vector3 screenEndPos = Transform(endNdcPos, viewportMatrix);

		//描画する
		Novice::DrawLine(
			static_cast<int>(screenStartPos.x),
			static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x),
			static_cast<int>(screenEndPos.y),
			(zIndex == kSubdvision / 2) ? 0x000000FF : 0xAAAAAAFF);

	}
}


void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,
	uint32_t color) {
	const uint32_t kSubdivision = 10;						//分割数
	const float kLonEvery = (2 * float(M_PI)) / kSubdivision;	//経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision;		//緯度分割1つ分の角度

	// φd=klon　経度
	// φ=lon　経度
	
	// θd=klat　緯度
	// θ=lat　緯度

	 
	//緯度の方向に分割 -π/2 ~-π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = (-float(M_PI) / 2.0f) + kLatEvery * latIndex;//現在の緯度
		//経度の方向に分割0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			//world座標系でのa,b,cを求める
			Vector3 a = {
				cos(lat) * cos(lon),
				sin(lat),
				cos(lat) * sin(lon) };
			Vector3 b = {
				cos(lat + kLatEvery) * cos(lon),
				sin(lat + kLatEvery),
				cos(lat + kLatEvery) * sin(lon)
			};
			Vector3 c = {
				cos(lat) * cos(lon + kLonEvery),
				sin(lat),
				cos(lat) * sin(lon + kLonEvery)
			};


			a = Vector3Add(sphere.center, Vector3Multiply(sphere.radius, a));
			b = Vector3Add(sphere.center, Vector3Multiply(sphere.radius, b));
			c = Vector3Add(sphere.center, Vector3Multiply(sphere.radius, c));

			//a,b,c,をScreen座標系まで変換する
			Matrix4x4 AWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
			Matrix4x4 AWorldViewProjectionMatrix = Multiply(AWorldMatrix, viewProjectionMatrix);
			Vector3 ANdcPos = Transform(a, AWorldViewProjectionMatrix);

			Matrix4x4 BWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
			Matrix4x4 BWorldViewProjectionMatrix = Multiply(BWorldMatrix, viewProjectionMatrix);
			Vector3 BNdcPos = Transform(b, BWorldViewProjectionMatrix);

			Matrix4x4 CWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, {0,0,0});
			Matrix4x4 CWorldViewProjectionMatrix = Multiply(CWorldMatrix, viewProjectionMatrix);
			Vector3 CNdcPos = Transform(c, CWorldViewProjectionMatrix);

			Vector3 screenAPos = Transform(Transform(a, AWorldViewProjectionMatrix), viewportMatrix);
			Vector3 screenBPos = Transform(Transform(b, BWorldViewProjectionMatrix), viewportMatrix);
			Vector3 screenCPos = Transform(Transform(c, CWorldViewProjectionMatrix), viewportMatrix);

			//ab,bcで線を引く
			Novice::DrawLine(
				static_cast<int>(screenAPos.x),
				static_cast<int>(screenAPos.y),
				static_cast<int>(screenBPos.x),
				static_cast<int>(screenBPos.y),
				color);
			Novice::DrawLine(
				static_cast<int>(screenAPos.x),
				static_cast<int>(screenAPos.y),
				static_cast<int>(screenCPos.x),
				static_cast<int>(screenCPos.y),
				color);

		}
	}


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

	Sphere sphere = { {0,0,0},0.5f };

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

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);


		ImGui::Begin("Window");
		//カメラ
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		//スフィア
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);

		ImGui::End();


		///
		/// ↑更新処理ここまで
		///


		///
		/// ↓描画処理ここから
		///

		DrawGrid(Multiply(viewMatrix, projectionMatrix), viewportMatrix);
		DrawSphere(sphere, Multiply(viewMatrix, projectionMatrix), viewportMatrix, BLACK);

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
