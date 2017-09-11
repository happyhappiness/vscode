@@ -36,6 +36,7 @@ struct IEvaluator{
 namespace xgboost {
 namespace learner {
 inline IEvaluator* CreateEvaluator(const char *name) {
+  using namespace std;
   if (!strcmp(name, "rmse")) return new EvalRMSE();
   if (!strcmp(name, "error")) return new EvalError();
   if (!strcmp(name, "merror")) return new EvalMatchError();
@@ -45,7 +46,9 @@ inline IEvaluator* CreateEvaluator(const char *name) {
   if (!strncmp(name, "pre@", 4)) return new EvalPrecision(name);
   if (!strncmp(name, "pratio@", 7)) return new EvalPrecisionRatio(name);
   if (!strncmp(name, "map", 3)) return new EvalMAP(name);
-  if (!strncmp(name, "ndcg", 3)) return new EvalNDCG(name);
+  if (!strncmp(name, "ndcg", 4)) return new EvalNDCG(name);
+  if (!strncmp(name, "ct-", 3)) return new EvalCTest(CreateEvaluator(name+3), name);
+
   utils::Error("unknown evaluation metric type: %s", name);
   return NULL;
 }
@@ -54,6 +57,7 @@ inline IEvaluator* CreateEvaluator(const char *name) {
 class EvalSet{
  public:
   inline void AddEval(const char *name) {
+    using namespace std;
     for (size_t i = 0; i < evals_.size(); ++i) {
       if (!strcmp(name, evals_[i]->Name())) return;
     }
@@ -71,11 +75,14 @@ class EvalSet{
     for (size_t i = 0; i < evals_.size(); ++i) {
       float res = evals_[i]->Eval(preds, info);
       char tmp[1024];
-      snprintf(tmp, sizeof(tmp), "\t%s-%s:%f", evname, evals_[i]->Name(), res);
+      utils::SPrintf(tmp, sizeof(tmp), "\t%s-%s:%f", evname, evals_[i]->Name(), res);
       result += tmp;
     }
     return result;
   }
+  inline size_t Size(void) const {
+    return evals_.size();
+  }
 
  private:
   std::vector<const IEvaluator*> evals_;