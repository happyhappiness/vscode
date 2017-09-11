#include <string>
#include <utility>
#include <cstring>
#include "xgboost_wrapper.h"
#include "xgboost_R.h"
#include "../src/utils/utils.h"
#include "../src/utils/omp.h"
#include "../src/utils/matrix_csr.h"

using namespace xgboost;

extern "C" {
  void _DMatrixFinalizer(SEXP ext) {    
