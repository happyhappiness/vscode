@@ -109,15 +109,16 @@ namespace xgboost{
 namespace xgboost{
     namespace regrank{        
        inline IObjFunction* CreateObjFunction( const char *name ){
-            if( !strcmp("reg", name ) ) return new RegressionObj();
-            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
-            if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
-            if( !strcmp("softmax", name ) ) return new SoftmaxMultiClassObj();
-            //            if (!strcmp("lambdarank:map", name)) return new LambdaRankObj_MAP();
-            //            if (!strcmp("lambdarank:ndcg", name)) return new LambdaRankObj_NDCG();
-            utils::Error("unknown objective function type");
-            return NULL;
-        }
+           if( !strcmp("reg:linear", name ) )     return new RegressionObj( LossType::kLinearSquare );
+           if( !strcmp("reg:logistic", name ) )    return new RegressionObj( LossType::kLogisticNeglik );
+           if( !strcmp("binary:logistic", name ) ) return new RegressionObj( LossType::kLogisticClassify );
+           if( !strcmp("binary:logitraw", name ) ) return new RegressionObj( LossType::kLogisticRaw );
+           if( !strcmp("multi:softmax", name ) )      return new SoftmaxMultiClassObj();
+           if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
+           if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
+           utils::Error("unknown objective function type");
+           return NULL;
+       }
     };
 };
 #endif