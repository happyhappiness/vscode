@@ -45,6 +45,7 @@ inline IEvaluator* CreateEvaluator(const char *name) {
   if (!strcmp(name, "error")) return new EvalError();
   if (!strcmp(name, "merror")) return new EvalMatchError();
   if (!strcmp(name, "logloss")) return new EvalLogLoss();
+  if (!strcmp(name, "mlogloss")) return new EvalMultiLogLoss();
   if (!strcmp(name, "auc")) return new EvalAuc();
   if (!strncmp(name, "ams@", 4)) return new EvalAMS(name);
   if (!strncmp(name, "pre@", 4)) return new EvalPrecision(name);