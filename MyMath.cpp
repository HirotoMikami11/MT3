#include "MyMath.h"


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
Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {

	Vector2 result = { t * a.x + (1.0f - t) * b.x,t * a.y + (1.0f - t) * b.y };
	return result;
}
float Lerp(const float& a, const float& b, float t) {

	float result = t * a + (1.0f - t) * b;

	return result;
}
int LerpColor(const int& a, const int& b, float t) {
	float result = t * a + (1 - t) * b;

	return int(result);

}


void VectorVertexS(Vector2 vertex[4], Vector2 CPos, float Width, float Height) {
	vertex[0].x = CPos.x - Width / 2;
	vertex[0].y = CPos.y - Height / 2;
	vertex[1].x = CPos.x + Width / 2;
	vertex[1].y = CPos.y - Height / 2;
	vertex[2].x = CPos.x - Width / 2;
	vertex[2].y = CPos.y + Height / 2;
	vertex[3].x = CPos.x + Width / 2;
	vertex[3].y = CPos.y + Height / 2;
};
void VectorVertexTriS(Vector2 vertex[3], Vector2 CPos, float Width, float Height) {
	//上
	vertex[0].x = CPos.x;
	vertex[0].y = CPos.y - Height / 2;
	//右下
	vertex[1].x = CPos.x + Width / 2;
	vertex[1].y = CPos.y + Height / 2;
	//左下
	vertex[2].x = CPos.x - Width / 2;
	vertex[2].y = CPos.y + Height / 2;
}


void VectorVertexSword(Vector2 vertex[11], Vector2 CPos, float Width, float Height) {

	//刃の部分三角形
	//上
	vertex[0].x = CPos.x;
	vertex[0].y = (CPos.y - Height * 0.3f) - (Height * 1.7f) / 2;
	//右下
	vertex[1].x = CPos.x + (Width / 2.5f) / 2;
	vertex[1].y = (CPos.y - Height * 0.3f) + (Height * 1.7f) / 2;
	//左下
	vertex[2].x = CPos.x - (Width / 2.5f) / 2;
	vertex[2].y = (CPos.y - Height * 0.3f) + (Height * 1.7f) / 2;

	//ガードの部分四角形横長の長方形
	vertex[3].x = CPos.x - (Width / 1.6f) / 2;
	vertex[3].y = (CPos.y + Height / 2 + Height / 8) - (Height / 4) / 2;
	vertex[4].x = CPos.x + (Width / 1.6f) / 2;
	vertex[4].y = (CPos.y + Height / 2 + Height / 8) - (Height / 4) / 2;
	vertex[5].x = CPos.x - (Width / 1.6f) / 2;
	vertex[5].y = (CPos.y + Height / 2 + Height / 8) + (Height / 4) / 2;
	vertex[6].x = CPos.x + (Width / 1.6f) / 2;
	vertex[6].y = (CPos.y + Height / 2 + Height / 8) + (Height / 4) / 2;

	//持ち手の部分四角形縦長
	vertex[7].x = CPos.x - (Width / 4) / 2;
	vertex[7].y = (CPos.y + Height) - (Height / 2) / 2;
	vertex[8].x = CPos.x + (Width / 4) / 2;
	vertex[8].y = (CPos.y + Height) - (Height / 2) / 2;
	vertex[9].x = CPos.x - (Width / 4) / 2;
	vertex[9].y = (CPos.y + Height) + (Height / 2) / 2;
	vertex[10].x = CPos.x + (Width / 4) / 2;
	vertex[10].y = (CPos.y + Height) + (Height / 2) / 2;


}

float  clamp(float value, float min, float max) {
	// valueが範囲外の場合、範囲内に収める
	if (value < min) {
		return min;
	} else if (value > max) {
		return max;
	} else {
		return value;
	}
}
float  easeClampRe(float t, float& easeDir) {
	if (t < 0) {
		easeDir *= -1;
		return 0;
	} else if (t > 1) {
		easeDir *= -1;
		return 1;
	} else {
		return t;
	}

}

