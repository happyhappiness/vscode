@@ -43,7 +43,6 @@ inline IEvaluator* CreateEvaluator(const char *name) {
   if (!strncmp(name, "ams@", 4)) return new EvalAMS(name);
   if (!strncmp(name, "pre@", 4)) return new EvalPrecision(name);
   if (!strncmp(name, "pratio@", 7)) return new EvalPrecisionRatio(name);
-  if (!strncmp(name, "apratio@", 8)) return new EvalPrecisionRatio(name);
   if (!strncmp(name, "map", 3)) return new EvalMAP(name);
   if (!strncmp(name, "ndcg", 3)) return new EvalNDCG(name);
   utils::Error("unknown evaluation metric type: %s", name);