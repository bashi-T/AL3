#pragma once
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];
};

Matrix4x4 Add(Matrix4x4 a, Matrix4x4 b) {
	Matrix4x4 add;
	add.m[0][0] = a.m[0][0] + b.m[0][0];
	add.m[0][1] = a.m[0][1] + b.m[0][1];
	add.m[0][2] = a.m[0][2] + b.m[0][2];
	add.m[0][3] = a.m[0][3] + b.m[0][3];
	add.m[1][0] = a.m[1][0] + b.m[1][0];
	add.m[1][1] = a.m[1][1] + b.m[1][1];
	add.m[1][2] = a.m[1][2] + b.m[1][2];
	add.m[1][3] = a.m[1][3] + b.m[1][3];
	add.m[2][0] = a.m[2][0] + b.m[2][0];
	add.m[2][1] = a.m[2][1] + b.m[2][1];
	add.m[2][2] = a.m[2][2] + b.m[2][2];
	add.m[2][3] = a.m[2][3] + b.m[2][3];
	add.m[3][0] = a.m[3][0] + b.m[3][0];
	add.m[3][1] = a.m[3][1] + b.m[3][1];
	add.m[3][2] = a.m[3][2] + b.m[3][2];
	add.m[3][3] = a.m[3][3] + b.m[3][3];
	return add;
}

Matrix4x4 Subtract(Matrix4x4 a, Matrix4x4 b) {
	Matrix4x4 subtract;
	subtract.m[0][1] = a.m[0][1] - b.m[0][1];
	subtract.m[0][0] = a.m[0][0] - b.m[0][0];
	subtract.m[0][2] = a.m[0][2] - b.m[0][2];
	subtract.m[0][3] = a.m[0][3] - b.m[0][3];
	subtract.m[1][0] = a.m[1][0] - b.m[1][0];
	subtract.m[1][1] = a.m[1][1] - b.m[1][1];
	subtract.m[1][2] = a.m[1][2] - b.m[1][2];
	subtract.m[1][3] = a.m[1][3] - b.m[1][3];
	subtract.m[2][0] = a.m[2][0] - b.m[2][0];
	subtract.m[2][1] = a.m[2][1] - b.m[2][1];
	subtract.m[2][2] = a.m[2][2] - b.m[2][2];
	subtract.m[2][3] = a.m[2][3] - b.m[2][3];
	subtract.m[3][0] = a.m[3][0] - b.m[3][0];
	subtract.m[3][1] = a.m[3][1] - b.m[3][1];
	subtract.m[3][2] = a.m[3][2] - b.m[3][2];
	subtract.m[3][3] = a.m[3][3] - b.m[3][3];
	return subtract;
}

