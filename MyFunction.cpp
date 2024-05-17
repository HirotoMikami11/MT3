#include "MyFunction.h"


///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

///																		///
///								計算関数
///																		///

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

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

Vector3 Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	bool isCollision = false;

	float distance = Vector3Distance(s1.center, s2.center);

	if (distance <= powf(s1.radius + s2.radius, 2)) {
		isCollision = true;

	}

	return isCollision;
}


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


///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

///																		///
///								描画関数
///																		///

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//


void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 start = segment.origin;
	Vector3 end = Vector3Add(segment.origin, segment.diff);

	//temp
	Vector3 startTemp = Transform(start, viewProjectionMatrix);
	Vector3 screenStart = Transform(startTemp, viewportMatrix);

	Vector3 endTemp = Transform(end, viewProjectionMatrix);
	Vector3 screenEnd = Transform(endTemp, viewportMatrix);

	Novice::DrawLine(
		static_cast<int>(screenStart.x),
		static_cast<int>(screenStart.y),
		static_cast<int>(screenEnd.x),
		static_cast<int>(screenEnd.y),
		color);


}


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
		Vector3 startNdcPos = Transform(startPos, viewProjectionMatrix);

		Vector3 endNdcPos = Transform(endPos, viewProjectionMatrix);

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
		//Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
		//Matrix4x4 startWorldViewProjectionMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Vector3 startNdcPos = Transform(startPos, viewProjectionMatrix);

		//Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
		//Matrix4x4 endWorldViewProjectionMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);
		Vector3 endNdcPos = Transform(endPos, viewProjectionMatrix);

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


/// <summary>
/// 3Dで球体を描く関数
/// </summary>
/// <param name="sphere"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
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
			//Matrix4x4 AWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
			//Matrix4x4 AWorldViewProjectionMatrix = Multiply(AWorldMatrix, viewProjectionMatrix);
			Vector3 ANdcPos = Transform(a, viewProjectionMatrix);

			//Matrix4x4 BWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
			//Matrix4x4 BWorldViewProjectionMatrix = Multiply(BWorldMatrix, viewProjectionMatrix);
			Vector3 BNdcPos = Transform(b, viewProjectionMatrix);

			//Matrix4x4 CWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
			//Matrix4x4 CWorldViewProjectionMatrix = Multiply(CWorldMatrix, viewProjectionMatrix);
			Vector3 CNdcPos = Transform(c, viewProjectionMatrix);

			Vector3 screenAPos = Transform(ANdcPos, viewportMatrix);
			Vector3 screenBPos = Transform(BNdcPos, viewportMatrix);
			Vector3 screenCPos = Transform(CNdcPos, viewportMatrix);

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
	for (int32_t i = 0; i < 4; i++) {
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