float  easeClampOnce(float t, float& easeDir, bool& isEase) {
	if (t < 0) {
		isEase = false;
		easeDir *= -1;
		return 0;
	} else if (t > 1) {
		easeDir *= -1;
		return 1;
	} else {
		return t;
	}

}

float  easeClamphalf(float t, float& easeDir, bool& isEase) {
	if (t < 0.0f) {
		isEase = false;
		easeDir *= -1;
		return 0.0f;
	} else if (t > 1.0f) {
		isEase = false;
		easeDir *= -1;
		return 1.0f;
	} else {
		return t;
	}

}

//反転しない1で停止
float easeClamphalfE(float t) {
	if (t < 0.0f) {
		return 0.0f;
	} else if (t > 1.0f) {
		return 1.0f;
	} else {
		return t;
	}

};


//無限にイージング
float easeClampReW(float t, float& easeDir, int& waitTimer, int kmaxTimer) {

	if (t < 0) {
		waitTimer -= 1;
		if (waitTimer == 0) {
			easeDir *= -1;
			waitTimer = kmaxTimer;
		}
		return 0;
	} else if (t > 1) {
		waitTimer -= 1;
		if (waitTimer == 0) {
			easeDir *= -1;
			waitTimer = kmaxTimer;
		}
		return 1;
	} else {
		return t;
	}

}
//0~1~0の一回で終了
float easeClampOnceW(float& t, float& easeDir, bool& isEase, int& waitTimer, int kmaxTimer) {
	if (t < 0) {
		isEase = false;
		easeDir *= -1;
		return 0;
	} else if (t > 1) {
		waitTimer -= 1;
		if (waitTimer == 0) {
			easeDir *= -1;
			waitTimer = kmaxTimer;
		}
		return 1;
	} else {
		return t;
	}

}
//0~1onceの半分で終了
float easeClamphalfW(float t, float& easeDir, bool& isEase, int& waitTimer, int kmaxTimer) {
	if (t < 0.0f) {

		waitTimer -= 1;
		if (waitTimer == 0) {
			easeDir *= -1;
			isEase = false;
			waitTimer = kmaxTimer;

		}
		return 0.0f;
	} else if (t > 1.0f) {

		waitTimer -= 1;
		if (waitTimer == 0) {
			easeDir *= -1;
			isEase = false;
			waitTimer = kmaxTimer;

		}
		return 1.0f;
	} else {
		return t;
	}

}



unsigned int clampColor(unsigned int& value, unsigned int min, unsigned int max, float t) {
	// valueが範囲外の場合、範囲内に収める
	if (t < 0) {
		return min;
	}

	if (t > 1) {
		return max;
	}

	if (value < min) {
		return min;
	} else if (value > max) {
		return max;
	} else {
		return value;
	}
}

void Vector2ScreenPrint(int x, int y, Vector2 vector) {
	static const int kColumnWidthvec2 = 44;
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidthvec2, y, "%.02f", vector.y);

}



void MyDrawQuad(Vector2 vertex[4], int GH, int srcX, int srcY, int srcW, int srcH, unsigned int color) {
	Novice::DrawQuad(int(vertex[0].x), int(vertex[0].y), int(vertex[1].x), int(vertex[1].y),
		int(vertex[2].x), int(vertex[2].y), int(vertex[3].x), int(vertex[3].y), srcX, srcY, srcW, srcH, GH, color);

}

void MyDrawLine(Vector2 startpos, Vector2 endpos, unsigned int color) {
	Novice::DrawLine(int(startpos.x), int(startpos.y), int(endpos.x), int(endpos.y), color);

}

/*-----------------------------------------------------------------------*/
//
//								3次元ベクトル
//
/*-----------------------------------------------------------------------*/


void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	static const int kColumnWidthvec3 = 60;
	static const int kRowHeightvec3 = 20;

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidthvec3, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidthvec3 * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidthvec3 * 3, y, "%s", label);
}