Matrix4x4 Multiply(Matrix4x4 a, Matrix4x4 b) {
	Matrix4x4 multiply;
	multiply.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0]
		+ a.m[0][2] * b.m[2][0] + a.m[0][3] * b.m[3][0];
	multiply.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1]
		+ a.m[0][2] * b.m[2][1] + a.m[0][3] * b.m[3][1];
	multiply.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2]
		+ a.m[0][2] * b.m[2][2] + a.m[0][3] * b.m[3][2];
	multiply.m[0][3] = a.m[0][0] * b.m[0][3] + a.m[0][1] * b.m[1][3]
		+ a.m[0][2] * b.m[2][3] + a.m[0][3] * b.m[3][3];
	multiply.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0]
		+ a.m[1][2] * b.m[2][0] + a.m[1][3] * b.m[3][0];
	multiply.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1]
		+ a.m[1][2] * b.m[2][1] + a.m[1][3] * b.m[3][1];
	multiply.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2]
		+ a.m[1][2] * b.m[2][2] + a.m[1][3] * b.m[3][2];
	multiply.m[1][3] = a.m[1][0] * b.m[0][3] + a.m[1][1] * b.m[1][3]
		+ a.m[1][2] * b.m[2][3] + a.m[1][3] * b.m[3][3];
	multiply.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0]
		+ a.m[2][2] * b.m[2][0] + a.m[2][3] * b.m[3][0];
	multiply.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1]
		+ a.m[2][2] * b.m[2][1] + a.m[2][3] * a.m[3][1];
	multiply.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2]
		+ a.m[2][2] * b.m[2][2] + a.m[2][3] * b.m[3][2];
	multiply.m[2][3] = a.m[2][0] * b.m[0][3] + a.m[2][1] * b.m[1][3]
		+ a.m[2][2] * b.m[2][3] + a.m[2][3] * b.m[3][3];
	multiply.m[3][0] = a.m[3][0] * b.m[3][0] + a.m[3][1] * b.m[1][0]
		+ a.m[3][2] * b.m[2][0] + a.m[3][3] * b.m[3][0];
	multiply.m[3][1] = a.m[3][0] * b.m[0][1] + a.m[3][1] * b.m[1][1]
		+ a.m[3][2] * b.m[2][1] + a.m[3][3] * b.m[3][1];
	multiply.m[3][2] = a.m[3][0] * b.m[0][2] + a.m[3][1] * b.m[1][2]
		+ a.m[3][2] * b.m[2][2] + a.m[3][3] * b.m[3][2];
	multiply.m[3][3] = a.m[3][0] * b.m[0][3] + a.m[3][1] * b.m[1][3]
		+ a.m[3][2] * b.m[2][3] + a.m[3][3] * b.m[3][3];

	return multiply;
}

