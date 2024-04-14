#pragma once
#include<Vector2.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<assert.h>
#include<Novice.h>

#include <Vector3.h>
#include <Matrix4x4.h>


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
Matrix4x4 Matrix4x4Add(const Matrix4x4& m1, const Matrix4x4& m2);

// 2. 行列の減法
Matrix4x4 Matrix4x4Subtract(const Matrix4x4& m1, const Matrix4x4& m2);

// 3. 行列の積
Matrix4x4 Matrix4x4Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 4. 逆行列
Matrix4x4 Matrix4x4Inverse(const Matrix4x4& m);

// 5. 転置行列
Matrix4x4 Matrix4x4Transpose(const Matrix4x4& m);
// 6. 単位行列の生成
Matrix4x4 MakeIdentity4x4();


//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

//3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);