Vector3 Vector3Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {
	v1.x + v2.x,
	v1.y + v2.y,
	v1.z + v2.z };
	return result;
}

Vector3 Vector3Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {
	v1.x - v2.x,
	v1.y - v2.y,
	v1.z - v2.z };

	return result;
}
Vector3 Vector3Multiply(float scalar, const Vector3& v) {
	Vector3 result = {
	v.x * scalar,
	v.y * scalar,
	v.z * scalar };

	return result;
}
float Vector3Dot(const Vector3& v1, const Vector3& v2) {

	float result = { (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) };
	return result;
}
float Vector3Length(const Vector3& v) {
	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}
Vector3 Vector3Normalize(const Vector3& v) {
	Vector3 result = { 0,0,0 };
	float length = Vector3Length(v);

	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}

	return result;
}






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

//1.行列の加法
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result = { 0 };
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}
	return result;
}

//2.行列の減法
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result = { 0 };
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}
	return result;
};
//3.行列の積
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result = { 0 };

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = (matrix1.m[i][0] * matrix2.m[0][j]) + (matrix1.m[i][1] * matrix2.m[1][j]);
		}
	}
	return result;
};
//4.ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 result = { 0 };
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];
	return result;
}

//2x2行列の逆行列を生成
Matrix2x2 Inverse2x2(Matrix2x2 matrix) {

	float scalar = (1 / ((matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[0][1] * matrix.m[1][0])));

	Matrix2x2 m1 = { 0 };
	m1.m[0][0] = matrix.m[1][1];
	m1.m[0][1] = -matrix.m[0][1];
	m1.m[1][0] = -matrix.m[1][0];
	m1.m[1][1] = matrix.m[0][0];

	Matrix2x2 result = { 0 };

	//行列のスカラー倍
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			result.m[i][j] = scalar * m1.m[i][j];
		}
	}

	return result;
};

//2x2転置行列を求める
Matrix2x2 Transpose2x2(Matrix2x2 matrix) {
	Matrix2x2 result = { 0 };
	//対称になるように変更
	result.m[1][0] = matrix.m[0][1];
	result.m[0][1] = matrix.m[1][0];

	//軸なので変わらない
	result.m[0][0] = matrix.m[0][0];
	result.m[1][1] = matrix.m[1][1];

	return result;
};


//2x2の行列を描画 
void MatriXScreenPrint2x2(int x, int y, Matrix2x2 matrix) {
	static const int kRowHeight2x2 = 20;
	static const int kColumnWidth2x2 = 44;
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth2x2,
				y + row * kRowHeight2x2, "%.02f ", matrix.m[row][column]);
		}
	}
}

/*-----------------------------------------------------------------------*/
//
//								3x3
//
/*-----------------------------------------------------------------------*/

Matrix3x3 Add(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}
	return result;
};

Matrix3x3 Subtract(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}
	return result;
};

//行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {

	Matrix3x3 result = { 0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = (matrix1.m[i][0] * matrix2.m[0][j]) + (matrix1.m[i][1] * matrix2.m[1][j]) + (matrix1.m[i][2] * matrix2.m[2][j]);
		}
	}

	return result;
};





//回転行列
Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 RotateMatrix = { 0 };

	RotateMatrix.m[0][0] = cosf(theta);
	RotateMatrix.m[0][1] = sinf(theta);
	RotateMatrix.m[0][2] = 0;
	RotateMatrix.m[1][0] = -sinf(theta);
	RotateMatrix.m[1][1] = cosf(theta);
	RotateMatrix.m[1][2] = 0;
	RotateMatrix.m[2][0] = 0;
	RotateMatrix.m[2][1] = 0;
	RotateMatrix.m[2][2] = 1;
	return RotateMatrix;

}

//平行移動行列
Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 TranslateMatrix = { 0 };

	TranslateMatrix.m[0][0] = 1;
	TranslateMatrix.m[0][1] = 0;
	TranslateMatrix.m[0][2] = 0;
	TranslateMatrix.m[1][0] = 0;
	TranslateMatrix.m[1][1] = 1;
	TranslateMatrix.m[1][2] = 0;
	TranslateMatrix.m[2][0] = translate.x;
	TranslateMatrix.m[2][1] = translate.y;
	TranslateMatrix.m[2][2] = 1;

	return TranslateMatrix;
};

