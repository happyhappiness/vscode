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
void HandlePrint(const char *msg) {
  Rprintf("%s", msg);
}
}  // namespace utils
namespace random {
void Seed(unsigned seed) {
  warning("parameter seed is ignored, please set random seed using set.seed");
