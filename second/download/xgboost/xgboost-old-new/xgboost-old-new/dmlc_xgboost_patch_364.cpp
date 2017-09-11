@@ -41,13 +41,14 @@ class IGradBooster {
   virtual void InitModel(void) = 0;
   /*!
    * \brief peform update to the model(boosting)
-   * \param gpair the gradient pair statistics of the data
    * \param fmat feature matrix that provide access to features
    * \param info meta information about training
+   * \param in_gpair address of the gradient pair statistics of the data
+   * the booster may change content of gpair
    */
-  virtual void DoBoost(const std::vector<bst_gpair> &gpair,
-                       const FMatrix &fmat,
-                       const BoosterInfo &info) = 0;
+  virtual void DoBoost(const FMatrix &fmat,
+                       const BoosterInfo &info,
+                       std::vector<bst_gpair> *in_gpair) = 0;
   /*!
    * \brief generate predictions for given feature matrix
    * \param fmat feature matrix
@@ -74,12 +75,16 @@ class IGradBooster {
 };
 }  // namespace gbm
 }  // namespace xgboost
+
 #include "gbtree-inl.hpp"
+#include "gblinear-inl.hpp"
+
 namespace xgboost {
 namespace gbm {
 template<typename FMatrix>
 inline IGradBooster<FMatrix>* CreateGradBooster(const char *name) {
   if (!strcmp("gbtree", name)) return new GBTree<FMatrix>();
+  if (!strcmp("gblinear", name)) return new GBLinear<FMatrix>();
   utils::Error("unknown booster type: %s", name);
   return NULL;
 }