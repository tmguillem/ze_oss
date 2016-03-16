#include <ze/geometry/triangulation.h>

#include <algorithm>
#include <glog/logging.h>

#include <ze/common/matrix.h>

namespace ze {

std::pair<Vector4, bool> triangulateHomogeneousDLT(
    const TransformationVector& T_C_W,
    const Bearings& f_C,
    const FloatType rank_tol)
{
  // Number of observations.
  size_t m = T_C_W.size();
  CHECK_GE(m, 2u);

  // Compute unit-plane coorinates (divide by z) from bearing vectors.
  const Matrix2X uv = f_C.topRows<2>().array().rowwise() / f_C.bottomRows<1>().array();

  // Allocate DLT matrix.
  MatrixX4 A(m * 2, 4);
  A.setZero();

  // Fill DLT matrix.
  for (size_t i = 0; i < m; ++i)
  {
    //! @todo: Think if this can be optimized, e.g. without computing the Matrix44 and uv.
    size_t row = i * 2;
    Matrix44 projection = T_C_W[i].getTransformationMatrix();
    A.row(row)     = uv(0, i) * projection.row(2) - projection.row(0);
    A.row(row + 1) = uv(1, i) * projection.row(2) - projection.row(1);
  }
  int rank;
  FloatType error;
  VectorX v;
  std::tie(rank, error, v) = DLT(A, rank_tol);

  // Return homogeneous coordinates and success.
  Vector4 p_W_homogeneous = v;
  bool success = (rank < 3) ? false : true;
  return std::make_pair(p_W_homogeneous, success);
}

} // namespace ze
