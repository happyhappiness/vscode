#include <string>
#include <utility>
#include <cstring>
#include "xgboost_R.h"
#include "wrapper/xgboost_wrapper.h"
#include "src/utils/utils.h"
#include "src/utils/omp.h"
#include "src/utils/matrix_csr.h"

using namespace xgboost;
// implements error handling
namespace xgboost {
namespace utils {
void HandleAssertError(const char *msg) {
  error("%s", msg);
}
void HandleCheckError(const char *msg) {
  error("%s", msg);
}
}  // namespace utils
}  // namespace xgboost

extern "C" {
  void _DMatrixFinalizer(SEXP ext) {    
    if (R_ExternalPtrAddr(ext) == NULL) return;
    XGDMatrixFree(R_ExternalPtrAddr(ext));
    R_ClearExternalPtr(ext);
  }
  SEXP XGDMatrixCreateFromFile_R(SEXP fname, SEXP silent) {
    void *handle = XGDMatrixCreateFromFile(CHAR(asChar(fname)), asInteger(silent));
    SEXP ret = PROTECT(R_MakeExternalPtr(handle, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(ret, _DMatrixFinalizer, TRUE);
    UNPROTECT(1);
    return ret;
  }
  SEXP XGDMatrixCreateFromMat_R(SEXP mat, 
                                SEXP missing) {
    SEXP dim = getAttrib(mat, R_DimSymbol);
    int nrow = INTEGER(dim)[0];
    int ncol = INTEGER(dim)[1];    