//拡大縮小行列
Matrix3x3 MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 ScaleMatrix = { 0 };

	ScaleMatrix.m[0][0] = scale.x;
	ScaleMatrix.m[0][1] = 0;
	ScaleMatrix.m[0][2] = 0;
	ScaleMatrix.m[1][0] = 0;
	ScaleMatrix.m[1][1] = scale.y;
	ScaleMatrix.m[1][2] = 0;
	ScaleMatrix.m[2][0] = 0;
	ScaleMatrix.m[2][1] = 0;
	ScaleMatrix.m[2][2] = 1;

	return ScaleMatrix;
};

//アフィン行列
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	Matrix3x3 AffineMatrix = { 0 };
	AffineMatrix.m[0][0] = scale.x * cosf(rotate);
	AffineMatrix.m[0][1] = scale.x * sinf(rotate);
	AffineMatrix.m[0][2] = 0;
	AffineMatrix.m[1][0] = scale.y * -sinf(rotate);
	AffineMatrix.m[1][1] = scale.y * cosf(rotate);
	AffineMatrix.m[1][2] = 0;
	AffineMatrix.m[2][0] = translate.x;
	AffineMatrix.m[2][1] = translate.y;
	AffineMatrix.m[2][2] = 1;

	return AffineMatrix;
};

//行列変換
Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result = { 0 };//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);//bベクトルに対して基本的な操作を行う秒列ではｗ＝０にならない
	result.x /= w;
	result.y /= w;

	return result;

};

//3x3行列の逆行列を生成
Matrix3x3 Inverse3x3(Matrix3x3 matrix) {
	float scalar = 1 /
		((matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]) +
			(matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]) +

			(matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]) -
			(matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]) -

			(matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]) -
			(matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1]));

	Matrix3x3 m1 = { 0 };
	m1.m[0][0] = matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1];
	m1.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	m1.m[0][2] = matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1];

	m1.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	m1.m[1][1] = matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0];
	m1.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);

	m1.m[2][0] = matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0];
	m1.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	m1.m[2][2] = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];


	Matrix3x3 result = { 0 };

	//行列のスカラー倍
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = scalar * m1.m[i][j];
		}
	}

	return result;
};

//3x3転置行列を求める
Matrix3x3 Transpose3x3(Matrix3x3 matrix) {
	Matrix3x3 result = { 0 };
	//対称になるように変更
	result.m[0][1] = matrix.m[1][0];
	result.m[0][2] = matrix.m[2][0];
	result.m[1][0] = matrix.m[0][1];
	result.m[1][2] = matrix.m[2][1];
	result.m[2][1] = matrix.m[1][2];
	result.m[2][0] = matrix.m[0][2];

	//軸なので変わらない
	result.m[0][0] = matrix.m[0][0];
	result.m[1][1] = matrix.m[1][1];
	result.m[2][2] = matrix.m[2][2];

	return result;
};




//正射影行列を生成
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 OrthographicMatrix = { 0 };


	OrthographicMatrix.m[0][0] = 2.0f / (right - left);

	OrthographicMatrix.m[1][1] = 2.0f / (top - bottom);

	OrthographicMatrix.m[2][0] = (left + right) / (left - right);
	OrthographicMatrix.m[2][1] = (top + bottom) / (bottom - top);
	OrthographicMatrix.m[2][2] = 1;

	return OrthographicMatrix;
};

//ビューポート行列を生成
Matrix3x3 MakeviewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 viewportMatrix = { 0 };

	viewportMatrix.m[0][0] = width / 2;
	viewportMatrix.m[1][1] = -(height / 2);
	viewportMatrix.m[2][0] = left + (width / 2);
	viewportMatrix.m[2][1] = top + (height / 2);
	viewportMatrix.m[2][2] = 1;


	return viewportMatrix;
};

