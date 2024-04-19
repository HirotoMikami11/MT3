#pragma once
#include<Vector2.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<assert.h>
#include<Novice.h>

#include <Vector3.h>
#include <Matrix4x4.h>
#include <cmath> //C++

static const int kRowHeight = 20;
static const int kColumnWidth = 60;
///*-------------------------------------------------------------------*///
///
///								ベクトル
///
///*-------------------------------------------------------------------*///

/*-----------------------------------------------------------------------*/
//
//								2次元ベクトル
//
/*-----------------------------------------------------------------------*/

//線形補間関数
Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
float Lerp(const float& a, const float& b, float t);
int LerpColor(const int& a, const int& b, float t);

//値を範囲内に収める関数
float  clamp(float value, float min, float max);
unsigned int clampColor(unsigned int& value, unsigned int min, unsigned int max, float t);


//イージングのｔを使う時の関数
//無限にイージング
float easeClampRe(float t, float& easeDir);
//0~1~0の一回で終了
float easeClampOnce(float t, float& easeDir, bool& isEase);
//0~1onceの半分で終了
float easeClamphalf(float t, float& easeDir, bool& isEase);
//反転しない1で停止
float easeClamphalfE(float t);



//waitTimer分待機する場合の関数
//無限にイージング
float easeClampReW(float t, float& easeDir, int& waitTimer, int kmaxTimer);
//0~1~0の一回で終了
float easeClampOnceW(float& t, float& easeDir, bool& isEase, int& waitTimer, int kmaxTimer);
//0~1onceの半分で終了
float easeClamphalfW(float t, float& easeDir, bool& isEase, int& waitTimer, int kmaxTimer);



void VectorVertexS(Vector2 vertex[4], Vector2 CPos, float Width, float Height);
void VectorVertexTriS(Vector2 vertex[3], Vector2 CPos, float Width, float Height);
void VectorVertexSword(Vector2 vertex[11], Vector2 CPos, float Width, float Height);
void Vector2ScreenPrint(int x, int y, Vector2 vector);

void MyDrawQuad(Vector2 vertex[4], int GH, int srcX, int srcY, int srcW, int srcH, unsigned int color);
void MyDrawLine(Vector2 startpos, Vector2 endpos, unsigned int color);

/*-----------------------------------------------------------------------*/
//
//								3次元ベクトル
//
/*-----------------------------------------------------------------------*/


//３次元ベクトルの値を表示する
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);
//加算
Vector3 Vector3Add(const Vector3& v1, const Vector3& v2);
//減算
Vector3 Vector3Subtract(const Vector3& v1, const Vector3& v2);
//スカラー倍
Vector3 Vector3Multiply(float scalar, const Vector3& v);
//内積
float Vector3Dot(const Vector3& v1, const Vector3& v2);
//長さ
float Vector3Length(const Vector3& v);
//正規化
Vector3 Vector3Normalize(const Vector3& v);




///*-------------------------------------------------------------------*///
///
///								行列
///
///*-------------------------------------------------------------------*///


/*-----------------------------------------------------------------------*/
//
//								2x2
//
/*-----------------------------------------------------------------------*/

//2x2の行列を表す
struct Matrix2x2 {
	float m[2][2];
};

//行列の加法
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 Matrix2);

//行列の減法
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 Matrix2);

//行列の積
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 Matrix2);

//ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 Matrix);

//2x2行列の逆行列を生成
Matrix2x2 Inverse2x2(Matrix2x2 matrix);
//2x2転置行列を求める
Matrix2x2 Transpose2x2(Matrix2x2 matrix);

//2x2の行列表示
void MatriXScreenPrint2x2(int x, int y, Matrix2x2 matrix);


/*-----------------------------------------------------------------------*/
//
//								3x3
//
/*-----------------------------------------------------------------------*/


//3x3の行列を表す
struct Matrix3x3 {
	float m[3][3];
};

Matrix3x3 Add(Matrix3x3 matrix1, Matrix3x3 matrix2);
Matrix3x3 Subtract(Matrix3x3 matrix1, Matrix3x3 matrix2);
//行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);


//回転行列
Matrix3x3 MakeRotateMatrix(float theta);

//平行移動行列
Matrix3x3 MakeTranslateMatrix(Vector2 translate);

//拡大縮小行列
Matrix3x3 MakeScaleMatrix(Vector2 scale);

//アフィン行列
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

//行列変換
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

//3x3行列の逆行列を生成
Matrix3x3 Inverse3x3(Matrix3x3 matrix);

//3x3転置行列を求める
Matrix3x3 Transpose3x3(Matrix3x3 matrix);


//正射影行列を生成
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

//ビューポート行列を生成
Matrix3x3 MakeviewportMatrix(float left, float top, float width, float height);

//レンダリングパイプラインを生成
Matrix3x3 MakeWvpVpMatrix(Vector2 localPos, Matrix3x3 worldMatrix, Matrix3x3 viewMatrix, Matrix3x3 orthoMatrix, Matrix3x3 viewportMatrix);


//3x3の行列描画
void MatriXScreenPrint3x3(int x, int y, Matrix3x3 matrix);
/*-----------------------------------------------------------------------*/
//
//								4x4
//
/*-----------------------------------------------------------------------*/

//4x4の行列の数値を表示する
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

// 1. 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);

// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
// 6. 単位行列の生成
Matrix4x4 MakeIdentity4x4();


//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

//3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

// 1 X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// 2 Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// 3 Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);


//  XYZ回転行列
// Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);

//アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// 1.透視投射行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
// 2.正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//　3.ビューポート行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width,
	float height, float minDepth, float maxDepth);

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);


//スフィア
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
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, startPos);
		Matrix4x4 startWorldViewProjectionMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, endPos);
		Matrix4x4 endWorldViewProjectionMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 screenStartPos = Transform(Transform(startPos, startWorldViewProjectionMatrix), viewportMatrix);

		Vector3 screenEndPos = Transform(Transform(endPos, endWorldViewProjectionMatrix), viewportMatrix);

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
		Matrix4x4 startWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, startPos);
		Matrix4x4 startWorldViewProjectionMatrix = Multiply(startWorldMatrix, viewProjectionMatrix);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, endPos);
		Matrix4x4 endWorldViewProjectionMatrix = Multiply(endWorldMatrix, viewProjectionMatrix);

		Vector3 screenStartPos = Transform(Transform(startPos, startWorldViewProjectionMatrix), viewportMatrix);

		Vector3 screenEndPos = Transform(Transform(endPos, endWorldViewProjectionMatrix), viewportMatrix);

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
/// スフィアを作る関数
/// </summary>
/// <param name="sphere">スフィア</param>
/// <param name="viewProjectionMatrix">ビュープロジェクション</param>
/// <param name="viewportMatrix">ビューポート</param>
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
			Matrix4x4 AWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, a);
			Matrix4x4 AWorldViewProjectionMatrix = Multiply(AWorldMatrix, viewProjectionMatrix);

			Matrix4x4 BWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, b);
			Matrix4x4 BWorldViewProjectionMatrix = Multiply(BWorldMatrix, viewProjectionMatrix);

			Matrix4x4 CWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, c);
			Matrix4x4 CWorldViewProjectionMatrix = Multiply(CWorldMatrix, viewProjectionMatrix);

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

