@@ -50,6 +50,7 @@ namespace xgboost{
             const static int kLinearSquare = 0;
             const static int kLogisticNeglik = 1;
             const static int kLogisticClassify = 2;
+            const static int kLogisticRaw = 3;
         public:
             /*! \brief indicate which type we are using */
             int loss_type;
@@ -61,6 +62,7 @@ namespace xgboost{
              */
             inline float PredTransform(float x){
                 switch (loss_type){
+                case kLogisticRaw: 
                 case kLinearSquare: return x;
                 case kLogisticClassify:
                 case kLogisticNeglik: return 1.0f / (1.0f + expf(-x));
@@ -77,6 +79,7 @@ namespace xgboost{
             inline float FirstOrderGradient(float predt, float label) const{
                 switch (loss_type){
                 case kLinearSquare: return predt - label;
+                case kLogisticRaw: predt = 1.0f / (1.0f + expf(-predt));
                 case kLogisticClassify:
                 case kLogisticNeglik: return predt - label;
                 default: utils::Error("unknown loss_type"); return 0.0f;
@@ -91,6 +94,7 @@ namespace xgboost{
             inline float SecondOrderGradient(float predt, float label) const{
                 switch (loss_type){
                 case kLinearSquare: return 1.0f;
+                case kLogisticRaw: predt = 1.0f / (1.0f + expf(-predt));
                 case kLogisticClassify:
                 case kLogisticNeglik: return predt * (1 - predt);
                 default: utils::Error("unknown loss_type"); return 0.0f;