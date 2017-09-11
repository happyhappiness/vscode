@@ -44,7 +44,9 @@ inline IEvaluator* CreateEvaluator(const char *name) {
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