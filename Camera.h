#pragma once
#include <MyFunction.h>
#include <ImGuiManager.h>

class Camera
{
private:
	Vector2Int windowSize_;
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;

	///座標変換
	Matrix4x4 cameraMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 viewProjectionMatrix_;
	Matrix4x4 viewportMatrix_;

	///カメラ移動
	bool ismove_;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="windowWidth">ウィンドウの縦幅</param>
	/// <param name="windowHeight">ウィンドウの横幅</param>
	Camera(int windowWidth, int windowHeight);

	//デストラクタ
	~Camera();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="scale"></param>
	/// <param name="rotate"></param>
	/// <param name="translate"></param>
	void Initialize(const Vector3& scale = { 1.0f,1.0f,1.0f }, const Vector3& rotate = { 0.26f, 0.0f, 0.0f }, const Vector3& translate = { 0.0f, 1.9f, -6.49f });
	void Update(const char* keys, const char* preKeys);

	/// <summary>
	/// カメラのデバッグ
	/// </summary>
	void DrawImGui();

	///egttar
	Matrix4x4 GetViewportMatrix() { return viewportMatrix_; };
	Matrix4x4 GetViewProjectionMatrix() { return viewProjectionMatrix_; };



};

