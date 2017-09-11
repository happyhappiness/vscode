@@ -14,9 +14,7 @@ namespace xgboost {
 namespace tree {
 /*! 
  * \brief interface of tree update module, that performs update of a tree
- * \tparam FMatrix the data type updater taking
  */
-template<typename FMatrix>
 class IUpdater {
  public:
   /*!
@@ -28,44 +26,26 @@ class IUpdater {
   /*!
    * \brief peform update to the tree models
    * \param gpair the gradient pair statistics of the data
-   * \param fmat feature matrix that provide access to features
+   * \param p_fmat feature matrix that provide access to features
    * \param info extra side information that may be need, such as root index
    * \param trees pointer to the trese to be updated, upater will change the content of the tree
    *   note: all the trees in the vector are updated, with the same statistics, 
    *         but maybe different random seeds, usually one tree is passed in at a time, 
    *         there can be multiple trees when we train random forest style model
    */
   virtual void Update(const std::vector<bst_gpair> &gpair,
-                      const FMatrix &fmat,
+                      IFMatrix *p_fmat,
                       const BoosterInfo &info,
                       const std::vector<RegTree*> &trees) = 0;
   // destructor
   virtual ~IUpdater(void) {}
 };
-
-}  // namespace tree
-}  // namespace xgboost
-
-#include "./updater_prune-inl.hpp"
-#include "./updater_refresh-inl.hpp"
-#include "./updater_colmaker-inl.hpp"
-
-namespace xgboost {
-namespace tree {
 /*! 
  * \brief create a updater based on name 
  * \param name name of updater
  * \return return the updater instance
  */
-template<typename FMatrix>
-inline IUpdater<FMatrix>* CreateUpdater(const char *name) {
-  if (!strcmp(name, "prune")) return new TreePruner<FMatrix>();
-  if (!strcmp(name, "refresh")) return new TreeRefresher<FMatrix, GradStats>();
-  if (!strcmp(name, "grow_colmaker")) return new ColMaker<FMatrix, GradStats>();
-  utils::Error("unknown updater:%s", name);
-  return NULL;
-}
-
+IUpdater* CreateUpdater(const char *name);
 }  // namespace tree
 }  // namespace xgboost
 #endif  // XGBOOST_TREE_UPDATER_H_