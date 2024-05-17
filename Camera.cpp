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

void Camera::Initialize(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;

	//座標変換
	cameraMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
	viewMatrix_ = Inverse(cameraMatrix_);
	viewProjectionMatrix_ = Multiply(viewMatrix_, projectionMatrix_);
	///カメラ移動
	ismove_ = true;

}

void Camera::Update(const char* keys, const char* preKeys) {

	IsMove(keys, preKeys);

	//座標変換
	cameraMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
	viewMatrix_ = Inverse(cameraMatrix_);
	viewProjectionMatrix_ = Multiply(viewMatrix_, projectionMatrix_);
}

void Camera::IsMove(const char* keys, const char* preKeys) {

	if (keys[DIK_LSHIFT] && !preKeys[DIK_LSHIFT]) {
		if (ismove_) {
			ismove_ = false;
		} else {
			ismove_ = true;
		}
	}

	if (ismove_) {
		//移動
		if (keys[DIK_W]) { translate_.z += 0.01f; }
		if (keys[DIK_A]) { translate_.x -= 0.01f; }
		if (keys[DIK_D]) { translate_.x += 0.01f; }
		if (keys[DIK_S]) { translate_.z -= 0.01f; }

		//始点の回転
		if (keys[DIK_UP]) { rotate_.x -= 0.01f; }
		if (keys[DIK_LEFT]) { rotate_.y -= 0.01f; }
		if (keys[DIK_RIGHT]) { rotate_.y += 0.01f; }
		if (keys[DIK_DOWN]) { rotate_.x += 0.01f; }
	}


}

void Camera::DrawImGui() {
	ImGui::Begin("Camera");
	ImGui::Text((ismove_ == true) ? "ismove_ : true" : "ismove_ : false");
	ImGui::DragFloat3("cameraTranslate", &translate_.x, 0.01f);
	ImGui::DragFloat3("cameraRotate", &rotate_.x, 0.01f);
	ImGui::End();
}