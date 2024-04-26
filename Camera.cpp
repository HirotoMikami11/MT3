#include "Camera.h"

Camera::Camera(int windowWidth, int windowHeight) {

	windowSize_ = { windowWidth,windowHeight };

	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(windowSize_.x) / float(windowSize_.y),
		0.1f, 100.0f);
	viewportMatrix_ = MakeViewportMatrix(0, 0, float(windowSize_.x), float(windowSize_.y), 0.0f, 1.0f);

	Initialize();
}

//デストラクタ
Camera::~Camera() {

}

void Camera::Initialize(const Vector3& scale ,const Vector3& rotate , const Vector3& translate) {
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;

	//座標変換
	cameraMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
	viewMatrix_ = Inverse(cameraMatrix_);
	viewProjectionMatrix_ = Multiply(viewMatrix_, projectionMatrix_);


}

void Camera::Update(const char* keys, const char* preKeys) {

	keys;
	preKeys;

	//座標変換
	cameraMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
	viewMatrix_ = Inverse(cameraMatrix_);
	viewProjectionMatrix_ = Multiply(viewMatrix_, projectionMatrix_);
}

void Camera::DrawImGui() {
	ImGui::Begin("Camera");
	ImGui::DragFloat3("cameraTranslate", &translate_.x, 0.01f);
	ImGui::DragFloat3("cameraRotate", &rotate_.x, 0.01f);
	ImGui::End();
}