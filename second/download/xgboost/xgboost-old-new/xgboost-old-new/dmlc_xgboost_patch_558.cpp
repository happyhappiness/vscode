@@ -172,6 +172,7 @@ namespace xgboost{
             enum LossType{
                 kLinearSquare = 0,
                 kLogisticNeglik = 1,
+                kLogisticClassify = 2
             };
 
             /*! \brief training parameter for regression */
@@ -211,6 +212,7 @@ namespace xgboost{
                 inline float PredTransform( float x ){
                     switch( loss_type ){                        
                     case kLinearSquare: return x;
+                    case kLogisticClassify:
                     case kLogisticNeglik: return 1.0f/(1.0f + expf(-x));
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
@@ -225,7 +227,8 @@ namespace xgboost{
                 inline float FirstOrderGradient( float predt, float label ) const{
                     switch( loss_type ){                        
                     case kLinearSquare: return predt - label;
-                    case 1: return predt - label;
+                    case kLogisticClassify:
+                    case kLogisticNeglik: return predt - label;
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
                 }
@@ -238,6 +241,7 @@ namespace xgboost{
                 inline float SecondOrderGradient( float predt, float label ) const{
                     switch( loss_type ){                        
                     case kLinearSquare: return 1.0f;
+                    case kLogisticClassify:
                     case kLogisticNeglik: return predt * ( 1 - predt );
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
@@ -253,6 +257,7 @@ namespace xgboost{
                     switch( loss_type ){
                     case kLinearSquare: return SquareLoss(preds,labels);
                     case kLogisticNeglik: return NegLoglikelihoodLoss(preds,labels);
+                    case kLogisticClassify: return ClassificationError(preds, labels);
                     default: utils::Error("unknown loss_type"); return 0.0f;
                     }
                 }
@@ -284,6 +289,24 @@ namespace xgboost{
                         ans -= labels[i] * logf(preds[i]) + ( 1 - labels[i] ) * logf(1 - preds[i]);
                     return ans;
                 }
+
+                /*!
+                * \brief calculating the ClassificationError  loss, given the predictions and labels
+                * \param preds the given predictions
+                * \param labels the given labels
+                * \return the summation of square loss
+                */
+                inline float ClassificationError(const std::vector<float> &preds, const std::vector<float> &labels) const{
+                    int nerr = 0;
+                    for(size_t i = 0; i < preds.size(); i++){
+                        if( preds[i] > 0.5f ){
+                            if( labels[i] < 0.5f ) nerr ++;
+                        }else{
+                            if( labels[i] > 0.5f ) nerr ++;
+                        }
+                    }
+                    return (float)nerr/preds.size();
+                }                
             };
         private:
             int silent;