//レンダリングパイプラインを生成
Matrix3x3 MakeWvpVpMatrix(Vector2 localPos, Matrix3x3 worldMatrix, Matrix3x3 viewMatrix, Matrix3x3 orthoMatrix, Matrix3x3 viewportMatrix) {

	Matrix3x3 wvpVpMatrix = { 0 };
	worldMatrix = MakeTranslateMatrix(localPos);
	wvpVpMatrix = Multiply(worldMatrix, viewMatrix);
	wvpVpMatrix = Multiply(wvpVpMatrix, orthoMatrix);
	wvpVpMatrix = Multiply(wvpVpMatrix, viewportMatrix);

	return wvpVpMatrix;
}

//3ｘ3の行列を描画
void MatriXScreenPrint3x3(int x, int y, Matrix3x3 matrix) {
	static const int kRowHeight3x3 = 20;
	static const int kColumnWidth3x3 = 54;

	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth3x3,
				y + row * kRowHeight3x3, "%.02f ", matrix.m[row][column]);
		}
	}
};

/*-----------------------------------------------------------------------*/
//
//								4x4
//
/*-----------------------------------------------------------------------*/




//4x4の行列の数値を表示する
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	static const int kRowHeight4x4 = 20;
	static const int kColumnWidth4x4 = 60;
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth4x4, y + (row + 1) * kRowHeight4x4, "%6.02f", matrix.m[row][column]);
		}
	}

}

// 1. 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;
}

// 2. 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}

// 3. 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = {
				(m1.m[i][0] * m2.m[0][j]) +
				(m1.m[i][1] * m2.m[1][j]) +
				(m1.m[i][2] * m2.m[2][j]) +
				(m1.m[i][3] * m2.m[3][j])
			};
		}
	}

	return result;
}

// 4. 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	//|A|を求める
	float A = {
		1 /
		((m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
		(m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
		(m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2])

		- (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
			(m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
			(m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2])

		- (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
			(m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
			(m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2])

		+ (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2])

		+ (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2])

		- (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2])

		- (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0])

		+ (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0])
			)
	};


	//00_02のP11　１/｜A｜の後ろを書く
	Matrix4x4 m1 = { 0 };
	m1.m[0][0] = (
		(m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) + (m.m[1][3] * m.m[2][1] * m.m[3][2])
		- (m.m[1][3] * m.m[2][2] * m.m[3][1]) - (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2])
		);
	m1.m[0][1] = (
		-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ (m.m[0][3] * m.m[2][2] * m.m[3][1]) + (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2])
		);
	m1.m[0][2] = (
		(m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) + (m.m[0][3] * m.m[1][1] * m.m[3][2])
		- (m.m[0][3] * m.m[1][2] * m.m[3][1]) - (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2])
		);

	m1.m[0][3] = (
		-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) - (m.m[0][3] * m.m[1][1] * m.m[2][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[2][1]) + (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2])
		);


	m1.m[1][0] = (
		-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) - (m.m[1][3] * m.m[2][0] * m.m[3][2])
		+ (m.m[1][3] * m.m[2][2] * m.m[3][0]) + (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2])
		);

	m1.m[1][1] = (
		(m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) + (m.m[0][3] * m.m[2][0] * m.m[3][2])
		- (m.m[0][3] * m.m[2][2] * m.m[3][0]) - (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2])
		);

	m1.m[1][2] = (
		-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ (m.m[0][3] * m.m[1][2] * m.m[3][0]) + (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2])
		);

	m1.m[1][3] = (
		(m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) + (m.m[0][3] * m.m[1][0] * m.m[2][2])
		- (m.m[0][3] * m.m[1][2] * m.m[2][0]) - (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2])
		);


	m1.m[2][0] = (
		(m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) + (m.m[1][3] * m.m[2][0] * m.m[3][1])
		- (m.m[1][3] * m.m[2][1] * m.m[3][0]) - (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1])
		);

	m1.m[2][1] = (
		-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ (m.m[0][3] * m.m[2][1] * m.m[3][0]) + (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1])
		);

	m1.m[2][2] = (
		(m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) + (m.m[0][3] * m.m[1][0] * m.m[3][1])
		- (m.m[0][3] * m.m[1][1] * m.m[3][0]) - (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1])
		);

	m1.m[2][3] = (
		-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ (m.m[0][3] * m.m[1][1] * m.m[2][0]) + (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1])
		);


	m1.m[3][0] = (
		-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ (m.m[1][2] * m.m[2][1] * m.m[3][0]) + (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1])
		);

	m1.m[3][1] = (
		(m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) + (m.m[0][2] * m.m[2][0] * m.m[3][1])
		- (m.m[0][2] * m.m[2][1] * m.m[3][0]) - (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1])
		);

	m1.m[3][2] = (
		-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ (m.m[0][2] * m.m[1][1] * m.m[3][0]) + (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1])
		);

	m1.m[3][3] = (
		(m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) + (m.m[0][2] * m.m[1][0] * m.m[2][1])
		- (m.m[0][2] * m.m[1][1] * m.m[2][0]) - (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1])
		);


	Matrix4x4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = A * m1.m[i][j];
		}
	}

	return result;
}

