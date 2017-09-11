@@ -41,6 +41,11 @@ namespace xgboost{
              * \param preds prediction values, saves to this vector as well
              */
             virtual void PredTransform(std::vector<float> &preds){}
+            /*! 
+             * \brief transform prediction values, this is only called when Eval is called, usually it redirect to PredTransform
+             * \param preds prediction values, saves to this vector as well
+             */
+            virtual void EvalTransform(std::vector<float> &preds){ this->PredTransform(preds); }
         };
     };
     
@@ -114,8 +119,8 @@ namespace xgboost{
            if( !strcmp("reg:logistic", name ) )    return new RegressionObj( LossType::kLogisticNeglik );
            if( !strcmp("binary:logistic", name ) ) return new RegressionObj( LossType::kLogisticClassify );
            if( !strcmp("binary:logitraw", name ) ) return new RegressionObj( LossType::kLogisticRaw );
-           if( !strcmp("multi:softmax", name ) )   return new SoftmaxMultiClassObj();
-           if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
+           if( !strcmp("multi:softmax", name ) )   return new SoftmaxMultiClassObj(0);
+           if( !strcmp("multi:softprob", name ) )   return new SoftmaxMultiClassObj(1);
            if( !strcmp("rank:pairwise", name ) ) return new PairwiseRankObj();
            if( !strcmp("rank:softmax", name ) )  return new SoftmaxRankObj();
            utils::Error("unknown objective function type");