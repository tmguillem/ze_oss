// Copyright (c) 2014, Paul Furgale, Jérôme Maye and Jörn Rehder,
// Autonomous Systems Lab, ETH Zurich, Switzerland
// Copyright (c) 2014, Thomas Schneider, Skybotix AG, Switzerland
// Copyright (c) 2016, Luc Oth
// Copyright (C) 2016 ETH Zurich, Wyss Zurich, Zurich Eye
// All rights reserved.
//
// Adopted from https://github.com/ethz-asl/kalibr/ (2016)
// BSD Licensed
//
// Changes wrt. original:
//  _ remove dependency on Schweizer-Messer toolbox
//  _ remove dependency on sparse_block_matrix (drop support for sparse
//    initialization)
//
// WARNING: Do NOT use as-is in production code.

#pragma once

#include <ze/splines/bspline.hpp>
#include <ze/common/transformation.h>
#include <ze/splines/rotation_vector.hpp>
#include <ze/splines/operators.hpp>
#include <ze/common/macros.h>

namespace ze {

/**
 * @class BSpline
 *
 * A class to facilitate state estimation for vehicles in 3D space using B-Splines
 * The spline represents a pose with respect to some navigation frame
 * \f$ \mathbf F_n \f$.
 * The pose is represented as a 6d spline of a translational component and
 * a 3d minimal rotation parametrization.
 *
 */
template<class ROTATION>
class BSplinePoseMinimal : public BSpline
{
 public:
    ZE_POINTER_TYPEDEFS(BSplinePoseMinimal);

    /**
     * Create a spline of the specified order. The resulting B-spline will
     * be a series of piecewise polynomials of degree splineOrder - 1.
     *
     * @param splineOrder The order of the spline.
     */
    BSplinePoseMinimal(int spline_order);

    ~BSplinePoseMinimal();

    Matrix4 transformation(real_t tk) const;
    Matrix4 transformationAndJacobian(
        real_t tk,
        MatrixX* J = NULL,
        VectorXi* coefficient_indices = NULL) const;

    Matrix4 inverseTransformationAndJacobian(
        real_t tk,
        MatrixX* J = NULL,
        VectorXi* coefficient_indices = NULL) const;

    Matrix4 inverseTransformation(real_t tk) const;


    Vector4 transformVectorAndJacobian(
        real_t tk,
        const Vector4& v,
        MatrixX* J = NULL,
        VectorXi* coefficient_indices = NULL) const;

    Vector3 position(real_t tk) const;

    Matrix3 orientation(real_t tk) const;
    Matrix3 orientationAndJacobian(
        real_t tk,
        MatrixX* J,
        VectorXi* coefficient_indices) const;

    Matrix3 inverseOrientation(real_t tk) const;
    Matrix3 inverseOrientationAndJacobian(
        real_t tk,
        MatrixX* J,
        VectorXi* coefficient_indices) const;

    Vector3 linearVelocity(real_t tk) const;
    Vector3 linearVelocityBodyFrame(real_t tk) const;

    Vector3 linearAcceleration(real_t tk) const;
    Vector3 linearAccelerationBodyFrame(real_t tk) const;
    Vector3 linearAccelerationAndJacobian(
        real_t tk,
        MatrixX* J,
        VectorXi* coefficient_indices) const;

    Vector3 angularVelocity(real_t tk) const;
    Vector3 angularVelocityBodyFrame(real_t tk) const;
    Vector3 angularVelocityBodyFrameAndJacobian(
        real_t tk,
        MatrixX* J,
        VectorXi* coefficient_indices) const;

    Vector3 angularVelocityAndJacobian(
        real_t tk,
        MatrixX* J,
        VectorXi* coefficient_indices) const;

    //! takes the two transformation matrices at two points in time
    //! to construct a pose spline
    void initPoseSpline(
        real_t t0,
        real_t t1,
        const Matrix4& T_n_t0,
        const Matrix4& T_n_t);

    //! take the pose in the minimal parametrization to initializ the spline
    void initPoseSpline2(
        const VectorX& times,
        const Eigen::Matrix<real_t, 6, Eigen::Dynamic>& poses,
        int num_segments,
        real_t lambda);

    void initPoseSpline3(
        const VectorX& times,
        const Eigen::Matrix<real_t, 6, Eigen::Dynamic>& poses,
        int num_segments,
        real_t lambda);

    //! initialize a bspline given a vector of poses
    void initPoseSplinePoses(
        const VectorX& times,
        const std::vector<Matrix4>& poses,
        int num_segments,
        real_t lambda);

    void initPoseSplinePoses(
        const StampedTransformationVector& poses,
        int num_segments,
        real_t lambda);

    void addPoseSegment(
        real_t tk,
        const Matrix4& T_n_tk);

    void addPoseSegment2(
        real_t tk,
        const Matrix4& T_n_tk,
        real_t lambda);

    Matrix4 curveValueToTransformation(const VectorX& c) const;
    VectorX transformationToCurveValue(const Matrix4& T) const;

    Matrix4 curveValueToTransformationAndJacobian(
        const VectorX& c,
        MatrixX * J) const;
};

typedef BSplinePoseMinimal<ze::sm::RotationVector> BSplinePoseMinimalRotationVector;

}  // namespace ze
