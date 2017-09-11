@@ -7,16 +7,15 @@
  */
 #include <vector>
 #include "../data.h"
+#include "../utils/io.h"
 #include "../utils/fmap.h"
 
 namespace xgboost {
 /*! \brief namespace for gradient booster */
 namespace gbm {
 /*! 
  * \brief interface of gradient boosting model
- * \tparam FMatrix the data type updater taking
  */
-template<typename FMatrix>
 class IGradBooster {
  public:
   /*!
@@ -41,28 +40,31 @@ class IGradBooster {
   virtual void InitModel(void) = 0;
   /*!
    * \brief peform update to the model(boosting)
-   * \param fmat feature matrix that provide access to features
+   * \param p_fmat feature matrix that provide access to features
    * \param info meta information about training
    * \param in_gpair address of the gradient pair statistics of the data
    * the booster may change content of gpair
    */
-  virtual void DoBoost(const FMatrix &fmat,
+  virtual void DoBoost(IFMatrix *p_fmat,
                        const BoosterInfo &info,
                        std::vector<bst_gpair> *in_gpair) = 0;
   /*!
    * \brief generate predictions for given feature matrix
-   * \param fmat feature matrix
+   * \param p_fmat feature matrix
    * \param buffer_offset buffer index offset of these instances, if equals -1
    *        this means we do not have buffer index allocated to the gbm
    *  a buffer index is assigned to each instance that requires repeative prediction
    *  the size of buffer is set by convention using IGradBooster.SetParam("num_pbuffer","size")
    * \param info extra side information that may be needed for prediction
    * \param out_preds output vector to hold the predictions
+   * \param ntree_limit limit the number of trees used in prediction, when it equals 0, this means 
+   *    we do not limit number of trees, this parameter is only valid for gbtree, but not for gblinear
    */
-  virtual void Predict(const FMatrix &fmat,
+  virtual void Predict(IFMatrix *p_fmat,
                        int64_t buffer_offset,
                        const BoosterInfo &info,
-                       std::vector<float> *out_preds) = 0;
+                       std::vector<float> *out_preds,
+                       unsigned ntree_limit = 0) = 0;
   /*!
    * \brief dump the model in text format
    * \param fmap feature map that may help give interpretations of feature
@@ -73,21 +75,11 @@ class IGradBooster {
   // destrcutor
   virtual ~IGradBooster(void){}
 };
-}  // namespace gbm
-}  // namespace xgboost
-
-#include "gbtree-inl.hpp"
-#include "gblinear-inl.hpp"
-
-namespace xgboost {
-namespace gbm {
-template<typename FMatrix>
-inline IGradBooster<FMatrix>* CreateGradBooster(const char *name) {
-  if (!strcmp("gbtree", name)) return new GBTree<FMatrix>();
-  if (!strcmp("gblinear", name)) return new GBLinear<FMatrix>();
-  utils::Error("unknown booster type: %s", name);
-  return NULL;
-}
+/*!
+ * \breif create a gradient booster from given name
+ * \param name name of gradient booster
+ */
+IGradBooster* CreateGradBooster(const char *name);
 }  // namespace gbm
 }  // namespace xgboost
 #endif  // XGBOOST_GBM_GBM_H_