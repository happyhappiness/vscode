namespace xgboost {
namespace learner {
inline IEvaluator* CreateEvaluator(const char *name) {
  using namespace std;
  if (!strcmp(name, "rmse")) return new EvalRMSE();
  if (!strcmp(name, "error")) return new EvalError();
  if (!strcmp(name, "merror")) return new EvalMatchError();
