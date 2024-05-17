#pragma once
#include "MyMath.h"

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

///																		///
///								構造体
///																		///

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//


/// <summary>
/// スフィア
/// </summary>
struct Sphere {
	Vector3 center;		//!<中心点
	float radius;		//!<半径
};

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

/// <summary>
/// 平面
/// </summary>
struct Plane {
	Vector3 normal;	//!<法線
	float distance;	//!<距離
};

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

///																		///
///								計算関数
///																		///

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//


/// <summary>
/// 正射影ベクトルを求める
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vector3 Project(const Vector3& v1, const Vector3& v2);

/// <summary>
/// 最近接点を求める関数
/// </summary>
/// <param name="point"></param>
/// <param name="segment"></param>
/// <returns></returns>
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

/// <summary>
/// 垂直なベクトルを求める
/// </summary>
/// <param name="vector"></param>
/// <returns></returns>
Vector3 Perpendicular(const Vector3& vector);

/// <summary>
/// 球体と球体の当たり判定を求める関数
/// </summary>
/// <param name="s1"></param>
/// <param name="s2"></param>
/// <returns></returns>
bool IsCollision(const Sphere& s1, const Sphere& s2);

/// <summary>
/// 球体と平面の衝突判定
/// </summary>
/// <param name="sphere"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool IsCollision(const Sphere& sphere, const Plane& plane);

/// <summary>
/// 平面と線の衝突判定
/// </summary>
/// <param name="segment"></param>
/// <param name="plane"></param>
/// <returns></returns>
bool IsCollision(const Segment& segment, const Plane& plane);


///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//

///																		///
///								描画関数
///																		///

///xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//


/// <summary>
/// 3Dで線を引く関数
/// </summary>
/// <param name="segment"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawLine(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);


/// <summary>
/// グリッド線を引く関数
/// </summary>
/// <param name="viewProjectionMatrix">ビュー行列*プロジェクション行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// スフィアを作る関数
/// </summary>
/// <param name="sphere">スフィア</param>
/// <param name="viewProjectionMatrix">ビュープロジェクション</param>
/// <param name="viewportMatrix">ビューポート</param>
/// <param name="color"></param>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix,
	uint32_t color);

/// <summary>
/// 平面を作る関数
/// </summary>
/// <param name="plane"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

