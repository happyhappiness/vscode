#include <string>
#include <utility>
#include <cstring>
#include <cstdio>
#include "xgboost_R.h"
#include "wrapper/xgboost_wrapper.h"
#include "src/utils/utils.h"
#include "src/utils/omp.h"
#include "src/utils/matrix_csr.h"
using namespace std;
using namespace xgboost;

extern "C" {
  void XGBoostAssert_R(int exp, const char *fmt, ...);
  void XGBoostCheck_R(int exp, const char *fmt, ...);
  int XGBoostSPrintf_R(char *buf, size_t size, const char *fmt, ...);
}

// implements error handling
namespace xgboost {
namespace utils {
extern "C" {
  void (*Printf)(const char *fmt, ...) = Rprintf;
  int (*SPrintf)(char *buf, size_t size, const char *fmt, ...) = XGBoostSPrintf_R;
  void (*Assert)(int exp, const char *fmt, ...) = XGBoostAssert_R;
  void (*Check)(int exp, const char *fmt, ...) = XGBoostCheck_R;
  void (*Error)(const char *fmt, ...) = error;
}
}  // namespace utils

namespace random {
void Seed(unsigned seed) {
  warning("parameter seed is ignored, please set random seed using set.seed");
}
double Uniform(void) {
  return unif_rand();
}
double Normal(void) {
  return norm_rand();
}
}  // namespace random
}  // namespace xgboost

// call before wrapper starts
inline void _WrapperBegin(void) {
  GetRNGstate();
}
// call after wrapper starts
inline void _WrapperEnd(void) {
  PutRNGstate();
}

extern "C" {
  void _DMatrixFinalizer(SEXP ext) {    
    if (R_ExternalPtrAddr(ext) == NULL) return;
    XGDMatrixFree(R_ExternalPtrAddr(ext));
    R_ClearExternalPtr(ext);
  }
  SEXP XGDMatrixCreateFromFile_R(SEXP fname, SEXP silent) {
    _WrapperBegin();
    void *handle = XGDMatrixCreateFromFile(CHAR(asChar(fname)), asInteger(silent));
    SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
    UNPROTECT(1);
    _WrapperEnd();
    return ret;
  }
  SEXP XGDMatrixCreateFromMat_R(SEXP mat, 
                                SEXP missing) {
    _WrapperBegin();
    SEXP dim = getAttrib(mat, R_DimSymbol);
    int nrow = INTEGER(dim)[0];
    int ncol = INTEGER(dim)[1];    
