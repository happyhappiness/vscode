@@ -113,8 +113,8 @@ namespace xgboost{
             if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
             if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
             if( !strcmp("softmax", name ) ) return new SoftmaxMultiClassObj();
-            //            if (!strcmp("lambdarank:map", name)) return new LambdaRankObj_MAP();
-            //            if (!strcmp("lambdarank:ndcg", name)) return new LambdaRankObj_NDCG();
+            if (!strcmp("rank:map", name)) return new LambdaRankObj_MAP();
+            if (!strcmp("rank:ndcg", name)) return new LambdaRankObj_NDCG();
             utils::Error("unknown objective function type");
             return NULL;
         }