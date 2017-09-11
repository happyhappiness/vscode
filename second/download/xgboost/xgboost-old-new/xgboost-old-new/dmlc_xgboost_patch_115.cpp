@@ -1,10 +1,12 @@
-#ifndef XGBOOST_TREE_MODEL_H_
-#define XGBOOST_TREE_MODEL_H_
 /*!
+ * Copyright 2014 by Contributors
  * \file model.h
  * \brief model structure for tree
  * \author Tianqi Chen
  */
+#ifndef XGBOOST_TREE_MODEL_H_
+#define XGBOOST_TREE_MODEL_H_
+
 #include <string>
 #include <cstring>
 #include <sstream>
@@ -19,7 +21,7 @@
 namespace xgboost {
 namespace tree {
 /*!
- * \brief template class of TreeModel 
+ * \brief template class of TreeModel
  * \tparam TSplitCond data type to indicate split condition
  * \tparam TNodeStat auxiliary statistics of node to help tree building
  */
@@ -42,7 +44,7 @@ class TreeModel {
     int max_depth;
     /*! \brief  number of features used for tree construction */
     int num_feature;
-    /*! 
+    /*!
      * \brief leaf vector size, used for vector tree
      * used to store more than one dimensional information in tree
      */
@@ -55,8 +57,8 @@ class TreeModel {
       size_leaf_vector = 0;
       std::memset(reserved, 0, sizeof(reserved));
     }
-    /*! 
-     * \brief set parameters from outside 
+    /*!
+     * \brief set parameters from outside
      * \param name name of the parameter
      * \param val  value of the parameter
      */
@@ -70,7 +72,7 @@ class TreeModel {
   /*! \brief tree node */
   class Node {
    public:
-	Node(void) : sindex_(0) {}
+    Node(void) : sindex_(0) {}
     /*! \brief index of left child */
     inline int cleft(void) const {
       return this->cleft_;
@@ -119,15 +121,15 @@ class TreeModel {
     inline bool is_root(void) const {
       return parent_ == -1;
     }
-    /*! 
-     * \brief set the right child 
+    /*!
+     * \brief set the right child
      * \param nide node id to right child
      */
     inline void set_right_child(int nid) {
       this->cright_ = nid;
     }
-    /*! 
-     * \brief set split condition of current node 
+    /*!
+     * \brief set split condition of current node
      * \param split_index feature index to split
      * \param split_cond  split condition
      * \param default_left the default direction when feature is unknown
@@ -138,10 +140,10 @@ class TreeModel {
       this->sindex_ = split_index;
       (this->info_).split_cond = split_cond;
     }
-    /*! 
+    /*!
      * \brief set the leaf value of the node
      * \param value leaf value
-     * \param right right index, could be used to store 
+     * \param right right index, could be used to store
      *        additional information
      */
     inline void set_leaf(float value, int right = -1) {
@@ -153,12 +155,12 @@ class TreeModel {
     inline void mark_delete(void) {
       this->sindex_ = std::numeric_limits<unsigned>::max();
     }
-    
+
    private:
     friend class TreeModel<TSplitCond, TNodeStat>;
-    /*! 
-     * \brief in leaf node, we have weights, in non-leaf nodes, 
-     *        we have split condition 
+    /*!
+     * \brief in leaf node, we have weights, in non-leaf nodes,
+     *        we have split condition
      */
     union Info{
       float leaf_value;
@@ -203,7 +205,7 @@ class TreeModel {
                  "number of nodes in the tree exceed 2^31");
     nodes.resize(param.num_nodes);
     stats.resize(param.num_nodes);
-    leaf_vector.resize(param.num_nodes * param.size_leaf_vector); 
+    leaf_vector.resize(param.num_nodes * param.size_leaf_vector);
     return nd;
   }
   // delete a tree node, keep the parent field to allow trace back
@@ -215,7 +217,7 @@ class TreeModel {
   }
 
  public:
-  /*! 
+  /*!
    * \brief change a non leaf node to a leaf node, delete its children
    * \param rid node id of the node
    * \param new leaf value
@@ -229,7 +231,7 @@ class TreeModel {
     this->DeleteNode(nodes[rid].cright());
     nodes[rid].set_leaf(value);
   }
-  /*! 
+  /*!
    * \brief collapse a non leaf node to a leaf node, delete its children
    * \param rid node id of the node
    * \param new leaf value
@@ -273,7 +275,7 @@ class TreeModel {
     return &leaf_vector[nid * param.size_leaf_vector];
   }
   /*! \brief get leaf vector given nid */
-  inline const bst_float* leafvec(int nid) const{
+  inline const bst_float* leafvec(int nid) const {
     if (leaf_vector.size() == 0) return NULL;
     return &leaf_vector[nid * param.size_leaf_vector];
   }
@@ -288,15 +290,15 @@ class TreeModel {
       nodes[i].set_parent(-1);
     }
   }
-  /*! 
+  /*!
    * \brief load model from stream
    * \param fi input stream
    */
-  inline void LoadModel(utils::IStream &fi) {
+  inline void LoadModel(utils::IStream &fi) { // NOLINT(*)
     utils::Check(fi.Read(&param, sizeof(Param)) > 0,
                  "TreeModel: wrong format");
     nodes.resize(param.num_nodes); stats.resize(param.num_nodes);
-    utils::Assert(param.num_nodes != 0, "invalid model"); 
+    utils::Assert(param.num_nodes != 0, "invalid model");
     utils::Check(fi.Read(BeginPtr(nodes), sizeof(Node) * nodes.size()) > 0,
                  "TreeModel: wrong format");
     utils::Check(fi.Read(BeginPtr(stats), sizeof(NodeStat) * stats.size()) > 0,
@@ -313,22 +315,22 @@ class TreeModel {
                   "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
                   param.num_deleted, deleted_nodes.size(), param.num_nodes);
   }
-  /*! 
+  /*!
    * \brief save model to stream
    * \param fo output stream
    */
-  inline void SaveModel(utils::IStream &fo) const {
+  inline void SaveModel(utils::IStream &fo) const { // NOLINT(*)
     utils::Assert(param.num_nodes == static_cast<int>(nodes.size()),
                   "Tree::SaveModel");
     utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
                   "Tree::SaveModel");
     fo.Write(&param, sizeof(Param));
-    utils::Assert(param.num_nodes != 0, "invalid model"); 
+    utils::Assert(param.num_nodes != 0, "invalid model");
     fo.Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
     fo.Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
     if (param.size_leaf_vector != 0) fo.Write(leaf_vector);
   }
-  /*! 
+  /*!
    * \brief add child nodes to node
    * \param nid node id to add childs
    */
@@ -340,8 +342,8 @@ class TreeModel {
     nodes[nodes[nid].cleft() ].set_parent(nid, true);
     nodes[nodes[nid].cright()].set_parent(nid, false);
   }
-  /*! 
-   * \brief only add a right child to a leaf node 
+  /*!
+   * \brief only add a right child to a leaf node
    * \param node id to add right child
    */
   inline void AddRightChild(int nid) {
@@ -385,7 +387,7 @@ class TreeModel {
   inline int num_extra_nodes(void) const {
     return param.num_nodes - param.num_roots - param.num_deleted;
   }
-  /*! 
+  /*!
    * \brief dump model to text string
    * \param fmap feature map of feature types
    * \param with_stats whether dump out statistics as well
@@ -400,7 +402,7 @@ class TreeModel {
   }
 
  private:
-  void Dump(int nid, std::stringstream &fo,
+  void Dump(int nid, std::stringstream &fo, // NOLINT(*)
             const utils::FeatMap& fmap, int depth, bool with_stats) {
     for (int i = 0;  i < depth; ++i) {
       fo << '\t';
@@ -469,7 +471,7 @@ struct RTreeNodeStat {
   /*! \brief number of child that is leaf node known up to now */
   int   leaf_child_cnt;
   /*! \brief print information of current stats to fo */
-  inline void Print(std::stringstream &fo, bool is_leaf) const {
+  inline void Print(std::stringstream &fo, bool is_leaf) const { // NOLINT(*)
     if (!is_leaf) {
       fo << ",gain=" << loss_chg << ",cover=" << sum_hess;
     } else {
@@ -481,13 +483,13 @@ struct RTreeNodeStat {
 /*! \brief define regression tree to be the most common tree model */
 class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
  public:
-  /*! 
+  /*!
    * \brief dense feature vector that can be taken by RegTree
    * to do tranverse efficiently
    * and can be construct from sparse feature vector
    */
   struct FVec {
-    /*! 
+    /*!
      * \brief a union value of value and flag
      * when flag == -1, this indicate the value is missing
      */
@@ -510,7 +512,7 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
       }
     }
     /*! \brief drop the trace after fill, must be called after fill */
-    inline void Drop(const RowBatch::Inst &inst) {      
+    inline void Drop(const RowBatch::Inst &inst) {
       for (bst_uint i = 0; i < inst.length; ++i) {
         if (inst[i].index >= data.size()) continue;
         data[inst[i].index].flag = -1;
@@ -526,10 +528,10 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
     }
   };
   /*!
-   * \brief get the leaf index 
+   * \brief get the leaf index
    * \param feats dense feature vector, if the feature is missing the field is set to NaN
    * \param root_gid starting root index of the instance
-   * \return the leaf index of the given feature 
+   * \return the leaf index of the given feature
    */
   inline int GetLeafIndex(const FVec&feat, unsigned root_id = 0) const {
     // start from groups that belongs to current data
@@ -545,7 +547,7 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
    * \brief get the prediction of regression tree, only accepts dense feature vector
    * \param feats dense feature vector, if the feature is missing the field is set to NaN
    * \param root_gid starting root index of the instance
-   * \return the leaf index of the given feature 
+   * \return the leaf index of the given feature
    */
   inline float Predict(const FVec &feat, unsigned root_id = 0) const {
     int pid = this->GetLeafIndex(feat, root_id);