Matrix4x4 Inverse(Matrix4x4 a) {
	Matrix4x4 result;
	float x = a.m[0][0] * a.m[1][1] * a.m[2][2] * a.m[3][3] +
		a.m[0][0] * a.m[1][2] * a.m[2][3] * a.m[3][1] +
		a.m[0][0] * a.m[1][3] * a.m[2][1] * a.m[3][2] -
		a.m[0][0] * a.m[1][3] * a.m[2][2] * a.m[3][1] -
		a.m[0][0] * a.m[1][2] * a.m[2][1] * a.m[3][3] -
		a.m[0][0] * a.m[1][1] * a.m[2][3] * a.m[3][1] -
		a.m[0][1] * a.m[1][0] * a.m[2][2] * a.m[3][3] -
		a.m[0][2] * a.m[1][0] * a.m[2][3] * a.m[3][1] -
		a.m[0][3] * a.m[1][0] * a.m[2][1] * a.m[3][2] +
		a.m[0][3] * a.m[1][0] * a.m[2][2] * a.m[3][1] +
		a.m[0][2] * a.m[1][0] * a.m[2][1] * a.m[3][3] +
		a.m[0][1] * a.m[1][0] * a.m[2][3] * a.m[3][2] +
		a.m[0][1] * a.m[1][2] * a.m[2][0] * a.m[3][3] +
		a.m[0][2] * a.m[1][3] * a.m[2][0] * a.m[3][1] +
		a.m[0][3] * a.m[1][1] * a.m[2][0] * a.m[3][2] -
		a.m[0][3] * a.m[1][2] * a.m[2][0] * a.m[3][1] -
		a.m[0][2] * a.m[1][1] * a.m[2][0] * a.m[3][3] -
		a.m[0][1] * a.m[1][3] * a.m[2][0] * a.m[3][2] -
		a.m[0][1] * a.m[1][2] * a.m[2][3] * a.m[3][0] -
		a.m[0][2] * a.m[1][3] * a.m[2][1] * a.m[3][0] -
		a.m[0][3] * a.m[1][1] * a.m[2][2] * a.m[3][0] +
		a.m[0][3] * a.m[1][2] * a.m[2][1] * a.m[3][0] +
		a.m[0][2] * a.m[1][1] * a.m[2][3] * a.m[3][0] +
		a.m[0][1] * a.m[1][3] * a.m[2][2] * a.m[3][0];


	if (x != 0) {
		result.m[0][0] = 1 / x *
			(a.m[1][1] * a.m[2][2] * a.m[3][3] + a.m[1][2] * a.m[2][3] * a.m[3][1] + a.m[1][3] * a.m[2][1] * a.m[3][2]
				- a.m[1][3] * a.m[2][2] * a.m[3][1] - a.m[1][2] * a.m[2][1] * a.m[3][3] - a.m[1][1] * a.m[2][3] * a.m[3][2]);

		result.m[0][1] = 1 / x *
			(-a.m[0][1] * a.m[2][2] * a.m[3][3] - a.m[0][2] * a.m[2][3] * a.m[3][1] - a.m[0][3] * a.m[2][1] * a.m[3][2]
				+ a.m[0][3] * a.m[2][2] * a.m[3][1] + a.m[1][2] * a.m[2][1] * a.m[3][3] + a.m[0][1] * a.m[2][3] * a.m[3][2]);

		result.m[0][2] = 1 / x *
			(a.m[0][1] * a.m[1][2] * a.m[3][3] + a.m[0][2] * a.m[1][3] * a.m[3][1] + a.m[0][3] * a.m[1][1] * a.m[3][2]
				- a.m[0][3] * a.m[1][2] * a.m[3][1] - a.m[0][2] * a.m[1][1] * a.m[3][3] - a.m[0][1] * a.m[1][3] * a.m[3][2]);

		result.m[0][3] = 1 / x *
			(-a.m[0][1] * a.m[1][2] * a.m[2][3] - a.m[1][2] * a.m[1][3] * a.m[2][1] - a.m[0][3] * a.m[1][1] * a.m[2][2]
				+ a.m[0][3] * a.m[1][2] * a.m[2][1] - a.m[0][2] * a.m[1][1] * a.m[2][3] + a.m[0][1] * a.m[1][3] * a.m[2][2]);

		result.m[1][0] = 1 / x *
			(-a.m[1][0] * a.m[2][2] * a.m[3][3] - a.m[1][2] * a.m[2][3] * a.m[3][0] - a.m[1][3] * a.m[2][0] * a.m[3][2]
				+ a.m[1][3] * a.m[2][2] * a.m[3][0] + a.m[1][2] * a.m[2][0] * a.m[3][3] + a.m[1][0] * a.m[2][3] * a.m[3][2]);

		result.m[1][1] = 1 / x *
			(a.m[0][0] * a.m[2][2] * a.m[3][3] + a.m[0][2] * a.m[2][3] * a.m[3][0] + a.m[0][3] * a.m[2][0] * a.m[3][2]
				- a.m[0][3] * a.m[2][2] * a.m[3][0] - a.m[0][2] * a.m[2][0] * a.m[3][3] - a.m[0][0] * a.m[2][3] * a.m[3][2]);

		result.m[1][2] = 1 / x *
			(-a.m[0][0] * a.m[1][2] * a.m[3][3] - a.m[0][2] * a.m[1][3] * a.m[3][0] - a.m[0][3] * a.m[1][0] * a.m[3][2]
				+ a.m[0][3] * a.m[1][2] * a.m[3][0] + a.m[0][2] * a.m[1][0] * a.m[3][3] + a.m[0][0] * a.m[1][3] * a.m[3][2]);

		result.m[1][3] = 1 / x *
			(a.m[0][0] * a.m[1][2] * a.m[2][3] + a.m[0][2] * a.m[1][3] * a.m[2][0] + a.m[0][3] * a.m[1][0] * a.m[2][2]
				- a.m[0][3] * a.m[1][2] * a.m[2][0] - a.m[1][2] * a.m[1][0] * a.m[2][3] - a.m[0][0] * a.m[1][3] * a.m[2][2]);

		result.m[2][0] = 1 / x *
			(a.m[1][0] * a.m[2][1] * a.m[3][3] + a.m[1][1] * a.m[2][3] * a.m[3][0] + a.m[1][3] * a.m[2][0] * a.m[3][1]
				- a.m[1][3] * a.m[2][1] * a.m[3][0] - a.m[1][1] * a.m[2][0] * a.m[3][3] - a.m[1][0] * a.m[2][3] * a.m[3][1]);

		result.m[2][1] = 1 / x *
			(-a.m[0][0] * a.m[2][1] * a.m[3][3] - a.m[1][0] * a.m[2][3] * a.m[3][0] - a.m[0][3] * a.m[2][0] * a.m[3][1]
				+ a.m[0][3] * a.m[2][1] * a.m[3][0] + a.m[0][1] * a.m[2][0] * a.m[3][3] + a.m[0][0] * a.m[2][3] * a.m[3][1]);

		result.m[2][2] = 1 / x *
			(a.m[0][0] * a.m[1][1] * a.m[3][3] + a.m[0][1] * a.m[1][3] * a.m[3][0] + a.m[0][3] * a.m[1][0] * a.m[3][1]
				- a.m[0][3] * a.m[1][1] * a.m[3][0] - a.m[0][1] * a.m[1][3] * a.m[2][0] - a.m[0][0] * a.m[1][3] * a.m[3][1]);

		result.m[2][3] = 1 / x *
			(-a.m[0][0] * a.m[1][1] * a.m[2][3] - a.m[0][1] * a.m[1][3] * a.m[2][0] - a.m[0][3] * a.m[1][0] * a.m[2][1]
				+ a.m[0][3] * a.m[1][1] * a.m[2][0] + a.m[0][1] * a.m[1][0] * a.m[2][3] + a.m[0][0] * a.m[1][3] * a.m[2][1]);

		result.m[3][0] = 1 / x *
			(-a.m[1][0] * a.m[2][1] * a.m[3][2] - a.m[1][1] * a.m[2][2] * a.m[3][0] - a.m[1][2] * a.m[2][0] * a.m[3][1]
				+ a.m[1][2] * a.m[2][1] * a.m[3][0] + a.m[1][1] * a.m[2][0] * a.m[3][2] + a.m[1][0] * a.m[2][2] * a.m[3][1]);

		result.m[3][1] = 1 / x *
			(a.m[0][0] * a.m[2][1] * a.m[3][2] + a.m[0][1] * a.m[2][2] * a.m[3][0] + a.m[0][2] * a.m[2][0] * a.m[3][1]
				- a.m[0][2] * a.m[2][1] * a.m[3][0] - a.m[0][1] * a.m[2][0] * a.m[3][2] - a.m[0][0] * a.m[2][2] * a.m[3][1]);

		result.m[3][2] = 1 / x *
			(-a.m[0][0] * a.m[1][1] * a.m[3][2] - a.m[0][1] * a.m[1][2] * a.m[3][0] - a.m[0][2] * a.m[1][0] * a.m[3][1]
				+ a.m[0][2] * a.m[1][1] * a.m[3][0] + a.m[0][1] * a.m[1][0] * a.m[3][2] + a.m[0][0] * a.m[1][2] * a.m[3][1]);

		result.m[3][3] = 1 / x *
			(a.m[0][0] * a.m[1][1] * a.m[2][2] + a.m[0][1] * a.m[1][2] * a.m[2][0] + a.m[0][2] * a.m[1][0] * a.m[2][1]
				- a.m[0][2] * a.m[1][1] * a.m[2][0] - a.m[0][1] * a.m[1][0] * a.m[2][2] - a.m[0][0] * a.m[1][2] * a.m[2][1]);

	}
	return result;
}

