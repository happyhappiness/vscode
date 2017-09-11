    error(XGBGetLastError());                   \
  }

namespace xgboost {
namespace common {
bool CheckNAN(double v) {
  return ISNAN(v);
}
double LogGamma(double v) {
  return lgammafn(v);
}
}  // namespace common
}  // namespace xgboost

using namespace dmlc;