// 5. 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = { m.m[j][i] };
		}
	}


	return result;
}

// 6. 単位行列の生成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//0を入れる
			result.m[i][j] = 0;
			//iとjの値が同じ時に1を入れる
			if (i == j) {
				result.m[i][j] = 1;
			}
		}
	}
	return result;
};

//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 TranslateMatrix = { 0 };

	TranslateMatrix.m[0][0] = 1;
	TranslateMatrix.m[0][1] = 0;
	TranslateMatrix.m[0][2] = 0;
	TranslateMatrix.m[0][3] = 0;

	TranslateMatrix.m[1][0] = 0;
	TranslateMatrix.m[1][1] = 1;
	TranslateMatrix.m[1][2] = 0;
	TranslateMatrix.m[1][3] = 0;

	TranslateMatrix.m[2][0] = 0;
	TranslateMatrix.m[2][1] = 0;
	TranslateMatrix.m[2][2] = 1;
	TranslateMatrix.m[2][3] = 0;

	TranslateMatrix.m[3][0] = translate.x;
	TranslateMatrix.m[3][1] = translate.y;
	TranslateMatrix.m[3][2] = translate.z;
	TranslateMatrix.m[3][3] = 1;

	return TranslateMatrix;
};

//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 	ScaleMatrix = { 0 };

	ScaleMatrix.m[0][0] = scale.x;
	ScaleMatrix.m[0][1] = 0;
	ScaleMatrix.m[0][2] = 0;
	ScaleMatrix.m[0][3] = 0;

	ScaleMatrix.m[1][0] = 0;
	ScaleMatrix.m[1][1] = scale.y;
	ScaleMatrix.m[1][2] = 0;
	ScaleMatrix.m[1][3] = 0;

	ScaleMatrix.m[2][0] = 0;
	ScaleMatrix.m[2][1] = 0;
	ScaleMatrix.m[2][2] = scale.z;
	ScaleMatrix.m[2][3] = 0;

	ScaleMatrix.m[3][0] = 0;
	ScaleMatrix.m[3][1] = 0;
	ScaleMatrix.m[3][2] = 0;
	ScaleMatrix.m[3][3] = 1;

	return ScaleMatrix;
};

//3.座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result = { 0 };//w=1がデカルト座標系であるので(x,y,1)のベクトルとしてmatrixの積をとる
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];


	assert(w != 0.0f);//bベクトルに対して基本的な操作を行う秒列ではｗ＝０にならない
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

