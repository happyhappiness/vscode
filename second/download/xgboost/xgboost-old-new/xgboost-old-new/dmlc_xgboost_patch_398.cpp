@@ -109,6 +109,7 @@ namespace xgboost{
 namespace xgboost{
     namespace regrank{        
        inline IObjFunction* CreateObjFunction( const char *name ){
+<<<<<<< HEAD
             if( !strcmp("reg", name ) ) return new RegressionObj();
             if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
             if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
@@ -118,6 +119,18 @@ namespace xgboost{
             utils::Error("unknown objective function type");
             return NULL;
         }
+=======
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
+>>>>>>> 9eabb5c7f912a326005aca53a76c2e53a1661842
     };
 };
 #endif