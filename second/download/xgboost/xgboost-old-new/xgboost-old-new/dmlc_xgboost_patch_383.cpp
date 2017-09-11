@@ -57,7 +57,6 @@ class IObjFunction{
     return base_score;
   }
 };
-
 }  // namespace learner
 }  // namespace xgboost
 
@@ -68,10 +67,10 @@ namespace xgboost {
 namespace learner {
 /*! \brief factory funciton to create objective function by name */
 inline IObjFunction* CreateObjFunction(const char *name) {
-  if (!strcmp("reg:linear", name)) return new RegLossObj( LossType::kLinearSquare );
-  if (!strcmp("reg:logistic", name)) return new RegLossObj( LossType::kLogisticNeglik );
-  if (!strcmp("binary:logistic", name)) return new RegLossObj( LossType::kLogisticClassify );
-  if (!strcmp("binary:logitraw", name)) return new RegLossObj( LossType::kLogisticRaw );
+  if (!strcmp("reg:linear", name)) return new RegLossObj(LossType::kLinearSquare);
+  if (!strcmp("reg:logistic", name)) return new RegLossObj(LossType::kLogisticNeglik);
+  if (!strcmp("binary:logistic", name)) return new RegLossObj(LossType::kLogisticClassify);
+  if (!strcmp("binary:logitraw", name)) return new RegLossObj(LossType::kLogisticRaw);
   utils::Error("unknown objective function type: %s", name);
   return NULL;
 }