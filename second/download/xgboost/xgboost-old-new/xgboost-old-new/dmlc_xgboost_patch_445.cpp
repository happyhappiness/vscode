@@ -106,8 +106,9 @@ namespace xgboost{
     namespace regrank{        
         IObjFunction* CreateObjFunction( const char *name ){
             if( !strcmp("reg", name ) ) return new RegressionObj();
-            if( !strcmp("rank", name ) ) return new PairwiseRankObj();
-            if( !strcmp("softmax", name ) ) return new SoftmaxObj();
+            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
+            if( !strcmp("rank:softmax", name ) ) return new SoftmaxRankObj();
+            if( !strcmp("softmax", name ) ) return new SoftmaxMultiClassObj();
             utils::Error("unknown objective function type");
             return NULL;
         }