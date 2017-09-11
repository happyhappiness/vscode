@@ -12,11 +12,55 @@
 #include <dmlc/parameter.h>
 #include <limits>
 #include <vector>
+#include <string>
 #include <cstring>
 #include <algorithm>
 #include "./base.h"
+#include "./data.h"
+#include "./feature_map.h"
 
 namespace xgboost {
+
+/*! \brief meta parameters of the tree */
+struct TreeParam : public dmlc::Parameter<TreeParam> {
+  /*! \brief number of start root */
+  int num_roots;
+  /*! \brief total number of nodes */
+  int num_nodes;
+  /*!\brief number of deleted nodes */
+  int num_deleted;
+  /*! \brief maximum depth, this is a statistics of the tree */
+  int max_depth;
+  /*! \brief number of features used for tree construction */
+  int num_feature;
+  /*!
+   * \brief leaf vector size, used for vector tree
+   * used to store more than one dimensional information in tree
+   */
+  int size_leaf_vector;
+  /*! \brief reserved part, make sure alignment works for 64bit */
+  int reserved[31];
+  /*! \brief constructor */
+  TreeParam() {
+    // assert compact alignment
+    static_assert(sizeof(TreeParam) == (31 + 6) * sizeof(int),
+                  "TreeParam: 64 bit align");
+    std::memset(this, 0, sizeof(TreeParam));
+    num_nodes = num_roots = 1;
+  }
+  // declare the parameters
+  DMLC_DECLARE_PARAMETER(TreeParam) {
+    // only declare the parameters that can be set by the user.
+    // other arguments are set by the algorithm.
+    DMLC_DECLARE_FIELD(num_roots).set_lower_bound(1).set_default(1)
+        .describe("Number of start root of trees.");
+    DMLC_DECLARE_FIELD(num_feature)
+        .describe("Number of features used in tree construction.");
+    DMLC_DECLARE_FIELD(size_leaf_vector).set_lower_bound(0).set_default(0)
+        .describe("Size of leaf vector, reserved for vector tree");
+  }
+};
+
 /*!
  * \brief template class of TreeModel
  * \tparam TSplitCond data type to indicate split condition
@@ -29,34 +73,6 @@ class TreeModel {
   typedef TNodeStat  NodeStat;
   /*! \brief auxiliary statistics of node to help tree building */
   typedef TSplitCond SplitCond;
-  /*! \brief parameters of the tree */
-  struct TreeParam {
-    /*! \brief number of start root */
-    int num_roots;
-    /*! \brief total number of nodes */
-    int num_nodes;
-    /*!\brief number of deleted nodes */
-    int num_deleted;
-    /*! \brief maximum depth, this is a statistics of the tree */
-    int max_depth;
-    /*! \brief  number of features used for tree construction */
-    int num_feature;
-    /*!
-     * \brief leaf vector size, used for vector tree
-     * used to store more than one dimensional information in tree
-     */
-    int size_leaf_vector;
-    /*! \brief reserved part */
-    int reserved[31];
-    /*! \brief constructor */
-    TreeParam() {
-      // assert compact alignment
-      static_assert(sizeof(TreeParam) == (31 + 6) * sizeof(int),
-                    "TreeParam: 64 bit align");
-      std::memset(this, 0, sizeof(TreeParam));
-      num_nodes = num_roots = 1;
-    }
-  };
   /*! \brief tree node */
   class Node {
    public:
@@ -259,6 +275,10 @@ class TreeModel {
   inline NodeStat& stat(int nid) {
     return stats[nid];
   }
+  /*! \brief get node statistics given nid */
+  inline const NodeStat& stat(int nid) const {
+    return stats[nid];
+  }
   /*! \brief get leaf vector given nid */
   inline bst_float* leafvec(int nid) {
     if (leaf_vector.size() == 0) return nullptr;
@@ -444,7 +464,7 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat> {
    * \param root_id starting root index of the instance
    * \return the leaf index of the given feature
    */
-    inline int GetLeafIndex(const FVec& feat, unsigned root_id = 0) const;
+  inline int GetLeafIndex(const FVec& feat, unsigned root_id = 0) const;
   /*!
    * \brief get the prediction of regression tree, only accepts dense feature vector
    * \param feats dense feature vector, if the feature is missing the field is set to NaN
@@ -459,6 +479,13 @@ class RegTree: public TreeModel<bst_float, RTreeNodeStat> {
    * \param is_unknown Whether current required feature is missing.
    */
   inline int GetNext(int pid, float fvalue, bool is_unknown) const;
+  /*!
+   * \brief dump model to text string
+   * \param fmap feature map of feature types
+   * \param with_stats whether dump out statistics as well
+   * \return the string of dumped model
+   */
+  std::string Dump2Text(const FeatureMap& fmap, bool with_stats) const;
 };
 
 // implementations of inline functions
@@ -518,6 +545,5 @@ inline int RegTree::GetNext(int pid, float fvalue, bool is_unknown) const {
     }
   }
 }
-
 }  // namespace xgboost
 #endif  // XGBOOST_TREE_MODEL_H_