Matrix4x4 Transpose(Matrix4x4 a) {
	Matrix4x4 result;
	result.m[0][0] = a.m[0][0];
	result.m[1][0] = a.m[0][1];
	result.m[2][0] = a.m[0][2];
	result.m[3][0] = a.m[0][3];
	result.m[0][1] = a.m[1][0];
	result.m[1][1] = a.m[1][1];
	result.m[2][1] = a.m[1][2];
	result.m[3][1] = a.m[1][3];
	result.m[0][2] = a.m[2][0];
	result.m[1][2] = a.m[2][1];
	result.m[2][2] = a.m[2][2];
	result.m[3][2] = a.m[2][3];
	result.m[0][3] = a.m[3][0];
	result.m[1][3] = a.m[3][1];
	result.m[2][3] = a.m[3][2];
	result.m[3][3] = a.m[3][3];
	return result;
}

Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;

}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}
Matrix4x4 MakerotateXMatrix(float radian) {
	Matrix4x4 rotate;
	rotate.m[0][0] = 1.0f;
	rotate.m[0][1] = 0.0f;
	rotate.m[0][2] = 0.0f;
	rotate.m[0][3] = 0.0f;
	rotate.m[1][0] = 0.0f;
	rotate.m[1][1] = std::cos(radian);
	rotate.m[1][2] = std::sin(radian);
	rotate.m[1][3] = 0.0f;
	rotate.m[2][0] = 0.0f;
	rotate.m[2][1] = -std::sin(radian);
	rotate.m[2][2] = std::cos(radian);
	rotate.m[2][3] = 0.0f;
	rotate.m[3][0] = 0.0f;
	rotate.m[3][1] = 0.0f;
	rotate.m[3][2] = 0.0f;
	rotate.m[3][3] = 1.0f;

	return rotate;
}

