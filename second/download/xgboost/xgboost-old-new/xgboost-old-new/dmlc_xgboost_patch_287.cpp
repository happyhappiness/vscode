@@ -36,6 +36,7 @@ struct IEvaluator{
 namespace xgboost {
 namespace learner {
 inline IEvaluator* CreateEvaluator(const char *name) {
+  using namespace std;
   if (!strcmp(name, "rmse")) return new EvalRMSE();
   if (!strcmp(name, "error")) return new EvalError();
   if (!strcmp(name, "merror")) return new EvalMatchError();
@@ -56,6 +57,7 @@ inline IEvaluator* CreateEvaluator(const char *name) {
 class EvalSet{
  public:
   inline void AddEval(const char *name) {
+    using namespace std;
     for (size_t i = 0; i < evals_.size(); ++i) {
       if (!strcmp(name, evals_[i]->Name())) return;
     }