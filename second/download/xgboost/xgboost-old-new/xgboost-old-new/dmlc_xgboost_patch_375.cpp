@@ -73,6 +73,9 @@ inline IObjFunction* CreateObjFunction(const char *name) {
   if (!strcmp("binary:logitraw", name)) return new RegLossObj(LossType::kLogisticRaw);
   if (!strcmp("multi:softmax", name)) return new SoftmaxMultiClassObj(0);
   if (!strcmp("multi:softprob", name)) return new SoftmaxMultiClassObj(1);
+  if (!strcmp("rank:pairwise", name )) return new PairwiseRankObj();
+  if (!strcmp("rank:ndcg", name)) return new LambdaRankObjNDCG();
+  if (!strcmp("rank:map", name)) return new LambdaRankObjMAP();  
   utils::Error("unknown objective function type: %s", name);
   return NULL;
 }