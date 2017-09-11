@@ -116,7 +116,11 @@ namespace xgboost{
            if( !strcmp("multi:softmax", name ) )      return new SoftmaxMultiClassObj();
            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
            if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
-           utils::Error("unknown objective function type");
+           if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
+           if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
+           if( !strcmp("rank:map", name ) ) return new LambdaRankObj_MAP();
+           if( !strcmp("rank:ndcg", name ) ) return new LambdaRankObj_NDCG();
+	   utils::Error("unknown objective function type");
            return NULL;
        }
     };