Matrix4x4 MakerotateYMatrix(float radian) {
	Matrix4x4 rotate;
	rotate.m[0][0] = std::cos(radian);
	rotate.m[0][1] = 0.0f;
	rotate.m[0][2] = -std::sin(radian);
	rotate.m[0][3] = 0.0f;
	rotate.m[1][0] = 0.0f;
	rotate.m[1][1] = 1.0f;
	rotate.m[1][2] = 0.0f;
	rotate.m[1][3] = 0.0f;
	rotate.m[2][0] = std::sin(radian);
	rotate.m[2][1] = 0.0f;
	rotate.m[2][2] = std::cos(radian);
	rotate.m[2][3] = 0.0f;
	rotate.m[3][0] = 0.0f;
	rotate.m[3][1] = 0.0f;
	rotate.m[3][2] = 0.0f;
	rotate.m[3][3] = 1.0f;

	return rotate;

}

Matrix4x4 MakerotateZMatrix(float radian) {
	Matrix4x4 rotate;
	rotate.m[0][0] = std::cos(radian);
	rotate.m[0][1] = std::sin(radian);
	rotate.m[0][2] = 0.0f;
	rotate.m[0][3] = 0.0f;
	rotate.m[1][0] = -std::sin(radian);
	rotate.m[1][1] = std::cos(radian);
	rotate.m[1][2] = 0.0f;
	rotate.m[1][3] = 0.0f;
	rotate.m[2][0] = 0.0f;
	rotate.m[2][1] = 0.0f;
	rotate.m[2][2] = 1.0f;
	rotate.m[2][3] = 0.0f;
	rotate.m[3][0] = 0.0f;
	rotate.m[3][1] = 0.0f;
	rotate.m[3][2] = 0.0f;
	rotate.m[3][3] = 1.0f;

	return rotate;

}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result;
	Matrix4x4 rotateX = MakerotateXMatrix(rotate.x);
	Matrix4x4 rotateY = MakerotateYMatrix(rotate.y);
	Matrix4x4 rotateZ = MakerotateZMatrix(rotate.z);
	Matrix4x4 ROTATE = Multiply(rotateX, Multiply(rotateY, rotateZ));


	result.m[0][0] = scale.x * ROTATE.m[0][0];
	result.m[0][1] = scale.x * ROTATE.m[0][1];
	result.m[0][2] = scale.x * ROTATE.m[0][2];
	result.m[0][3] = 0.0f;
	result.m[1][0] = scale.y * ROTATE.m[1][0];
	result.m[1][1] = scale.y * ROTATE.m[1][1];
	result.m[1][2] = scale.y * ROTATE.m[1][2];
	result.m[1][3] = 0.0f;
	result.m[2][0] = scale.z * ROTATE.m[2][0];
	result.m[2][1] = scale.z * ROTATE.m[2][1];
	result.m[2][2] = scale.z * ROTATE.m[2][2];
	result.m[2][3] = 0.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;

};
