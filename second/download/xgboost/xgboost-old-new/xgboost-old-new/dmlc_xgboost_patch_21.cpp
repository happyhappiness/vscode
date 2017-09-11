@@ -1,149 +1,213 @@
 /*!
- * Copyright by Contributors
- * \file gbtree-inl.hpp
- * \brief gradient boosted tree implementation
+ * Copyright 2014 by Contributors
+ * \file gbtree.cc
+ * \brief gradient boosted tree implementation.
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_GBM_GBTREE_INL_HPP_
-#define XGBOOST_GBM_GBTREE_INL_HPP_
+#include <dmlc/logging.h>
+#include <dmlc/omp.h>
+#include <dmlc/parameter.h>
+#include <xgboost/gbm.h>
+#include <xgboost/tree_updater.h>
 
 #include <vector>
+#include <memory>
 #include <utility>
 #include <string>
 #include <limits>
-#include "./gbm.h"
-#include "../utils/omp.h"
-#include "../tree/updater.h"
 
 namespace xgboost {
 namespace gbm {
-/*!
- * \brief gradient boosted tree
- */
-class GBTree : public IGradBooster {
- public:
-  GBTree(void) {
+
+/*! \brief training parameters */
+struct GBTreeTrainParam : public dmlc::Parameter<GBTreeTrainParam> {
+  /*! \brief number of threads */
+  int nthread;
+  /*!
+   * \brief number of parallel trees constructed each iteration
+   *  use this option to support boosted random forest
+   */
+  int num_parallel_tree;
+  /*! \brief tree updater sequence */
+  std::string updater_seq;
+  // declare parameters
+  DMLC_DECLARE_PARAMETER(GBTreeTrainParam) {
+    DMLC_DECLARE_FIELD(nthread).set_lower_bound(0).set_default(0)
+        .describe("Number of threads used for training.");
+    DMLC_DECLARE_FIELD(num_parallel_tree).set_lower_bound(1).set_default(1)
+        .describe("Number of parallel trees constructed during each iteration."\
+                  " This option is used to support boosted random forest");
+    DMLC_DECLARE_FIELD(updater_seq).set_default("grow_colmaker,prune")
+        .describe("Tree updater sequence.");
   }
-  virtual ~GBTree(void) {
-    this->Clear();
+};
+
+/*! \brief model parameters */
+struct GBTreeModelParam : public dmlc::Parameter<GBTreeModelParam> {
+  /*! \brief number of trees */
+  int num_trees;
+  /*! \brief number of roots */
+  int num_roots;
+  /*! \brief number of features to be used by trees */
+  int num_feature;
+  /*! \brief pad this space, for backward compatiblity reason.*/
+  int pad_32bit;
+  /*! \brief size of prediction buffer allocated used for buffering */
+  int64_t num_pbuffer;
+  /*!
+   * \brief how many output group a single instance can produce
+   *  this affects the behavior of number of output we have:
+   *    suppose we have n instance and k group, output will be k * n
+   */
+  int num_output_group;
+  /*! \brief size of leaf vector needed in tree */
+  int size_leaf_vector;
+  /*! \brief reserved parameters */
+  int reserved[32];
+  /*! \brief constructor */
+  GBTreeModelParam() {
+    std::memset(this, 0, sizeof(GBTreeModelParam));
+    static_assert(sizeof(GBTreeModelParam) == (4 + 2 + 2 + 32) * sizeof(int),
+                  "64/32 bit compatibility issue");
   }
-  virtual void SetParam(const char *name, const char *val) {
-    using namespace std;
-    if (!strncmp(name, "bst:", 4)) {
-      cfg.push_back(std::make_pair(std::string(name+4), std::string(val)));
-      // set into updaters, if already initialized
-      for (size_t i = 0; i < updaters.size(); ++i) {
-        updaters[i]->SetParam(name+4, val);
-      }
-    }
-    if (!strcmp(name, "silent")) {
-      this->SetParam("bst:silent", val);
+  // declare parameters, only declare those that need to be set.
+  DMLC_DECLARE_PARAMETER(GBTreeModelParam) {
+    DMLC_DECLARE_FIELD(num_output_group).set_lower_bound(1).set_default(1)
+        .describe("Number of output groups to be predicted,"\
+                  " used for multi-class classification.");
+    DMLC_DECLARE_FIELD(num_roots).set_lower_bound(1).set_default(1)
+        .describe("Tree updater sequence.");
+    DMLC_DECLARE_FIELD(num_feature).set_lower_bound(0)
+        .describe("Number of features used for training and prediction.");
+    DMLC_DECLARE_FIELD(size_leaf_vector).set_lower_bound(0).set_default(0)
+        .describe("Reserved option for vector tree.");
+  }
+  /*! \return size of prediction buffer actually needed */
+  inline size_t PredBufferSize() const {
+    return num_output_group * num_pbuffer * (size_leaf_vector + 1);
+  }
+  /*!
+   * \brief get the buffer offset given a buffer index and group id
+   * \return calculated buffer offset
+   */
+  inline int64_t BufferOffset(int64_t buffer_index, int bst_group) const {
+    if (buffer_index < 0) return -1;
+    CHECK_LT(buffer_index, num_pbuffer);
+    return (buffer_index + num_pbuffer * bst_group) * (size_leaf_vector + 1);
+  }
+};
+
+// gradient boosted trees
+class GBTree : public GradientBooster {
+ public:
+  void Configure(const std::vector<std::pair<std::string, std::string> >& cfg) override {
+    this->cfg = cfg;
+    // initialize model parameters if not yet been initialized.
+    if (trees.size() == 0) {
+      mparam.InitAllowUnknown(cfg);
+    }
+    // initialize the updaters only when needed.
+    std::string updater_seq = tparam.updater_seq;
+    tparam.InitAllowUnknown(cfg);
+    if (updater_seq != tparam.updater_seq) updaters.clear();
+    for (const auto& up : updaters) {
+      up->Init(cfg);
     }
-    tparam.SetParam(name, val);
-    if (trees.size() == 0) mparam.SetParam(name, val);
   }
-  virtual void LoadModel(utils::IStream &fi, bool with_pbuffer) { // NOLINT(*)
-    this->Clear();
-    utils::Check(fi.Read(&mparam, sizeof(ModelParam)) != 0,
-                 "GBTree: invalid model file");
-    trees.resize(mparam.num_trees);
-    for (size_t i = 0; i < trees.size(); ++i) {
-      trees[i] = new tree::RegTree();
-      trees[i]->LoadModel(fi);
+  void LoadModel(dmlc::Stream* fi) override {
+    CHECK_EQ(fi->Read(&mparam, sizeof(mparam)), sizeof(mparam))
+        << "GBTree: invalid model file";
+    trees.clear();
+    for (int i = 0; i < mparam.num_trees; ++i) {
+      std::unique_ptr<RegTree> ptr(new RegTree());
+      ptr->LoadModel(fi);
+      trees.push_back(std::move(ptr));
     }
     tree_info.resize(mparam.num_trees);
     if (mparam.num_trees != 0) {
-      utils::Check(fi.Read(&tree_info[0], sizeof(int) * mparam.num_trees) != 0,
-                   "GBTree: invalid model file");
-    }
-    if (mparam.num_pbuffer != 0 && with_pbuffer) {
-      pred_buffer.resize(mparam.PredBufferSize());
-      pred_counter.resize(mparam.PredBufferSize());
-      utils::Check(fi.Read(&pred_buffer[0], pred_buffer.size() * sizeof(float)) != 0,
-                   "GBTree: invalid model file");
-      utils::Check(fi.Read(&pred_counter[0], pred_counter.size() * sizeof(unsigned)) != 0,
-                   "GBTree: invalid model file");
+      CHECK_EQ(fi->Read(dmlc::BeginPtr(tree_info), sizeof(int) * mparam.num_trees),
+               sizeof(int) * mparam.num_trees);
     }
+    this->ResetPredBuffer(0);
   }
-  virtual void SaveModel(utils::IStream &fo, bool with_pbuffer) const { // NOLINT(*)
-    utils::Assert(mparam.num_trees == static_cast<int>(trees.size()), "GBTree");
-    if (with_pbuffer) {
-      fo.Write(&mparam, sizeof(ModelParam));
-    } else {
-      ModelParam p = mparam;
-      p.num_pbuffer = 0;
-      fo.Write(&p, sizeof(ModelParam));
-    }
+  void SaveModel(dmlc::Stream* fo) const override {
+    CHECK_EQ(mparam.num_trees, static_cast<int>(trees.size()));
+    // not save predict buffer.
+    GBTreeModelParam p = mparam;
+    p.num_pbuffer = 0;
+    fo->Write(&p, sizeof(p));
     for (size_t i = 0; i < trees.size(); ++i) {
       trees[i]->SaveModel(fo);
     }
     if (tree_info.size() != 0) {
-      fo.Write(BeginPtr(tree_info), sizeof(int) * tree_info.size());
-    }
-    if (mparam.num_pbuffer != 0 && with_pbuffer) {
-      fo.Write(BeginPtr(pred_buffer), pred_buffer.size() * sizeof(float));
-      fo.Write(BeginPtr(pred_counter), pred_counter.size() * sizeof(unsigned));
+      fo->Write(dmlc::BeginPtr(tree_info), sizeof(int) * tree_info.size());
     }
   }
-  // initialize the predict buffer
-  virtual void InitModel(void) {
-    pred_buffer.clear(); pred_counter.clear();
+  void InitModel() override {
+    CHECK(mparam.num_trees == 0 && trees.size() == 0)
+        << "Model has already been initialized.";
+    pred_buffer.clear();
+    pred_counter.clear();
     pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
     pred_counter.resize(mparam.PredBufferSize(), 0);
-    utils::Assert(mparam.num_trees == 0, "GBTree: model already initialized");
-    utils::Assert(trees.size() == 0, "GBTree: model already initialized");
   }
-  virtual void ResetPredBuffer(size_t num_pbuffer) {
+  void ResetPredBuffer(size_t num_pbuffer) override {
     mparam.num_pbuffer = static_cast<int64_t>(num_pbuffer);
-    pred_buffer.clear(); pred_counter.clear();
+    pred_buffer.clear();
+    pred_counter.clear();
     pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
     pred_counter.resize(mparam.PredBufferSize(), 0);
   }
-  virtual bool AllowLazyCheckPoint(void) const {
-    return !(tparam.distcol_mode != 0  && mparam.num_output_group != 1);
+  bool AllowLazyCheckPoint() const override {
+    return mparam.num_output_group == 1 ||
+        tparam.updater_seq.find("distcol") != std::string::npos;
   }
-  virtual void DoBoost(IFMatrix *p_fmat,
-                       int64_t buffer_offset,
-                       const BoosterInfo &info,
-                       std::vector<bst_gpair> *in_gpair) {
-    const std::vector<bst_gpair> &gpair = *in_gpair;
-    std::vector<std::vector<tree::RegTree*> > new_trees;
+  void DoBoost(DMatrix* p_fmat,
+               int64_t buffer_offset,
+               std::vector<bst_gpair>* in_gpair) override {
+    const std::vector<bst_gpair>& gpair = *in_gpair;
+    std::vector<std::vector<std::unique_ptr<RegTree> > > new_trees;
     if (mparam.num_output_group == 1) {
-      new_trees.push_back(BoostNewTrees(gpair, p_fmat, buffer_offset, info, 0));
+      std::vector<std::unique_ptr<RegTree> > ret;
+      BoostNewTrees(gpair, p_fmat, buffer_offset, 0, &ret);
+      new_trees.push_back(std::move(ret));
     } else {
       const int ngroup = mparam.num_output_group;
-      utils::Check(gpair.size() % ngroup == 0,
-                   "must have exactly ngroup*nrow gpairs");
-      std::vector<bst_gpair> tmp(gpair.size()/ngroup);
+      CHECK_EQ(gpair.size() % ngroup, 0)
+          << "must have exactly ngroup*nrow gpairs";
+      std::vector<bst_gpair> tmp(gpair.size() / ngroup);
       for (int gid = 0; gid < ngroup; ++gid) {
         bst_omp_uint nsize = static_cast<bst_omp_uint>(tmp.size());
         #pragma omp parallel for schedule(static)
         for (bst_omp_uint i = 0; i < nsize; ++i) {
           tmp[i] = gpair[i * ngroup + gid];
         }
-        new_trees.push_back(BoostNewTrees(tmp, p_fmat, buffer_offset, info, gid));
+        std::vector<std::unique_ptr<RegTree> > ret;
+        BoostNewTrees(tmp, p_fmat, buffer_offset, gid, &ret);
+        new_trees.push_back(std::move(ret));
       }
     }
     for (int gid = 0; gid < mparam.num_output_group; ++gid) {
-      this->CommitModel(new_trees[gid], gid);
+      this->CommitModel(std::move(new_trees[gid]), gid);
     }
   }
-  virtual void Predict(IFMatrix *p_fmat,
-                       int64_t buffer_offset,
-                       const BoosterInfo &info,
-                       std::vector<float> *out_preds,
-                       unsigned ntree_limit = 0) {
+  void Predict(DMatrix* p_fmat,
+               int64_t buffer_offset,
+               std::vector<float>* out_preds,
+               unsigned ntree_limit) override {
+    const MetaInfo& info = p_fmat->info();
     int nthread;
     #pragma omp parallel
     {
       nthread = omp_get_num_threads();
     }
     InitThreadTemp(nthread);
     std::vector<float> &preds = *out_preds;
-    const size_t stride = info.num_row * mparam.num_output_group;
+    const size_t stride = p_fmat->info().num_row * mparam.num_output_group;
     preds.resize(stride * (mparam.size_leaf_vector+1));
     // start collecting the prediction
-    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
+    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();
+
     iter->BeforeFirst();
     while (iter->Next()) {
       const RowBatch &batch = iter->Value();
@@ -152,9 +216,9 @@ class GBTree : public IGradBooster {
       #pragma omp parallel for schedule(static)
       for (bst_omp_uint i = 0; i < nsize; ++i) {
         const int tid = omp_get_thread_num();
-        tree::RegTree::FVec &feats = thread_temp[tid];
+        RegTree::FVec &feats = thread_temp[tid];
         int64_t ridx = static_cast<int64_t>(batch.base_rowid + i);
-        utils::Assert(static_cast<size_t>(ridx) < info.num_row, "data row index exceed bound");
+        CHECK_LT(static_cast<size_t>(ridx), info.num_row);
         // loop over output groups
         for (int gid = 0; gid < mparam.num_output_group; ++gid) {
           this->Pred(batch[i],
@@ -166,12 +230,12 @@ class GBTree : public IGradBooster {
       }
     }
   }
-  virtual void Predict(const SparseBatch::Inst &inst,
-                       std::vector<float> *out_preds,
-                       unsigned ntree_limit,
-                       unsigned root_index) {
+  void Predict(const SparseBatch::Inst& inst,
+               std::vector<float>* out_preds,
+               unsigned ntree_limit,
+               unsigned root_index) override {
     if (thread_temp.size() == 0) {
-      thread_temp.resize(1, tree::RegTree::FVec());
+      thread_temp.resize(1, RegTree::FVec());
       thread_temp[0].Init(mparam.num_feature);
     }
     out_preds->resize(mparam.num_output_group * (mparam.size_leaf_vector+1));
@@ -182,120 +246,99 @@ class GBTree : public IGradBooster {
                  ntree_limit);
     }
   }
-  virtual void PredictLeaf(IFMatrix *p_fmat,
-                           const BoosterInfo &info,
-                           std::vector<float> *out_preds,
-                           unsigned ntree_limit) {
+  void PredictLeaf(DMatrix* p_fmat,
+                   std::vector<float>* out_preds,
+                   unsigned ntree_limit) {
     int nthread;
     #pragma omp parallel
     {
       nthread = omp_get_num_threads();
     }
     InitThreadTemp(nthread);
-    this->PredPath(p_fmat, info, out_preds, ntree_limit);
+    this->PredPath(p_fmat, out_preds, ntree_limit);
   }
-  virtual std::vector<std::string> DumpModel(const utils::FeatMap& fmap, int option) {
+  std::vector<std::string> Dump2Text(const FeatureMap& fmap, int option) {
     std::vector<std::string> dump;
     for (size_t i = 0; i < trees.size(); i++) {
-      dump.push_back(trees[i]->DumpModel(fmap, option&1));
+      dump.push_back(trees[i]->Dump2Text(fmap, option & 1));
     }
     return dump;
   }
 
  protected:
-  // clear the model
-  inline void Clear(void) {
-    for (size_t i = 0; i < trees.size(); ++i) {
-      delete trees[i];
-    }
-    for (size_t i = 0; i < updaters.size(); ++i) {
-      delete updaters[i];
-    }
-    updaters.clear();
-    trees.clear();
-    pred_buffer.clear();
-    pred_counter.clear();
-  }
   // initialize updater before using them
-  inline void InitUpdater(void) {
-    if (tparam.updater_initialized != 0) return;
-    for (size_t i = 0; i < updaters.size(); ++i) {
-      delete updaters[i];
-    }
-    updaters.clear();
+  inline void InitUpdater() {
+    if (updaters.size() != 0) return;
     std::string tval = tparam.updater_seq;
     char *pstr;
     pstr = std::strtok(&tval[0], ",");
-    while (pstr != NULL) {
-      updaters.push_back(tree::CreateUpdater(pstr));
-      for (size_t j = 0; j < cfg.size(); ++j) {
-        // set parameters
-        updaters.back()->SetParam(cfg[j].first.c_str(), cfg[j].second.c_str());
-      }
-      pstr = std::strtok(NULL, ",");
+    while (pstr != nullptr) {
+      std::unique_ptr<TreeUpdater> up(TreeUpdater::Create(pstr));
+      up->Init(this->cfg);
+      updaters.push_back(std::move(up));
+      pstr = std::strtok(nullptr, ",");
     }
-    tparam.updater_initialized = 1;
   }
   // do group specific group
-  inline std::vector<tree::RegTree*>
+  inline void
   BoostNewTrees(const std::vector<bst_gpair> &gpair,
-                IFMatrix *p_fmat,
+                DMatrix *p_fmat,
                 int64_t buffer_offset,
-                const BoosterInfo &info,
-                int bst_group) {
-    std::vector<tree::RegTree *> new_trees;
+                int bst_group,
+                std::vector<std::unique_ptr<RegTree> >* ret) {
     this->InitUpdater();
+    std::vector<RegTree*> new_trees;
+    ret->clear();
     // create the trees
     for (int i = 0; i < tparam.num_parallel_tree; ++i) {
-      new_trees.push_back(new tree::RegTree());
-      for (size_t j = 0; j < cfg.size(); ++j) {
-        new_trees.back()->param.SetParam(cfg[j].first.c_str(), cfg[j].second.c_str());
-      }
-      new_trees.back()->InitModel();
+      std::unique_ptr<RegTree> ptr(new RegTree());
+      ptr->param.InitAllowUnknown(this->cfg);
+      ptr->InitModel();
+      new_trees.push_back(ptr.get());
+      ret->push_back(std::move(ptr));
     }
     // update the trees
-    for (size_t i = 0; i < updaters.size(); ++i) {
-      updaters[i]->Update(gpair, p_fmat, info, new_trees);
+    for (auto& up : updaters) {
+      up->Update(gpair, p_fmat, new_trees);
     }
     // optimization, update buffer, if possible
     // this is only under distributed column mode
     // for safety check of lazy checkpoint
-    if (
-        buffer_offset >= 0 &&
+    if (buffer_offset >= 0 &&
         new_trees.size() == 1 && updaters.size() > 0 &&
-        updaters.back()->GetLeafPosition() != NULL) {
-      utils::Check(info.num_row == p_fmat->buffered_rowset().size(),
-                   "distributed mode is not compatible with prob_buffer_row");
+        updaters.back()->GetLeafPosition() != nullptr) {
+      CHECK_EQ(p_fmat->info().num_row, p_fmat->buffered_rowset().size());
       this->UpdateBufferByPosition(p_fmat,
-                                   buffer_offset, bst_group,
+                                   buffer_offset,
+                                   bst_group,
                                    *new_trees[0],
                                    updaters.back()->GetLeafPosition());
     }
-    return new_trees;
   }
   // commit new trees all at once
-  inline void CommitModel(const std::vector<tree::RegTree*> &new_trees, int bst_group) {
+  inline void CommitModel(std::vector<std::unique_ptr<RegTree> >&& new_trees,
+                          int bst_group) {
     for (size_t i = 0; i < new_trees.size(); ++i) {
-      trees.push_back(new_trees[i]);
+      trees.push_back(std::move(new_trees[i]));
       tree_info.push_back(bst_group);
     }
     mparam.num_trees += static_cast<int>(new_trees.size());
   }
   // update buffer by pre-cached position
-  inline void UpdateBufferByPosition(IFMatrix *p_fmat,
+  inline void UpdateBufferByPosition(DMatrix *p_fmat,
                                      int64_t buffer_offset,
                                      int bst_group,
-                                     const tree::RegTree &new_tree,
+                                     const RegTree &new_tree,
                                      const int* leaf_position) {
-    const std::vector<bst_uint> &rowset = p_fmat->buffered_rowset();
+    const std::vector<bst_uint>& rowset = p_fmat->buffered_rowset();
     const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
     #pragma omp parallel for schedule(static)
     for (bst_omp_uint i = 0; i < ndata; ++i) {
       const bst_uint ridx = rowset[i];
       const int64_t bid = mparam.BufferOffset(buffer_offset + ridx, bst_group);
       const int tid = leaf_position[ridx];
-      utils::Assert(pred_counter[bid] == trees.size(), "cached buffer not up to date");
-      utils::Assert(tid >= 0, "invalid leaf position");
+      CHECK_EQ(pred_counter[bid], trees.size());
+      CHECK_GE(tid, 0);
       pred_buffer[bid] += new_tree[tid].leaf_value();
       for (int i = 0; i < mparam.size_leaf_vector; ++i) {
         pred_buffer[bid + i + 1] += new_tree.leafvec(tid)[i];
@@ -308,8 +351,9 @@ class GBTree : public IGradBooster {
                    int64_t buffer_index,
                    int bst_group,
                    unsigned root_index,
-                   tree::RegTree::FVec *p_feats,
-                   float *out_pred, size_t stride,
+                   RegTree::FVec *p_feats,
+                   float *out_pred,
+                   size_t stride,
                    unsigned ntree_limit) {
     size_t itop = 0;
     float  psum = 0.0f;
@@ -354,28 +398,28 @@ class GBTree : public IGradBooster {
     }
   }
   // predict independent leaf index
-  inline void PredPath(IFMatrix *p_fmat,
-                       const BoosterInfo &info,
+  inline void PredPath(DMatrix *p_fmat,
                        std::vector<float> *out_preds,
                        unsigned ntree_limit) {
+    const MetaInfo& info = p_fmat->info();
     // number of valid trees
     if (ntree_limit == 0 || ntree_limit > trees.size()) {
       ntree_limit = static_cast<unsigned>(trees.size());
     }
-    std::vector<float> &preds = *out_preds;
+    std::vector<float>& preds = *out_preds;
     preds.resize(info.num_row * ntree_limit);
     // start collecting the prediction
-    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
+    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();
     iter->BeforeFirst();
     while (iter->Next()) {
-      const RowBatch &batch = iter->Value();
+      const RowBatch& batch = iter->Value();
       // parallel over local batch
       const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
       #pragma omp parallel for schedule(static)
       for (bst_omp_uint i = 0; i < nsize; ++i) {
         const int tid = omp_get_thread_num();
         size_t ridx = static_cast<size_t>(batch.base_rowid + i);
-        tree::RegTree::FVec &feats = thread_temp[tid];
+        RegTree::FVec &feats = thread_temp[tid];
         feats.Fill(batch[i]);
         for (unsigned j = 0; j < ntree_limit; ++j) {
           int tid = trees[j]->GetLeafIndex(feats, info.GetRoot(ridx));
@@ -389,117 +433,20 @@ class GBTree : public IGradBooster {
   inline void InitThreadTemp(int nthread) {
     int prev_thread_temp_size = thread_temp.size();
     if (prev_thread_temp_size < nthread) {
-      thread_temp.resize(nthread, tree::RegTree::FVec());
+      thread_temp.resize(nthread, RegTree::FVec());
       for (int i = prev_thread_temp_size; i < nthread; ++i) {
         thread_temp[i].Init(mparam.num_feature);
       }
     }
   }
 
   // --- data structure ---
-  /*! \brief training parameters */
-  struct TrainParam {
-    /*! \brief number of threads */
-    int nthread;
-    /*!
-     * \brief number of parallel trees constructed each iteration
-     *  use this option to support boosted random forest
-     */
-    int num_parallel_tree;
-    /*! \brief whether updater is already initialized */
-    int updater_initialized;
-    /*! \brief distributed column mode */
-    int distcol_mode;
-    /*! \brief tree updater sequence */
-    std::string updater_seq;
-    // construction
-    TrainParam(void) {
-      nthread = 0;
-      updater_seq = "grow_colmaker,prune";
-      num_parallel_tree = 1;
-      updater_initialized = 0;
-      distcol_mode = 0;
-    }
-    inline void SetParam(const char *name, const char *val){
-      using namespace std;
-      if (!strcmp(name, "updater") &&
-          strcmp(updater_seq.c_str(), val) != 0) {
-        updater_seq = val;
-        updater_initialized = 0;
-      }
-      if (!strcmp(name, "dsplit") && !strcmp(val, "col")) {
-        distcol_mode = 1;
-      }
-      if (!strcmp(name, "nthread")) {
-        omp_set_num_threads(nthread = atoi(val));
-      }
-      if (!strcmp(name, "num_parallel_tree")) {
-        num_parallel_tree = atoi(val);
-      }
-    }
-  };
-  /*! \brief model parameters */
-  struct ModelParam {
-    /*! \brief number of trees */
-    int num_trees;
-    /*! \brief number of root: default 0, means single tree */
-    int num_roots;
-    /*! \brief number of features to be used by trees */
-    int num_feature;
-    /*! \brief size of prediction buffer allocated used for buffering */
-    int64_t num_pbuffer;
-    /*!
-     * \brief how many output group a single instance can produce
-     *  this affects the behavior of number of output we have:
-     *    suppose we have n instance and k group, output will be k*n
-     */
-    int num_output_group;
-    /*! \brief size of leaf vector needed in tree */
-    int size_leaf_vector;
-    /*! \brief reserved parameters */
-    int reserved[31];
-    /*! \brief constructor */
-    ModelParam(void) {
-      std::memset(this, 0, sizeof(ModelParam));
-      num_trees = 0;
-      num_roots = num_feature = 0;
-      num_pbuffer = 0;
-      num_output_group = 1;
-      size_leaf_vector = 0;
-    }
-    /*!
-     * \brief set parameters from outside
-     * \param name name of the parameter
-     * \param val  value of the parameter
-     */
-    inline void SetParam(const char *name, const char *val) {
-      using namespace std;
-      if (!strcmp("num_pbuffer", name)) num_pbuffer = atol(val);
-      if (!strcmp("num_output_group", name)) num_output_group = atol(val);
-      if (!strcmp("bst:num_roots", name)) num_roots = atoi(val);
-      if (!strcmp("bst:num_feature", name)) num_feature = atoi(val);
-      if (!strcmp("bst:size_leaf_vector", name)) size_leaf_vector = atoi(val);
-    }
-    /*! \return size of prediction buffer actually needed */
-    inline size_t PredBufferSize(void) const {
-      return num_output_group * num_pbuffer * (size_leaf_vector + 1);
-    }
-    /*!
-     * \brief get the buffer offset given a buffer index and group id
-     * \return calculated buffer offset
-     */
-    inline int64_t BufferOffset(int64_t buffer_index, int bst_group) const {
-      if (buffer_index < 0) return -1;
-      utils::Check(buffer_index < num_pbuffer, "buffer_index exceed num_pbuffer");
-      return (buffer_index + num_pbuffer * bst_group) * (size_leaf_vector + 1);
-    }
-  };
   // training parameter
-  TrainParam tparam;
+  GBTreeTrainParam tparam;
   // model parameter
-  ModelParam mparam;
+  GBTreeModelParam mparam;
   /*! \brief vector of trees stored in the model */
-  std::vector<tree::RegTree*> trees;
+  std::vector<std::unique_ptr<RegTree> > trees;
   /*! \brief some information indicator of the tree, reserved */
   std::vector<int> tree_info;
   /*! \brief prediction buffer */
@@ -508,13 +455,22 @@ class GBTree : public IGradBooster {
   std::vector<unsigned> pred_counter;
   // ----training fields----
   // configurations for tree
-  std::vector< std::pair<std::string, std::string> > cfg;
+  std::vector<std::pair<std::string, std::string> > cfg;
   // temporal storage for per thread
-  std::vector<tree::RegTree::FVec> thread_temp;
+  std::vector<RegTree::FVec> thread_temp;
   // the updaters that can be applied to each of tree
-  std::vector<tree::IUpdater*> updaters;
+  std::vector<std::unique_ptr<TreeUpdater> > updaters;
 };
 
+// register the ojective functions
+DMLC_REGISTER_PARAMETER(GBTreeModelParam);
+DMLC_REGISTER_PARAMETER(GBTreeTrainParam);
+
+XGBOOST_REGISTER_GBM(GBTree, "gbtree")
+.describe("Tree booster, gradient boosted trees.")
+.set_body([]() {
+    return new GBTree();
+  });
 }  // namespace gbm
 }  // namespace xgboost
-#endif  // XGBOOST_GBM_GBTREE_INL_HPP_
+