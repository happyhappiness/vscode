@@ -1,52 +1,106 @@
 /*!
- * Copyright by Contributors
- * \file gblinear-inl.hpp
+ * Copyright 2014 by Contributors
+ * \file gblinear.cc
  * \brief Implementation of Linear booster, with L1/L2 regularization: Elastic Net
  *        the update rule is parallel coordinate descent (shotgun)
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_GBM_GBLINEAR_INL_HPP_
-#define XGBOOST_GBM_GBLINEAR_INL_HPP_
-
+#include <dmlc/logging.h>
+#include <dmlc/omp.h>
+#include <dmlc/parameter.h>
+#include <xgboost/gbm.h>
 #include <vector>
 #include <string>
 #include <sstream>
+#include <cstring>
 #include <algorithm>
-#include "./gbm.h"
-#include "../tree/updater.h"
 
 namespace xgboost {
 namespace gbm {
+// model parameter
+struct GBLinearModelParam :public dmlc::Parameter<GBLinearModelParam> {
+  // number of feature dimension
+  unsigned num_feature;
+  // number of output group
+  int num_output_group;
+  // reserved field
+  int reserved[32];
+  // constructor
+  GBLinearModelParam() {
+    std::memset(this, 0, sizeof(GBLinearModelParam));
+  }
+  DMLC_DECLARE_PARAMETER(GBLinearModelParam) {
+    DMLC_DECLARE_FIELD(num_feature).set_lower_bound(0)
+        .describe("Number of features used in classification.");
+    DMLC_DECLARE_FIELD(num_output_group).set_lower_bound(1).set_default(1)
+        .describe("Number of output groups in the setting.");
+  }
+};
+
+// training parameter
+struct GBLinearTrainParam : public dmlc::Parameter<GBLinearTrainParam> {
+  /*! \brief learning_rate */
+  float learning_rate;
+  /*! \brief regularization weight for L2 norm */
+  float reg_lambda;
+  /*! \brief regularization weight for L1 norm */
+  float reg_alpha;
+  /*! \brief regularization weight for L2 norm in bias */
+  float reg_lambda_bias;
+  // declare parameters
+  DMLC_DECLARE_PARAMETER(GBLinearTrainParam) {
+    DMLC_DECLARE_FIELD(learning_rate).set_lower_bound(0.0f).set_default(1.0f)
+        .describe("Learning rate of each update.");
+    DMLC_DECLARE_FIELD(reg_lambda).set_lower_bound(0.0f).set_default(0.0f)
+        .describe("L2 regularization on weights.");
+    DMLC_DECLARE_FIELD(reg_alpha).set_lower_bound(0.0f).set_default(0.0f)
+        .describe("L1 regularization on weights.");
+    DMLC_DECLARE_FIELD(reg_lambda_bias).set_lower_bound(0.0f).set_default(0.0f)
+        .describe("L2 regularization on bias.");
+    // alias of parameters
+    DMLC_DECLARE_ALIAS(learning_rate, eta);
+    DMLC_DECLARE_ALIAS(reg_lambda, lambda);
+    DMLC_DECLARE_ALIAS(reg_alpha, alpha);
+    DMLC_DECLARE_ALIAS(reg_lambda_bias, lambda_bias);
+  }
+  // given original weight calculate delta
+  inline double CalcDelta(double sum_grad, double sum_hess, double w) const {
+    if (sum_hess < 1e-5f) return 0.0f;
+    double tmp = w - (sum_grad + reg_lambda * w) / (sum_hess + reg_lambda);
+    if (tmp >=0) {
+      return std::max(-(sum_grad + reg_lambda * w + reg_alpha) / (sum_hess + reg_lambda), -w);
+    } else {
+      return std::min(-(sum_grad + reg_lambda * w - reg_alpha) / (sum_hess + reg_lambda), -w);
+    }
+  }
+  // given original weight calculate delta bias
+  inline double CalcDeltaBias(double sum_grad, double sum_hess, double w) const {
+    return - (sum_grad + reg_lambda_bias * w) / (sum_hess + reg_lambda_bias);
+  }
+};
+
 /*!
  * \brief gradient boosted linear model
- * \tparam FMatrix the data type updater taking
  */