// 1 X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 RotateMatrix = { 0 };

	RotateMatrix.m[0][0] = 1;
	RotateMatrix.m[0][1] = 0;
	RotateMatrix.m[0][2] = 0;
	RotateMatrix.m[0][3] = 0;

	RotateMatrix.m[1][0] = 0;
	RotateMatrix.m[1][1] = std::cosf(radian);
	RotateMatrix.m[1][2] = std::sinf(radian);
	RotateMatrix.m[1][3] = 0;

	RotateMatrix.m[2][0] = 0;
	RotateMatrix.m[2][1] = -(std::sinf(radian));
	RotateMatrix.m[2][2] = std::cosf(radian);
	RotateMatrix.m[2][3] = 0;

	RotateMatrix.m[3][0] = 0;
	RotateMatrix.m[3][1] = 0;
	RotateMatrix.m[3][2] = 0;
	RotateMatrix.m[3][3] = 1;

	return RotateMatrix;
};

// 2 Y軸回転行列

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 RotateMatrix = { 0 };

	RotateMatrix.m[0][0] = std::cosf(radian);
	RotateMatrix.m[0][1] = 0;
	RotateMatrix.m[0][2] = -(std::sinf(radian));
	RotateMatrix.m[0][3] = 0;

	RotateMatrix.m[1][0] = 0;
	RotateMatrix.m[1][1] = 1;
	RotateMatrix.m[1][2] = 0;
	RotateMatrix.m[1][3] = 0;

	RotateMatrix.m[2][0] = std::sinf(radian);
	RotateMatrix.m[2][1] = 0;
	RotateMatrix.m[2][2] = std::cosf(radian);
	RotateMatrix.m[2][3] = 0;

	RotateMatrix.m[3][0] = 0;
	RotateMatrix.m[3][1] = 0;
	RotateMatrix.m[3][2] = 0;
	RotateMatrix.m[3][3] = 1;

	return RotateMatrix;


};

// 3 Z軸回転行列

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 RotateMatrix = { 0 };

	RotateMatrix.m[0][0] = std::cosf(radian);
	RotateMatrix.m[0][1] = std::sinf(radian);
	RotateMatrix.m[0][2] = 0;
	RotateMatrix.m[0][3] = 0;

	RotateMatrix.m[1][0] = -(std::sinf(radian));
	RotateMatrix.m[1][1] = std::cosf(radian);
	RotateMatrix.m[1][2] = 0;
	RotateMatrix.m[1][3] = 0;

	RotateMatrix.m[2][0] = 0;
	RotateMatrix.m[2][1] = 0;
	RotateMatrix.m[2][2] = 1;
	RotateMatrix.m[2][3] = 0;

	RotateMatrix.m[3][0] = 0;
	RotateMatrix.m[3][1] = 0;
	RotateMatrix.m[3][2] = 0;
	RotateMatrix.m[3][3] = 1;

	return RotateMatrix;



};
//  XYZ回転行列
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {

	Matrix4x4 RotateMatrix = { 0 };

	//RotateMatrix.m[0][0] = std::cosf(rotate.y) * std::cosf(rotate.z);
	//RotateMatrix.m[0][1] = std::sinf(rotate.z);
	//RotateMatrix.m[0][2] = -(std::sinf(rotate.y));
	//RotateMatrix.m[0][3] = 0;

	//RotateMatrix.m[1][0] = -(std::sinf(rotate.z));
	//RotateMatrix.m[1][1] = std::cosf(rotate.x) * std::cosf(rotate.z);
	//RotateMatrix.m[1][2] = std::sinf(rotate.x);
	//RotateMatrix.m[1][3] = 0;

	//RotateMatrix.m[2][0] = std::sinf(rotate.y);
	//RotateMatrix.m[2][1] = -(std::sinf(rotate.x));
	//RotateMatrix.m[2][2] = std::cosf(rotate.x) * std::cosf(rotate.y);
	//RotateMatrix.m[2][3] = 0;

	//RotateMatrix.m[3][0] = 0;
	//RotateMatrix.m[3][1] = 0;
	//RotateMatrix.m[3][2] = 0;
	//RotateMatrix.m[3][3] = 1;

	return RotateMatrix;


};