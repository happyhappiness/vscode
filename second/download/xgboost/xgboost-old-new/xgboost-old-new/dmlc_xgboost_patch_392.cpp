@@ -113,14 +113,11 @@ namespace xgboost{
            if( !strcmp("reg:logistic", name ) )    return new RegressionObj( LossType::kLogisticNeglik );
            if( !strcmp("binary:logistic", name ) ) return new RegressionObj( LossType::kLogisticClassify );
            if( !strcmp("binary:logitraw", name ) ) return new RegressionObj( LossType::kLogisticRaw );
-           if( !strcmp("multi:softmax", name ) )      return new SoftmaxMultiClassObj();
+           if( !strcmp("multi:softmax", name ) )   return new SoftmaxMultiClassObj();
            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
-           if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
-           if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
-           if( !strcmp("rank:map", name ) ) return new LambdaRankObj_MAP();
-           if( !strcmp("rank:ndcg", name ) ) return new LambdaRankObj_NDCG();
-	   utils::Error("unknown objective function type");
+           if( !strcmp("rank:softmax", name ) )  return new SoftmaxRankObj();
+           utils::Error("unknown objective function type");
            return NULL;
        }
     };