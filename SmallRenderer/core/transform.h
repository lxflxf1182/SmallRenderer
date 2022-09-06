#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"

class Transform {
	Matrix4f model_trans;
	Matrix4f view_trans;
	Matrix4f projection_trans;
	Matrix4f mvp_trans;
};

#endif