-class GBLinear : public IGradBooster {
+class GBLinear : public GradientBooster {
  public:
-  virtual ~GBLinear(void) {
-  }
-  // set model parameters
-  virtual void SetParam(const char *name, const char *val) {
-    using namespace std;
-    if (!strncmp(name, "bst:", 4)) {
-      param.SetParam(name + 4, val);
-    }
+  void Configure(const std::vector<std::pair<std::string, std::string> >& cfg) override {
     if (model.weight.size() == 0) {
-      model.param.SetParam(name, val);
+      model.param.InitAllowUnknown(cfg);
     }
+    param.InitAllowUnknown(cfg);
   }
-  virtual void LoadModel(utils::IStream &fi, bool with_pbuffer) { // NOLINT(*)
+  void LoadModel(dmlc::Stream* fi) override {
     model.LoadModel(fi);
   }
-  virtual void SaveModel(utils::IStream &fo, bool with_pbuffer) const { // NOLINT(*)
+  void SaveModel(dmlc::Stream* fo) const override {
     model.SaveModel(fo);
   }
-  virtual void InitModel(void) {
+  void InitModel() override {
     model.InitModel();
   }
-  virtual void DoBoost(IFMatrix *p_fmat,
+  virtual void DoBoost(DMatrix *p_fmat,
                        int64_t buffer_offset,
-                       const BoosterInfo &info,
                        std::vector<bst_gpair> *in_gpair) {
     std::vector<bst_gpair> &gpair = *in_gpair;
     const int ngroup = model.param.num_output_group;
@@ -75,7 +129,7 @@ class GBLinear : public IGradBooster {
         }
       }
     }
-    utils::IIterator<ColBatch> *iter = p_fmat->ColIterator();
+    dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator();
     while (iter->Next()) {
       // number of features
       const ColBatch &batch = iter->Value();
@@ -108,22 +162,20 @@ class GBLinear : public IGradBooster {
     }
   }
 
-  virtual void Predict(IFMatrix *p_fmat,
-                       int64_t buffer_offset,
-                       const BoosterInfo &info,
-                       std::vector<float> *out_preds,
-                       unsigned ntree_limit = 0) {
-    utils::Check(ntree_limit == 0,
-                 "GBLinear::Predict ntrees is only valid for gbtree predictor");
+  void Predict(DMatrix *p_fmat,
+               int64_t buffer_offset,
+               std::vector<float> *out_preds,
+               unsigned ntree_limit) override {
+    CHECK_EQ(ntree_limit, 0)
+        << "GBLinear::Predict ntrees is only valid for gbtree predictor";
     std::vector<float> &preds = *out_preds;
     preds.resize(0);
     // start collecting the prediction
-    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
+    dmlc::DataIter<RowBatch> *iter = p_fmat->RowIterator();
     const int ngroup = model.param.num_output_group;
     while (iter->Next()) {
       const RowBatch &batch = iter->Value();
-      utils::Assert(batch.base_rowid * ngroup == preds.size(),
-                    "base_rowid is not set correctly");
+      CHECK_EQ(batch.base_rowid * ngroup, preds.size());
       // output convention: nrow * k, where nrow is number of rows
       // k is number of group
       preds.resize(preds.size() + batch.size * ngroup);
@@ -139,22 +191,22 @@ class GBLinear : public IGradBooster {
       }
     }
   }
-  virtual void Predict(const SparseBatch::Inst &inst,
-                       std::vector<float> *out_preds,
-                       unsigned ntree_limit,
-                       unsigned root_index) {
+  void Predict(const SparseBatch::Inst &inst,
+               std::vector<float> *out_preds,
+               unsigned ntree_limit,
+               unsigned root_index) override {
     const int ngroup = model.param.num_output_group;
     for (int gid = 0; gid < ngroup; ++gid) {
-      this->Pred(inst, BeginPtr(*out_preds));
+      this->Pred(inst, dmlc::BeginPtr(*out_preds));
     }
   }
-  virtual void PredictLeaf(IFMatrix *p_fmat,
-                           const BoosterInfo &info,
-                           std::vector<float> *out_preds,
-                           unsigned ntree_limit = 0) {
-    utils::Error("gblinear does not support predict leaf index");
+  void PredictLeaf(DMatrix *p_fmat,
+                   std::vector<float> *out_preds,
+                   unsigned ntree_limit) override {
+    LOG(FATAL) << "gblinear does not support predict leaf index";
   }
-  virtual std::vector<std::string> DumpModel(const utils::FeatMap& fmap, int option) {
+
+  std::vector<std::string> Dump2Text(const FeatureMap& fmap, int option) override {
     std::stringstream fo("");
     fo << "bias:\n";
     for (int i = 0; i < model.param.num_output_group; ++i) {
@@ -182,76 +234,11 @@ class GBLinear : public IGradBooster {
       preds[gid] = psum;
     }
   }
-  // training parameter
-  struct ParamTrain {
-    /*! \brief learning_rate */
-    float learning_rate;
-    /*! \brief regularization weight for L2 norm */
-    float reg_lambda;
-    /*! \brief regularization weight for L1 norm */
-    float reg_alpha;
-    /*! \brief regularization weight for L2 norm in bias */
-    float reg_lambda_bias;
-    // parameter
-    ParamTrain(void) {
-      reg_alpha = 0.0f;
-      reg_lambda = 0.0f;
-      reg_lambda_bias = 0.0f;
-      learning_rate = 1.0f;
-    }
-    inline void SetParam(const char *name, const char *val) {
-      using namespace std;
-      // sync-names
-      if (!strcmp("eta", name)) learning_rate = static_cast<float>(atof(val));
-      if (!strcmp("lambda", name)) reg_lambda = static_cast<float>(atof(val));
-      if (!strcmp( "alpha", name)) reg_alpha = static_cast<float>(atof(val));
-      if (!strcmp( "lambda_bias", name)) reg_lambda_bias = static_cast<float>(atof(val));
-      // real names
-      if (!strcmp( "learning_rate", name)) learning_rate = static_cast<float>(atof(val));
-      if (!strcmp( "reg_lambda", name)) reg_lambda = static_cast<float>(atof(val));
-      if (!strcmp( "reg_alpha", name)) reg_alpha = static_cast<float>(atof(val));
-      if (!strcmp( "reg_lambda_bias", name)) reg_lambda_bias = static_cast<float>(atof(val));
-    }
-    // given original weight calculate delta
-    inline double CalcDelta(double sum_grad, double sum_hess, double w) {
-      if (sum_hess < 1e-5f) return 0.0f;
-      double tmp = w - (sum_grad + reg_lambda * w) / (sum_hess + reg_lambda);
-      if (tmp >=0) {
-        return std::max(-(sum_grad + reg_lambda * w + reg_alpha) / (sum_hess + reg_lambda), -w);
-      } else {
-        return std::min(-(sum_grad + reg_lambda * w - reg_alpha) / (sum_hess + reg_lambda), -w);
-      }
-    }
-    // given original weight calculate delta bias
-    inline double CalcDeltaBias(double sum_grad, double sum_hess, double w) {
-      return - (sum_grad + reg_lambda_bias * w) / (sum_hess + reg_lambda_bias);
-    }
-  };
   // model for linear booster
   class Model {
    public:
-    // model parameter
-    struct Param {
-      // number of feature dimension
-      unsigned num_feature;
-      // number of output group
-      int num_output_group;
-      // reserved field
-      int reserved[32];
-      // constructor
-      Param(void) {
-        num_feature = 0;
-        num_output_group = 1;
-        std::memset(reserved, 0, sizeof(reserved));
-      }
-      inline void SetParam(const char *name, const char *val) {
-        using namespace std;
-        if (!strcmp(name, "bst:num_feature")) num_feature = static_cast<unsigned>(atoi(val));
-        if (!strcmp(name, "num_output_group")) num_output_group = atoi(val);
-      }
-    };
     // parameter
-    Param param;
+    GBLinearModelParam param;
     // weight for each of feature, bias is the last one
     std::vector<float> weight;
     // initialize the model parameter
@@ -261,14 +248,14 @@ class GBLinear : public IGradBooster {
       std::fill(weight.begin(), weight.end(), 0.0f);
     }
     // save the model to file
-    inline void SaveModel(utils::IStream &fo) const { // NOLINT(*)
-      fo.Write(&param, sizeof(Param));
-      fo.Write(weight);
+    inline void SaveModel(dmlc::Stream* fo) const {
+      fo->Write(&param, sizeof(param));
+      fo->Write(weight);
     }
     // load model from file
-    inline void LoadModel(utils::IStream &fi) { // NOLINT(*)
-      utils::Assert(fi.Read(&param, sizeof(Param)) != 0, "Load LinearBooster");
-      fi.Read(&weight);
+    inline void LoadModel(dmlc::Stream* fi) {
+      CHECK_EQ(fi->Read(&param, sizeof(param)), sizeof(param));
+      fi->Read(&weight);
     }
     // model bias
     inline float* bias(void) {
@@ -282,11 +269,20 @@ class GBLinear : public IGradBooster {
   // model field
   Model model;
   // training parameter
-  ParamTrain param;
+  GBLinearTrainParam param;
   // Per feature: shuffle index of each feature index
   std::vector<bst_uint> feat_index;
 };
 
+// register the ojective functions
+DMLC_REGISTER_PARAMETER(GBLinearModelParam);
+DMLC_REGISTER_PARAMETER(GBLinearTrainParam);
+
+XGBOOST_REGISTER_GBM(GBLinear, "gblinear")
+.describe("Linear booster, implement generalized linear model.")
+.set_body([]() {
+    return new GBLinear();
+  });
 }  // namespace gbm
 }  // namespace xgboost
-#endif  // XGBOOST_GBM_GBLINEAR_INL_HPP_
+