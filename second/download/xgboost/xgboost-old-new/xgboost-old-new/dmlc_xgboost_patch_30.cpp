@@ -1,25 +1,22 @@
 /*!
  * Copyright 2014 by Contributors
- * \file model.h
+ * \file tree_model.h
  * \brief model structure for tree
  * \author Tianqi Chen
  */
 #ifndef XGBOOST_TREE_MODEL_H_
 #define XGBOOST_TREE_MODEL_H_
 
-#include <string>
-#include <cstring>
-#include <sstream>
+#include <dmlc/io.h>
+#include <dmlc/logging.h>
+#include <dmlc/parameter.h>
 #include <limits>
-#include <algorithm>
 #include <vector>
-#include <cmath>
-#include "../utils/io.h"
-#include "../utils/fmap.h"
-#include "../utils/utils.h"
+#include <cstring>
+#include <algorithm>
+#include "./base.h"
 
 namespace xgboost {
-namespace tree {
 /*!
  * \brief template class of TreeModel
  * \tparam TSplitCond data type to indicate split condition
@@ -33,7 +30,7 @@ class TreeModel {
   /*! \brief auxiliary statistics of node to help tree building */
   typedef TSplitCond SplitCond;
   /*! \brief parameters of the tree */
-  struct Param{
+  struct TreeParam {
     /*! \brief number of start root */
     int num_roots;
     /*! \brief total number of nodes */
@@ -52,73 +49,68 @@ class TreeModel {
     /*! \brief reserved part */
     int reserved[31];
     /*! \brief constructor */
-    Param(void) {
-      max_depth = 0;
-      size_leaf_vector = 0;
-      std::memset(reserved, 0, sizeof(reserved));
-    }
-    /*!
-     * \brief set parameters from outside
-     * \param name name of the parameter
-     * \param val  value of the parameter
-     */
-    inline void SetParam(const char *name, const char *val) {
-      using namespace std;
-      if (!strcmp("num_roots", name)) num_roots = atoi(val);
-      if (!strcmp("num_feature", name)) num_feature = atoi(val);
-      if (!strcmp("size_leaf_vector", name)) size_leaf_vector = atoi(val);
+    TreeParam() {
+      // assert compact alignment
+      static_assert(sizeof(TreeParam) == (31 + 6) * sizeof(int),
+                    "TreeParam: 64 bit align");
+      std::memset(this, 0, sizeof(TreeParam));
+      num_nodes = num_roots = 1;
     }
   };
   /*! \brief tree node */
   class Node {
    public:
-    Node(void) : sindex_(0) {}
+    Node() : sindex_(0) {
+      // assert compact alignment
+      static_assert(sizeof(Node) == 4 * sizeof(int) + sizeof(Info),
+                    "Node: 64 bit align");
+    }
     /*! \brief index of left child */
-    inline int cleft(void) const {
+    inline int cleft() const {
       return this->cleft_;
     }
     /*! \brief index of right child */
-    inline int cright(void) const {
+    inline int cright() const {
       return this->cright_;
     }
     /*! \brief index of default child when feature is missing */
-    inline int cdefault(void) const {
+    inline int cdefault() const {
       return this->default_left() ? this->cleft() : this->cright();
     }
     /*! \brief feature index of split condition */
-    inline unsigned split_index(void) const {
+    inline unsigned split_index() const {
       return sindex_ & ((1U << 31) - 1U);
     }
     /*! \brief when feature is unknown, whether goes to left child */
-    inline bool default_left(void) const {
+    inline bool default_left() const {
       return (sindex_ >> 31) != 0;
     }
     /*! \brief whether current node is leaf node */
-    inline bool is_leaf(void) const {
+    inline bool is_leaf() const {
       return cleft_ == -1;
     }
     /*! \brief get leaf value of leaf node */
-    inline float leaf_value(void) const {
+    inline float leaf_value() const {
       return (this->info_).leaf_value;
     }
     /*! \brief get split condition of the node */
-    inline TSplitCond split_cond(void) const {
+    inline TSplitCond split_cond() const {
       return (this->info_).split_cond;
     }
     /*! \brief get parent of the node */
-    inline int parent(void) const {
+    inline int parent() const {
       return parent_ & ((1U << 31) - 1);
     }
     /*! \brief whether current node is left child */
-    inline bool is_left_child(void) const {
+    inline bool is_left_child() const {
       return (parent_ & (1U << 31)) != 0;
     }
     /*! \brief whether this node is deleted */
-    inline bool is_deleted(void) const {
+    inline bool is_deleted() const {
       return sindex_ == std::numeric_limits<unsigned>::max();
     }
     /*! \brief whether current node is root */
-    inline bool is_root(void) const {
+    inline bool is_root() const {
       return parent_ == -1;
     }
     /*!
@@ -152,7 +144,7 @@ class TreeModel {
       this->cright_ = right;
     }
     /*! \brief mark that this node is deleted */
-    inline void mark_delete(void) {
+    inline void mark_delete() {
       this->sindex_ = std::numeric_limits<unsigned>::max();
     }
 
@@ -193,24 +185,24 @@ class TreeModel {
   std::vector<bst_float> leaf_vector;
   // allocate a new node,
   // !!!!!! NOTE: may cause BUG here, nodes.resize
-  inline int AllocNode(void) {
+  inline int AllocNode() {
     if (param.num_deleted != 0) {
       int nd = deleted_nodes.back();
       deleted_nodes.pop_back();
       --param.num_deleted;
       return nd;
     }
     int nd = param.num_nodes++;
-    utils::Check(param.num_nodes < std::numeric_limits<int>::max(),
-                 "number of nodes in the tree exceed 2^31");
+    CHECK_LT(param.num_nodes, std::numeric_limits<int>::max())
+        << "number of nodes in the tree exceed 2^31";
     nodes.resize(param.num_nodes);
     stats.resize(param.num_nodes);
     leaf_vector.resize(param.num_nodes * param.size_leaf_vector);
     return nd;
   }
   // delete a tree node, keep the parent field to allow trace back
   inline void DeleteNode(int nid) {
-    utils::Assert(nid >= param.num_roots, "can not delete root");
+    CHECK_GE(nid, param.num_roots);
     deleted_nodes.push_back(nid);
     nodes[nid].mark_delete();
     ++param.num_deleted;
@@ -223,10 +215,8 @@ class TreeModel {
    * \param new leaf value
    */
   inline void ChangeToLeaf(int rid, float value) {
-    utils::Assert(nodes[nodes[rid].cleft() ].is_leaf(),
-                  "can not delete a non termial child");
-    utils::Assert(nodes[nodes[rid].cright()].is_leaf(),
-                  "can not delete a non termial child");
+    CHECK(nodes[nodes[rid].cleft() ].is_leaf());
+    CHECK(nodes[nodes[rid].cright()].is_leaf());
     this->DeleteNode(nodes[rid].cleft());
     this->DeleteNode(nodes[rid].cright());
     nodes[rid].set_leaf(value);
@@ -249,38 +239,38 @@ class TreeModel {
 
  public:
   /*! \brief model parameter */
-  Param param;
+  TreeParam param;
   /*! \brief constructor */
-  TreeModel(void) {
+  TreeModel() {
     param.num_nodes = 1;
     param.num_roots = 1;
     param.num_deleted = 0;
     nodes.resize(1);
   }
   /*! \brief get node given nid */
-  inline Node &operator[](int nid) {
+  inline Node& operator[](int nid) {
     return nodes[nid];
   }
   /*! \brief get node given nid */
-  inline const Node &operator[](int nid) const {
+  inline const Node& operator[](int nid) const {
     return nodes[nid];
   }
   /*! \brief get node statistics given nid */
-  inline NodeStat &stat(int nid) {
+  inline NodeStat& stat(int nid) {
     return stats[nid];
   }
   /*! \brief get leaf vector given nid */
   inline bst_float* leafvec(int nid) {
-    if (leaf_vector.size() == 0) return NULL;
-    return &leaf_vector[nid * param.size_leaf_vector];
+    if (leaf_vector.size() == 0) return nullptr;
+    return& leaf_vector[nid * param.size_leaf_vector];
   }
   /*! \brief get leaf vector given nid */
   inline const bst_float* leafvec(int nid) const {
-    if (leaf_vector.size() == 0) return NULL;
-    return &leaf_vector[nid * param.size_leaf_vector];
+    if (leaf_vector.size() == 0) return nullptr;
+    return& leaf_vector[nid * param.size_leaf_vector];
   }
   /*! \brief initialize the model */
-  inline void InitModel(void) {
+  inline void InitModel() {
     param.num_nodes = param.num_roots;
     nodes.resize(param.num_nodes);
     stats.resize(param.num_nodes);
@@ -294,41 +284,37 @@ class TreeModel {
    * \brief load model from stream
    * \param fi input stream
    */
-  inline void LoadModel(utils::IStream &fi) { // NOLINT(*)
-    utils::Check(fi.Read(&param, sizeof(Param)) > 0,
-                 "TreeModel: wrong format");
-    nodes.resize(param.num_nodes); stats.resize(param.num_nodes);
-    utils::Assert(param.num_nodes != 0, "invalid model");
-    utils::Check(fi.Read(BeginPtr(nodes), sizeof(Node) * nodes.size()) > 0,
-                 "TreeModel: wrong format");
-    utils::Check(fi.Read(BeginPtr(stats), sizeof(NodeStat) * stats.size()) > 0,
-                 "TreeModel: wrong format");
+  inline void LoadModel(dmlc::Stream* fi) {
+    CHECK_EQ(fi->Read(&param, sizeof(TreeParam)), sizeof(TreeParam));
+    nodes.resize(param.num_nodes);
+    stats.resize(param.num_nodes);
+    CHECK_NE(param.num_nodes, 0);
+    CHECK_EQ(fi->Read(dmlc::BeginPtr(nodes), sizeof(Node) * nodes.size()),
+             sizeof(Node) * nodes.size());
+    CHECK_EQ(fi->Read(dmlc::BeginPtr(stats), sizeof(NodeStat) * stats.size()),
+             sizeof(NodeStat) * stats.size());
     if (param.size_leaf_vector != 0) {
-      utils::Check(fi.Read(&leaf_vector), "TreeModel: wrong format");
+      CHECK(fi->Read(&leaf_vector));
     }
     // chg deleted nodes
     deleted_nodes.resize(0);
     for (int i = param.num_roots; i < param.num_nodes; ++i) {
       if (nodes[i].is_deleted()) deleted_nodes.push_back(i);
     }
-    utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
-                  "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
-                  param.num_deleted, deleted_nodes.size(), param.num_nodes);
+    CHECK_EQ(static_cast<int>(deleted_nodes.size()), param.num_deleted);
   }
   /*!
    * \brief save model to stream
    * \param fo output stream
    */
-  inline void SaveModel(utils::IStream &fo) const { // NOLINT(*)
-    utils::Assert(param.num_nodes == static_cast<int>(nodes.size()),
-                  "TreeModel::SaveModel");
-    utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
-                  "TreeModel::SaveModel");
-    fo.Write(&param, sizeof(Param));
-    utils::Assert(param.num_nodes != 0, "invalid model");
-    fo.Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
-    fo.Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
-    if (param.size_leaf_vector != 0) fo.Write(leaf_vector);
+  inline void SaveModel(dmlc::Stream* fo) const {
+    CHECK_EQ(param.num_nodes, static_cast<int>(nodes.size()));
+    CHECK_EQ(param.num_nodes, static_cast<int>(stats.size()));
+    fo->Write(&param, sizeof(TreeParam));
+    CHECK_NE(param.num_nodes, 0);
+    fo->Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
+    fo->Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
+    if (param.size_leaf_vector != 0) fo->Write(leaf_vector);
   }
   /*!
    * \brief add child nodes to node
@@ -376,88 +362,17 @@ class TreeModel {
   /*!
    * \brief get maximum depth
    */
-  inline int MaxDepth(void) {
+  inline int MaxDepth() {
     int maxd = 0;
     for (int i = 0; i < param.num_roots; ++i) {
       maxd = std::max(maxd, MaxDepth(i));
     }
     return maxd;
   }
   /*! \brief number of extra nodes besides the root */
-  inline int num_extra_nodes(void) const {
+  inline int num_extra_nodes() const {
     return param.num_nodes - param.num_roots - param.num_deleted;
   }
-  /*!
-   * \brief dump model to text string
-   * \param fmap feature map of feature types
-   * \param with_stats whether dump out statistics as well
-   * \return the string of dumped model
-   */
-  inline std::string DumpModel(const utils::FeatMap& fmap, bool with_stats) {
-    std::stringstream fo("");
-    for (int i = 0; i < param.num_roots; ++i) {
-      this->Dump(i, fo, fmap, 0, with_stats);
-    }
-    return fo.str();
-  }
-
- private:
-  void Dump(int nid, std::stringstream &fo, // NOLINT(*)
-            const utils::FeatMap& fmap, int depth, bool with_stats) {
-    for (int i = 0;  i < depth; ++i) {
-      fo << '\t';
-    }
-    if (nodes[nid].is_leaf()) {
-      fo << nid << ":leaf=" << nodes[nid].leaf_value();
-      if (with_stats) {
-        stat(nid).Print(fo, true);
-      }
-      fo << '\n';
-    } else {
-      // right then left,
-      TSplitCond cond = nodes[nid].split_cond();
-      const unsigned split_index = nodes[nid].split_index();
-      if (split_index < fmap.size()) {
-        switch (fmap.type(split_index)) {
-          case utils::FeatMap::kIndicator: {
-            int nyes = nodes[nid].default_left() ?
-                nodes[nid].cright() : nodes[nid].cleft();
-            fo << nid << ":[" << fmap.name(split_index) << "] yes=" << nyes
-               << ",no=" << nodes[nid].cdefault();
-            break;
-          }
-          case utils::FeatMap::kInteger: {
-            fo << nid << ":[" << fmap.name(split_index) << "<"
-               << int(float(cond)+1.0f)
-               << "] yes=" << nodes[nid].cleft()
-               << ",no=" << nodes[nid].cright()
-               << ",missing=" << nodes[nid].cdefault();
-            break;
-          }
-          case utils::FeatMap::kFloat:
-          case utils::FeatMap::kQuantitive: {
-            fo << nid << ":[" << fmap.name(split_index) << "<"<< float(cond)
-               << "] yes=" << nodes[nid].cleft()
-               << ",no=" << nodes[nid].cright()
-               << ",missing=" << nodes[nid].cdefault();
-            break;
-          }
-          default: utils::Error("unknown fmap type");
-        }
-      } else {
-        fo << nid << ":[f" << split_index << "<"<< float(cond)
-           << "] yes=" << nodes[nid].cleft()
-           << ",no=" << nodes[nid].cright()
-           << ",missing=" << nodes[nid].cdefault();
-      }
-      if (with_stats) {
-        stat(nid).Print(fo, false);
-      }
-      fo << '\n';
-      this->Dump(nodes[nid].cleft(), fo, fmap, depth+1, with_stats);
-      this->Dump(nodes[nid].cright(), fo, fmap, depth+1, with_stats);
-    }
-  }
 };
 
 /*! \brief node statistics used in regression tree */
@@ -469,105 +384,140 @@ struct RTreeNodeStat {
   /*! \brief weight of current node */
   float base_weight;
   /*! \brief number of child that is leaf node known up to now */
-  int   leaf_child_cnt;
-  /*! \brief print information of current stats to fo */
-  inline void Print(std::stringstream &fo, bool is_leaf) const { // NOLINT(*)
-    if (!is_leaf) {
-      fo << ",gain=" << loss_chg << ",cover=" << sum_hess;
-    } else {
-      fo << ",cover=" << sum_hess;
-    }
-  }
+  int leaf_child_cnt;
 };
 
-/*! \brief define regression tree to be the most common tree model */
-class RegTree: public TreeModel<bst_float, RTreeNodeStat>{
+/*!
+ * \brief define regression tree to be the most common tree model.
+ *  This is the data structure used in xgboost's major tree models.
+ */
+class RegTree: public TreeModel<bst_float, RTreeNodeStat> {
  public:
   /*!
    * \brief dense feature vector that can be taken by RegTree
-   * to do traverse efficiently
-   * and can be construct from sparse feature vector
+   * and can be construct from sparse feature vector.
    */
   struct FVec {
+   public:
+    /*!
+     * \brief initialize the vector with size vector
+     * \param size The size of the feature vector.
+     */
+    inline void Init(size_t size);
+    /*!
+     * \brief fill the vector with sparse vector
+     * \param inst The sparse instance to fil.
+     */
+    inline void Fill(const RowBatch::Inst& inst);
+    /*!
+     * \brief drop the trace after fill, must be called after fill.
+     * \param inst The sparse instanc to drop.
+     */
+    inline void Drop(const RowBatch::Inst& inst);
+    /*!
+     * \brief get ith value
+     * \param i feature index.
+     * \return the i-th feature value
+     */
+    inline float fvalue(size_t i) const;
+    /*!
+     * \brief check whether i-th entry is missing
+     * \param i feature index.
+     * \return whether i-th value is missing.
+     */
+    inline bool is_missing(size_t i) const;
+
+   private:
     /*!
      * \brief a union value of value and flag
-     * when flag == -1, this indicate the value is missing
+     *  when flag == -1, this indicate the value is missing
      */
-    union Entry{
+    union Entry {
       float fvalue;
       int flag;
     };
     std::vector<Entry> data;
-    /*! \brief initialize the vector with size vector */
-    inline void Init(size_t size) {
-      Entry e; e.flag = -1;
-      data.resize(size);
-      std::fill(data.begin(), data.end(), e);
-    }
-    /*! \brief fill the vector with sparse vector */
-    inline void Fill(const RowBatch::Inst &inst) {
-      for (bst_uint i = 0; i < inst.length; ++i) {
-        if (inst[i].index >= data.size()) continue;
-        data[inst[i].index].fvalue = inst[i].fvalue;
-      }
-    }
-    /*! \brief drop the trace after fill, must be called after fill */
-    inline void Drop(const RowBatch::Inst &inst) {
-      for (bst_uint i = 0; i < inst.length; ++i) {
-        if (inst[i].index >= data.size()) continue;
-        data[inst[i].index].flag = -1;
-      }
-    }
-    /*! \brief get ith value */
-    inline float fvalue(size_t i) const {
-      return data[i].fvalue;
-    }
-    /*! \brief check whether i-th entry is missing */
-    inline bool is_missing(size_t i) const {
-      return data[i].flag == -1;
-    }
   };
   /*!
    * \brief get the leaf index
    * \param feat dense feature vector, if the feature is missing the field is set to NaN
    * \param root_id starting root index of the instance
    * \return the leaf index of the given feature
    */
-  inline int GetLeafIndex(const FVec &feat, unsigned root_id = 0) const {
-    // start from groups that belongs to current data
-    int pid = static_cast<int>(root_id);
-    // traverse tree
-    while (!(*this)[ pid ].is_leaf()) {
-      unsigned split_index = (*this)[pid].split_index();
-      pid = this->GetNext(pid, feat.fvalue(split_index), feat.is_missing(split_index));
-    }
-    return pid;
-  }
+    inline int GetLeafIndex(const FVec& feat, unsigned root_id = 0) const;
   /*!
    * \brief get the prediction of regression tree, only accepts dense feature vector
    * \param feats dense feature vector, if the feature is missing the field is set to NaN
    * \param root_id starting root index of the instance
    * \return the leaf index of the given feature
    */
-  inline float Predict(const FVec &feat, unsigned root_id = 0) const {
-    int pid = this->GetLeafIndex(feat, root_id);
-    return (*this)[pid].leaf_value();
+  inline float Predict(const FVec& feat, unsigned root_id = 0) const;
+  /*!
+   * \brief get next position of the tree given current pid
+   * \param pid Current node id.
+   * \param fvalue feature value if not missing.
+   * \param is_unknown Whether current required feature is missing.
+   */
+  inline int GetNext(int pid, float fvalue, bool is_unknown) const;
+};
+
+// implementations of inline functions
+// do not need to read if only use the model
+inline void RegTree::FVec::Init(size_t size) {
+  Entry e; e.flag = -1;
+  data.resize(size);
+  std::fill(data.begin(), data.end(), e);
+}
+
+inline void RegTree::FVec::Fill(const RowBatch::Inst& inst) {
+  for (bst_uint i = 0; i < inst.length; ++i) {
+    if (inst[i].index >= data.size()) continue;
+    data[inst[i].index].fvalue = inst[i].fvalue;
+  }
+}
+
+inline void RegTree::FVec::Drop(const RowBatch::Inst& inst) {
+  for (bst_uint i = 0; i < inst.length; ++i) {
+    if (inst[i].index >= data.size()) continue;
+    data[inst[i].index].flag = -1;
   }
-  /*! \brief get next position of the tree given current pid */
-  inline int GetNext(int pid, float fvalue, bool is_unknown) const {
-    float split_value = (*this)[pid].split_cond();
-    if (is_unknown) {
-      return (*this)[pid].cdefault();
+}
+
+inline float RegTree::FVec::fvalue(size_t i) const {
+  return data[i].fvalue;
+}
+
+inline bool RegTree::FVec::is_missing(size_t i) const {
+  return data[i].flag == -1;
+}
+
+inline int RegTree::GetLeafIndex(const RegTree::FVec& feat, unsigned root_id) const {
+  int pid = static_cast<int>(root_id);
+  while (!(*this)[pid].is_leaf()) {
+    unsigned split_index = (*this)[pid].split_index();
+    pid = this->GetNext(pid, feat.fvalue(split_index), feat.is_missing(split_index));
+  }
+  return pid;
+}
+
+inline float RegTree::Predict(const RegTree::FVec& feat, unsigned root_id) const {
+  int pid = this->GetLeafIndex(feat, root_id);
+  return (*this)[pid].leaf_value();
+}
+
+/*! \brief get next position of the tree given current pid */
+inline int RegTree::GetNext(int pid, float fvalue, bool is_unknown) const {
+  float split_value = (*this)[pid].split_cond();
+  if (is_unknown) {
+    return (*this)[pid].cdefault();
+  } else {
+    if (fvalue < split_value) {
+      return (*this)[pid].cleft();
     } else {
-      if (fvalue < split_value) {
-        return (*this)[pid].cleft();
-      } else {
-        return (*this)[pid].cright();
-      }
+      return (*this)[pid].cright();
     }
   }
-};
+}
 
-}  // namespace tree
 }  // namespace xgboost
 #endif  // XGBOOST_TREE_MODEL_H_