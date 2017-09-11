@@ -33,7 +33,7 @@ struct EvalEWiseBase : public Metric {
     #pragma omp parallel for reduction(+: sum, wsum) schedule(static)
     for (omp_ulong i = 0; i < ndata; ++i) {
       const float wt = info.GetWeight(i);
-      sum += Derived::EvalRow(info.labels[i], preds[i]) * wt;
+      sum += static_cast<const Derived*>(this)->EvalRow(info.labels[i], preds[i]) * wt;
       wsum += wt;
     }
     double dat[2]; dat[0] = sum, dat[1] = wsum;
@@ -48,7 +48,7 @@ struct EvalEWiseBase : public Metric {
    * \param label label of current instance
    * \param pred prediction value of current instance
    */
-  inline static float EvalRow(float label, float pred);
+  inline float EvalRow(float label, float pred) const;
   /*!
    * \brief to be overridden by subclass, final transformation
    * \param esum the sum statistics returned by EvalRow
@@ -63,7 +63,7 @@ struct EvalRMSE : public EvalEWiseBase<EvalRMSE> {
   const char *Name() const override {
     return "rmse";
   }
-  inline static float EvalRow(float label, float pred) {
+  inline float EvalRow(float label, float pred) const {
     float diff = label - pred;
     return diff * diff;
   }
@@ -76,7 +76,7 @@ struct EvalMAE : public EvalEWiseBase<EvalMAE> {
   const char *Name() const override {
     return "mae";
   }
-  inline static float EvalRow(float label, float pred) {
+  inline float EvalRow(float label, float pred) const {
     return std::abs(label - pred);
   }
 };
@@ -85,7 +85,7 @@ struct EvalLogLoss : public EvalEWiseBase<EvalLogLoss> {
   const char *Name() const override {
     return "logloss";
   }
-  inline static float EvalRow(float y, float py) {
+  inline float EvalRow(float y, float py) const {
     const float eps = 1e-16f;
     const float pneg = 1.0f - py;
     if (py < eps) {
@@ -99,20 +99,36 @@ struct EvalLogLoss : public EvalEWiseBase<EvalLogLoss> {
 };
 
 struct EvalError : public EvalEWiseBase<EvalError> {
+  explicit EvalError(const char* param) {
+    if (param != nullptr) {
+      std::ostringstream os;
+      os << "error";
+      CHECK_EQ(sscanf(param, "%f", &threshold_), 1)
+        << "unable to parse the threshold value for the error metric";
+      if (threshold_ != 0.5f) os << '@' << threshold_;
+      name_ = os.str();
+    } else {
+      threshold_ = 0.5f;
+      name_ = "error";
+    }
+  }
   const char *Name() const override {
-    return "error";
+    return name_.c_str();
   }
-  inline static float EvalRow(float label, float pred) {
+  inline float EvalRow(float label, float pred) const {
     // assume label is in [0,1]
-    return pred > 0.5f ? 1.0f - label : label;
+    return pred > threshold_ ? 1.0f - label : label;
   }
+ protected:
+  float threshold_;
+  std::string name_;
 };
 
 struct EvalPoissionNegLogLik : public EvalEWiseBase<EvalPoissionNegLogLik> {
   const char *Name() const override {
     return "poisson-nloglik";
   }
-  inline static float EvalRow(float y, float py) {
+  inline float EvalRow(float y, float py) const {
     const float eps = 1e-16f;
     if (py < eps) py = eps;
     return common::LogGamma(y + 1.0f) + py - std::log(py) * y;
@@ -133,7 +149,7 @@ XGBOOST_REGISTER_METRIC(LogLoss, "logloss")
 
 XGBOOST_REGISTER_METRIC(Error, "error")
 .describe("Binary classification error.")
-.set_body([](const char* param) { return new EvalError(); });
+.set_body([](const char* param) { return new EvalError(param); });
 
 XGBOOST_REGISTER_METRIC(PossionNegLoglik, "poisson-nloglik")
 .describe("Negative loglikelihood for poisson regression.")