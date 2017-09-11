@@ -321,9 +321,9 @@ class TreeModel {
    */
   inline void SaveModel(utils::IStream &fo) const { // NOLINT(*)
     utils::Assert(param.num_nodes == static_cast<int>(nodes.size()),
-                  "Tree::SaveModel");
+                  "TreeModel::SaveModel");
     utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
-                  "Tree::SaveModel");
+                  "TreeModel::SaveModel");
     fo.Write(&param, sizeof(Param));
     utils::Assert(param.num_nodes != 0, "invalid model");
     fo.Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
@@ -462,7 +462,7 @@ class TreeModel {
 
 /*! \brief node statistics used in regression tree */
 struct RTreeNodeStat {
-  /*! \brief loss chg caused by current split */
+  /*! \brief loss change caused by current split */
   float loss_chg;
   /*! \brief sum of hessian values, used to measure coverage of data */
   float sum_hess;
@@ -485,7 +485,7 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
  public:
   /*!
    * \brief dense feature vector that can be taken by RegTree
-   * to do tranverse efficiently
+   * to do traverse efficiently
    * and can be construct from sparse feature vector
    */
   struct FVec {
@@ -498,7 +498,7 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
       int flag;
     };
     std::vector<Entry> data;
-    /*! \brief intialize the vector with size vector */
+    /*! \brief initialize the vector with size vector */
     inline void Init(size_t size) {
       Entry e; e.flag = -1;
       data.resize(size);
@@ -529,14 +529,14 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
   };
   /*!
    * \brief get the leaf index
-   * \param feats dense feature vector, if the feature is missing the field is set to NaN
-   * \param root_gid starting root index of the instance
+   * \param feat dense feature vector, if the feature is missing the field is set to NaN
+   * \param root_id starting root index of the instance
    * \return the leaf index of the given feature
    */
-  inline int GetLeafIndex(const FVec&feat, unsigned root_id = 0) const {
+  inline int GetLeafIndex(const FVec &feat, unsigned root_id = 0) const {
     // start from groups that belongs to current data
     int pid = static_cast<int>(root_id);
-    // tranverse tree
+    // traverse tree
     while (!(*this)[ pid ].is_leaf()) {
       unsigned split_index = (*this)[pid].split_index();
       pid = this->GetNext(pid, feat.fvalue(split_index), feat.is_missing(split_index));
@@ -546,7 +546,7 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
   /*!
    * \brief get the prediction of regression tree, only accepts dense feature vector
    * \param feats dense feature vector, if the feature is missing the field is set to NaN
-   * \param root_gid starting root index of the instance
+   * \param root_id starting root index of the instance
    * \return the leaf index of the given feature
    */
   inline float Predict(const FVec &feat, unsigned root_id = 0) const {