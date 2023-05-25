#pragma once
#include <assert.h>
#include<cmath>
#include<stdio.h>
#include<Matrix4x4.h>
#include<Vector2.h>
#include<Vector3.h>

typedef struct Matrix2x2 {
	float m[2][2];
} Matrix2x2;

typedef struct Matrix3x3 {
	float m[3][3];
} Matrix3x3;



Matrix2x2 Add(Matrix2x2 a, Matrix2x2 b);
Matrix2x2 Subtract(Matrix2x2 a, Matrix2x2 b);
Matrix2x2 Multiply(Matrix2x2 a, Matrix2x2 b);

Vector2 Multiply(Vector2 v, Matrix2x2 b);
Matrix3x3 Multiply(Matrix3x3 a, Matrix3x3 b);

static const int kRowHeight = 20;
static const int kcolumnWidth = 54;





//Matrix2x2 MakeRotateMatrix(float theta);
//Matrix3x3 makeRotateMatrix(float theta);
//
//Matrix3x3 MakeTranslateMatrix(Vector2 translate);
//
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
//
//
//Matrix3x3 MakeTranslateMatrix(Vector2 translate);
//
//
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
//
//
//Matrix2x2 Inverse(Matrix2x2 a);
//
//Matrix3x3 Inverse(Matrix3x3 a);
//
//Matrix2x2 TransposeM1(Matrix2x2 a);
//
//Matrix3x3 TransposeM2(Matrix3x3 a);
//
//
//Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);
//
//Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);
//
Matrix3x3 Inverse3x3(Matrix3x3 a);

Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);


Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Multiply(float scalar, const Vector3& v);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v);



Matrix4x4 Add(Matrix4x4 a, Matrix4x4 b);

Matrix4x4 Subtract(Matrix4x4 a, Matrix4x4 b);

Matrix4x4 Multiply(Matrix4x4 a, Matrix4x4 b);

Matrix4x4 Inverse(Matrix4x4 a);

Matrix4x4 Transpose(Matrix4x4 a);

Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

Matrix4x4 MakerotateXMatrix(float radian);

Matrix4x4 MakerotateYMatrix(float radian);

Matrix4x4 MakerotateZMatrix(float radian);
Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 rotate, Vector3 translate);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//正射影
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//ビューポート
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
Vector3 Cross(const Vector3& v1, const Vector3& v2);