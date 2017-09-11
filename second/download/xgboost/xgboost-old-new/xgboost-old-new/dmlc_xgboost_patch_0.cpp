@@ -9,18 +9,17 @@
 #include <dmlc/timer.h>
 #include <xgboost/logging.h>
 #include <xgboost/gbm.h>
+#include <xgboost/predictor.h>
 #include <xgboost/tree_updater.h>
-
 #include <vector>
 #include <memory>
 #include <utility>
 #include <string>
 #include <limits>
-#include <unordered_map>
 #include <algorithm>
 #include "../common/common.h"
-
 #include "../common/random.h"
+#include "gbtree_model.h"
 
 namespace xgboost {
 namespace gbm {
@@ -121,47 +120,6 @@ struct DartTrainParam : public dmlc::Parameter<DartTrainParam> {
   }
 };
 
-/*! \brief model parameters */
-struct GBTreeModelParam : public dmlc::Parameter<GBTreeModelParam> {
-  /*! \brief number of trees */
-  int num_trees;
-  /*! \brief number of roots */
-  int num_roots;
-  /*! \brief number of features to be used by trees */
-  int num_feature;
-  /*! \brief pad this space, for backward compatibility reason.*/
-  int pad_32bit;
-  /*! \brief deprecated padding space. */
-  int64_t num_pbuffer_deprecated;
-  /*!
-   * \brief how many output group a single instance can produce
-   *  this affects the behavior of number of output we have:
-   *    suppose we have n instance and k group, output will be k * n
-   */
-  int num_output_group;
-  /*! \brief size of leaf vector needed in tree */
-  int size_leaf_vector;
-  /*! \brief reserved parameters */
-  int reserved[32];
-  /*! \brief constructor */
-  GBTreeModelParam() {
-    std::memset(this, 0, sizeof(GBTreeModelParam));
-    static_assert(sizeof(GBTreeModelParam) == (4 + 2 + 2 + 32) * sizeof(int),
-                  "64/32 bit compatibility issue");
-  }
-  // declare parameters, only declare those that need to be set.
-  DMLC_DECLARE_PARAMETER(GBTreeModelParam) {
-    DMLC_DECLARE_FIELD(num_output_group).set_lower_bound(1).set_default(1)
-        .describe("Number of output groups to be predicted,"\
-                  " used for multi-class classification.");
-    DMLC_DECLARE_FIELD(num_roots).set_lower_bound(1).set_default(1)
-        .describe("Tree updater sequence.");
-    DMLC_DECLARE_FIELD(num_feature).set_lower_bound(0)
-        .describe("Number of features used for training and prediction.");
-    DMLC_DECLARE_FIELD(size_leaf_vector).set_lower_bound(0).set_default(0)
-        .describe("Reserved option for vector tree.");
-  }
-};
 
 // cache entry
 struct CacheEntry {
@@ -172,22 +130,18 @@ struct CacheEntry {
 // gradient boosted trees
 class GBTree : public GradientBooster {
  public:
-  explicit GBTree(bst_float base_margin) : base_margin_(base_margin) {}
+  explicit GBTree(bst_float base_margin)
+      : model_(base_margin),
+        predictor(
+            std::unique_ptr<Predictor>(Predictor::Create("cpu_predictor"))) {}
 
   void InitCache(const std::vector<std::shared_ptr<DMatrix> > &cache) {
-    for (const std::shared_ptr<DMatrix>& d : cache) {
-      CacheEntry e;
-      e.data = d;
-      cache_[d.get()] = std::move(e);
-    }
+    predictor->InitCache(cache);
   }
 
   void Configure(const std::vector<std::pair<std::string, std::string> >& cfg) override {
     this->cfg = cfg;
-    // initialize model parameters if not yet been initialized.
-    if (trees.size() == 0) {
-      mparam.InitAllowUnknown(cfg);
-    }
+    model_.Configure(cfg);
     // initialize the updaters only when needed.
     std::string updater_seq = tparam.updater_seq;
     tparam.InitAllowUnknown(cfg);
@@ -196,48 +150,25 @@ class GBTree : public GradientBooster {
       up->Init(cfg);
     }
     // for the 'update' process_type, move trees into trees_to_update
-    if (tparam.process_type == kUpdate && trees_to_update.size() == 0u) {
-      for (size_t i = 0; i < trees.size(); ++i) {
-        trees_to_update.push_back(std::move(trees[i]));
-      }
-      trees.clear();
-      mparam.num_trees = 0;
+    if (tparam.process_type == kUpdate) {
+      model_.InitTreesToUpdate();
     }
   }
 
   void Load(dmlc::Stream* fi) override {
-    CHECK_EQ(fi->Read(&mparam, sizeof(mparam)), sizeof(mparam))
-        << "GBTree: invalid model file";
-    trees.clear();
-    trees_to_update.clear();
-    for (int i = 0; i < mparam.num_trees; ++i) {
-      std::unique_ptr<RegTree> ptr(new RegTree());
-      ptr->Load(fi);
-      trees.push_back(std::move(ptr));
-    }
-    tree_info.resize(mparam.num_trees);
-    if (mparam.num_trees != 0) {
-      CHECK_EQ(fi->Read(dmlc::BeginPtr(tree_info), sizeof(int) * mparam.num_trees),
-               sizeof(int) * mparam.num_trees);
-    }
+    model_.Load(fi);
+
     this->cfg.clear();
     this->cfg.push_back(std::make_pair(std::string("num_feature"),
-                                       common::ToString(mparam.num_feature)));
+                                       common::ToString(model_.param.num_feature)));
   }
 
   void Save(dmlc::Stream* fo) const override {
-    CHECK_EQ(mparam.num_trees, static_cast<int>(trees.size()));
-    fo->Write(&mparam, sizeof(mparam));
-    for (size_t i = 0; i < trees.size(); ++i) {
-      trees[i]->Save(fo);
-    }
-    if (tree_info.size() != 0) {
-      fo->Write(dmlc::BeginPtr(tree_info), sizeof(int) * tree_info.size());
-    }
+    model_.Save(fo);
   }
 
   bool AllowLazyCheckPoint() const override {
-    return mparam.num_output_group == 1 ||
+    return model_.param.num_output_group == 1 ||
         tparam.updater_seq.find("distcol") != std::string::npos;
   }
 
@@ -246,7 +177,7 @@ class GBTree : public GradientBooster {
                ObjFunction* obj) override {
     const std::vector<bst_gpair>& gpair = *in_gpair;
     std::vector<std::vector<std::unique_ptr<RegTree> > > new_trees;
-    const int ngroup = mparam.num_output_group;
+    const int ngroup = model_.param.num_output_group;
     if (ngroup == 1) {
       std::vector<std::unique_ptr<RegTree> > ret;
       BoostNewTrees(gpair, p_fmat, 0, &ret);
@@ -275,167 +206,39 @@ class GBTree : public GradientBooster {
     }
   }
 
-  void Predict(DMatrix* p_fmat,
+  void PredictBatch(DMatrix* p_fmat,
                std::vector<bst_float>* out_preds,
                unsigned ntree_limit) override {
-    if (ntree_limit == 0 ||
-        ntree_limit * mparam.num_output_group >= trees.size()) {
-      auto it = cache_.find(p_fmat);
-      if (it != cache_.end()) {
-        std::vector<bst_float>& y = it->second.predictions;
-        if (y.size() != 0) {
-          out_preds->resize(y.size());
-          std::copy(y.begin(), y.end(), out_preds->begin());
-          return;
-        }
-      }
-    }
-    PredLoopInternal<GBTree>(p_fmat, out_preds, 0, ntree_limit, true);
+    predictor->PredictBatch(p_fmat, out_preds, model_, 0, ntree_limit);
   }
 
-  void Predict(const SparseBatch::Inst& inst,
+  void PredictInstance(const SparseBatch::Inst& inst,
                std::vector<bst_float>* out_preds,
                unsigned ntree_limit,
                unsigned root_index) override {
-    if (thread_temp.size() == 0) {
-      thread_temp.resize(1, RegTree::FVec());
-      thread_temp[0].Init(mparam.num_feature);
-    }
-    ntree_limit *= mparam.num_output_group;
-    if (ntree_limit == 0 || ntree_limit > trees.size()) {
-      ntree_limit = static_cast<unsigned>(trees.size());
-    }
-    out_preds->resize(mparam.num_output_group * (mparam.size_leaf_vector+1));
-    // loop over output groups
-    for (int gid = 0; gid < mparam.num_output_group; ++gid) {
-      (*out_preds)[gid] =
-          PredValue(inst, gid, root_index,
-                    &thread_temp[0], 0, ntree_limit) + base_margin_;
-    }
+    predictor->PredictInstance(inst, out_preds, model_,
+                               ntree_limit, root_index);
   }
 
   void PredictLeaf(DMatrix* p_fmat,
                    std::vector<bst_float>* out_preds,
                    unsigned ntree_limit) override {
-    const int nthread = omp_get_max_threads();
-    InitThreadTemp(nthread);
-    this->PredPath(p_fmat, out_preds, ntree_limit);
+    predictor->PredictLeaf(p_fmat, out_preds, model_, ntree_limit);
   }
 
   void PredictContribution(DMatrix* p_fmat,
                            std::vector<bst_float>* out_contribs,
                            unsigned ntree_limit) override {
-    const int nthread = omp_get_max_threads();
-    InitThreadTemp(nthread);
-    this->PredContrib(p_fmat, out_contribs, ntree_limit);
+    predictor->PredictContribution(p_fmat, out_contribs, model_, ntree_limit);
   }
 
   std::vector<std::string> DumpModel(const FeatureMap& fmap,
                                      bool with_stats,
                                      std::string format) const override {
-    std::vector<std::string> dump;
-    for (size_t i = 0; i < trees.size(); i++) {
-      dump.push_back(trees[i]->DumpModel(fmap, with_stats, format));
-    }
-    return dump;
+    return model_.DumpModel(fmap, with_stats, format);
   }
 
  protected:
-  // internal prediction loop
-  // add predictions to out_preds
-  template<typename Derived>
-  inline void PredLoopInternal(
-      DMatrix* p_fmat,
-      std::vector<bst_float>* out_preds,
-      unsigned tree_begin,
-      unsigned ntree_limit,
-      bool init_out_preds) {
-    int num_group = mparam.num_output_group;
-    ntree_limit *= num_group;
-    if (ntree_limit == 0 || ntree_limit > trees.size()) {
-      ntree_limit = static_cast<unsigned>(trees.size());
-    }
-
-    if (init_out_preds) {
-      size_t n = num_group * p_fmat->info().num_row;
-      const std::vector<bst_float>& base_margin = p_fmat->info().base_margin;
-      out_preds->resize(n);
-      if (base_margin.size() != 0) {
-        CHECK_EQ(out_preds->size(), n);
-        std::copy(base_margin.begin(), base_margin.end(), out_preds->begin());
-      } else {
-        std::fill(out_preds->begin(), out_preds->end(), base_margin_);
-      }
-    }
-
-    if (num_group == 1) {
-      PredLoopSpecalize<Derived>(p_fmat, out_preds, 1,
-                                 tree_begin, ntree_limit);
-    } else {
-      PredLoopSpecalize<Derived>(p_fmat, out_preds, num_group,
-                                 tree_begin, ntree_limit);
-    }
-  }
-
-  template<typename Derived>
-  inline void PredLoopSpecalize(
-      DMatrix* p_fmat,
-      std::vector<bst_float>* out_preds,
-      int num_group,
-      unsigned tree_begin,
-      unsigned tree_end) {
-    const MetaInfo& info = p_fmat->info();
-    const int nthread = omp_get_max_threads();
-    CHECK_EQ(num_group, mparam.num_output_group);
-    InitThreadTemp(nthread);
-    std::vector<bst_float>& preds = *out_preds;
-    CHECK_EQ(mparam.size_leaf_vector, 0)
-        << "size_leaf_vector is enforced to 0 so far";
-    CHECK_EQ(preds.size(), p_fmat->info().num_row * num_group);
-    // start collecting the prediction
-    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();
-    Derived* self = static_cast<Derived*>(this);
-    iter->BeforeFirst();
-    while (iter->Next()) {
-      const RowBatch &batch = iter->Value();
-      // parallel over local batch
-      const int K = 8;
-      const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
-      const bst_omp_uint rest = nsize % K;
-      #pragma omp parallel for schedule(static)
-      for (bst_omp_uint i = 0; i < nsize - rest; i += K) {
-        const int tid = omp_get_thread_num();
-        RegTree::FVec& feats = thread_temp[tid];
-        int64_t ridx[K];
-        RowBatch::Inst inst[K];
-        for (int k = 0; k < K; ++k) {
-          ridx[k] = static_cast<int64_t>(batch.base_rowid + i + k);
-        }
-        for (int k = 0; k < K; ++k) {
-          inst[k] = batch[i + k];
-        }
-        for (int k = 0; k < K; ++k) {
-          for (int gid = 0; gid < num_group; ++gid) {
-            const size_t offset = ridx[k] * num_group + gid;
-            preds[offset] +=
-                self->PredValue(inst[k], gid, info.GetRoot(ridx[k]),
-                                &feats, tree_begin, tree_end);
-          }
-        }
-      }
-      for (bst_omp_uint i = nsize - rest; i < nsize; ++i) {
-        RegTree::FVec& feats = thread_temp[0];
-        const int64_t ridx = static_cast<int64_t>(batch.base_rowid + i);
-        const RowBatch::Inst inst = batch[i];
-        for (int gid = 0; gid < num_group; ++gid) {
-          const size_t offset = ridx * num_group + gid;
-          preds[offset] +=
-              self->PredValue(inst, gid, info.GetRoot(ridx),
-                              &feats, tree_begin, tree_end);
-        }
-      }
-    }
-  }
   // initialize updater before using them
   inline void InitUpdater() {
     if (updaters.size() != 0) return;
@@ -466,9 +269,9 @@ class GBTree : public GradientBooster {
         new_trees.push_back(ptr.get());
         ret->push_back(std::move(ptr));
       } else if (tparam.process_type == kUpdate) {
-        CHECK_LT(trees.size(), trees_to_update.size());
+        CHECK_LT(model_.trees.size(), model_.trees_to_update.size());
         // move an existing tree from trees_to_update
-        auto t = std::move(trees_to_update[trees.size() +
+        auto t = std::move(model_.trees_to_update[model_.trees.size() +
                            bst_group * tparam.num_parallel_tree + i]);
         new_trees.push_back(t.get());
         ret->push_back(std::move(t));
@@ -483,173 +286,22 @@ class GBTree : public GradientBooster {
   virtual void
   CommitModel(std::vector<std::unique_ptr<RegTree> >&& new_trees,
               int bst_group) {
-    size_t old_ntree = trees.size();
-    for (size_t i = 0; i < new_trees.size(); ++i) {
-      trees.push_back(std::move(new_trees[i]));
-      tree_info.push_back(bst_group);
-    }
-    mparam.num_trees += static_cast<int>(new_trees.size());
+    model_.CommitModel(std::move(new_trees), bst_group);
 
-    // update cache entry
-    for (auto &kv : cache_) {
-      CacheEntry& e = kv.second;
-
-      if (e.predictions.size() == 0) {
-        PredLoopInternal<GBTree>(
-            e.data.get(), &(e.predictions),
-            0, trees.size(), true);
-      } else {
-        if (mparam.num_output_group == 1 && updaters.size() > 0 && new_trees.size() == 1
-          && updaters.back()->UpdatePredictionCache(e.data.get(), &(e.predictions)) ) {
-          {}  // do nothing
-        } else {
-          PredLoopInternal<GBTree>(
-              e.data.get(), &(e.predictions),
-              old_ntree, trees.size(), false);
-        }
-      }
-    }
+    predictor->UpdatePredictionCache(model_, &updaters, new_trees.size());
   }
 
-  // make a prediction for a single instance
-  inline bst_float PredValue(const RowBatch::Inst &inst,
-                             int bst_group,
-                             unsigned root_index,
-                             RegTree::FVec *p_feats,
-                             unsigned tree_begin,
-                             unsigned tree_end) {
-    bst_float psum = 0.0f;
-    p_feats->Fill(inst);
-    for (size_t i = tree_begin; i < tree_end; ++i) {
-      if (tree_info[i] == bst_group) {
-        int tid = trees[i]->GetLeafIndex(*p_feats, root_index);
-        psum += (*trees[i])[tid].leaf_value();
-      }
-    }
-    p_feats->Drop(inst);
-    return psum;
-  }
-  // predict independent leaf index
-  inline void PredPath(DMatrix *p_fmat,
-                       std::vector<bst_float> *out_preds,
-                       unsigned ntree_limit) {
-    const MetaInfo& info = p_fmat->info();
-    // number of valid trees
-    ntree_limit *= mparam.num_output_group;
-    if (ntree_limit == 0 || ntree_limit > trees.size()) {
-      ntree_limit = static_cast<unsigned>(trees.size());
-    }
-    std::vector<bst_float>& preds = *out_preds;
-    preds.resize(info.num_row * ntree_limit);
-    // start collecting the prediction
-    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();
-    iter->BeforeFirst();
-    while (iter->Next()) {
-      const RowBatch& batch = iter->Value();
-      // parallel over local batch
-      const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
-      #pragma omp parallel for schedule(static)
-      for (bst_omp_uint i = 0; i < nsize; ++i) {
-        const int tid = omp_get_thread_num();
-        size_t ridx = static_cast<size_t>(batch.base_rowid + i);
-        RegTree::FVec &feats = thread_temp[tid];
-        feats.Fill(batch[i]);
-        for (unsigned j = 0; j < ntree_limit; ++j) {
-          int tid = trees[j]->GetLeafIndex(feats, info.GetRoot(ridx));
-          preds[ridx * ntree_limit + j] = static_cast<bst_float>(tid);
-        }
-        feats.Drop(batch[i]);
-      }
-    }
-  }
-  // predict contributions
-  inline void PredContrib(DMatrix *p_fmat,
-                          std::vector<bst_float> *out_contribs,
-                          unsigned ntree_limit) {
-    const MetaInfo& info = p_fmat->info();
-    // number of valid trees
-    ntree_limit *= mparam.num_output_group;
-    if (ntree_limit == 0 || ntree_limit > trees.size()) {
-      ntree_limit = static_cast<unsigned>(trees.size());
-    }
-    const int ngroup = mparam.num_output_group;
-    size_t ncolumns = mparam.num_feature + 1;
-    // allocate space for (number of features + bias) times the number of rows
-    std::vector<bst_float>& contribs = *out_contribs;
-    contribs.resize(info.num_row * ncolumns * mparam.num_output_group);
-    // make sure contributions is zeroed, we could be reusing a previously allocated one
-    std::fill(contribs.begin(), contribs.end(), 0);
-    // initialize tree node mean values
-    #pragma omp parallel for schedule(static)
-    for (bst_omp_uint i=0; i < ntree_limit; ++i) {
-      trees[i]->FillNodeMeanValues();
-    }
-    // start collecting the contributions
-    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();
-    const std::vector<bst_float>& base_margin = info.base_margin;
-    iter->BeforeFirst();
-    while (iter->Next()) {
-      const RowBatch& batch = iter->Value();
-      // parallel over local batch
-      const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
-      #pragma omp parallel for schedule(static)
-      for (bst_omp_uint i = 0; i < nsize; ++i) {
-        size_t row_idx = static_cast<size_t>(batch.base_rowid + i);
-        unsigned root_id = info.GetRoot(row_idx);
-        RegTree::FVec &feats = thread_temp[omp_get_thread_num()];
-        // loop over all classes
-        for (int gid = 0; gid < ngroup; ++gid) {
-          bst_float *p_contribs = &contribs[(row_idx * ngroup + gid) * ncolumns];
-          feats.Fill(batch[i]);
-          // calculate contributions
-          for (unsigned j = 0; j < ntree_limit; ++j) {
-            if (tree_info[j] != gid) {
-              continue;
-            }
-            trees[j]->CalculateContributions(feats, root_id, p_contribs);
-          }
-          feats.Drop(batch[i]);
-          // add base margin to BIAS
-          if (base_margin.size() != 0) {
-            p_contribs[ncolumns - 1] += base_margin[row_idx * ngroup + gid];
-          } else {
-            p_contribs[ncolumns - 1] += base_margin_;
-          }
-        }
-      }
-    }
-  }
-  // init thread buffers
-  inline void InitThreadTemp(int nthread) {
-    int prev_thread_temp_size = thread_temp.size();
-    if (prev_thread_temp_size < nthread) {
-      thread_temp.resize(nthread, RegTree::FVec());
-      for (int i = prev_thread_temp_size; i < nthread; ++i) {
-        thread_temp[i].Init(mparam.num_feature);
-      }
-    }
-  }
   // --- data structure ---
-  // base margin
-  bst_float base_margin_;
+  GBTreeModel model_;
   // training parameter
   GBTreeTrainParam tparam;
-  // model parameter
-  GBTreeModelParam mparam;
-  /*! \brief vector of trees stored in the model */
-  std::vector<std::unique_ptr<RegTree> > trees;
-  /*! \brief for the update process, a place to keep the initial trees */
-  std::vector<std::unique_ptr<RegTree> > trees_to_update;
-  /*! \brief some information indicator of the tree, reserved */
-  std::vector<int> tree_info;
   // ----training fields----
-  std::unordered_map<DMatrix*, CacheEntry> cache_;
   // configurations for tree
   std::vector<std::pair<std::string, std::string> > cfg;
-  // temporal storage for per thread
-  std::vector<RegTree::FVec> thread_temp;
   // the updaters that can be applied to each of tree
-  std::vector<std::unique_ptr<TreeUpdater> > updaters;
+  std::vector<std::unique_ptr<TreeUpdater>> updaters;
+
+  std::unique_ptr<Predictor> predictor;
 };
 
 // dart
@@ -659,15 +311,15 @@ class Dart : public GBTree {
 
   void Configure(const std::vector<std::pair<std::string, std::string> >& cfg) override {
     GBTree::Configure(cfg);
-    if (trees.size() == 0) {
+    if (model_.trees.size() == 0) {
       dparam.InitAllowUnknown(cfg);
     }
   }
 
   void Load(dmlc::Stream* fi) override {
     GBTree::Load(fi);
-    weight_drop.resize(mparam.num_trees);
-    if (mparam.num_trees != 0) {
+    weight_drop.resize(model_.param.num_trees);
+    if (model_.param.num_trees != 0) {
       fi->Read(&weight_drop);
     }
   }
@@ -680,45 +332,140 @@ class Dart : public GBTree {
   }
 
   // predict the leaf scores with dropout if ntree_limit = 0
-  void Predict(DMatrix* p_fmat,
+  void PredictBatch(DMatrix* p_fmat,
                std::vector<bst_float>* out_preds,
                unsigned ntree_limit) override {
     DropTrees(ntree_limit);
     PredLoopInternal<Dart>(p_fmat, out_preds, 0, ntree_limit, true);
   }
 
-  void Predict(const SparseBatch::Inst& inst,
+  void PredictInstance(const SparseBatch::Inst& inst,
                std::vector<bst_float>* out_preds,
                unsigned ntree_limit,
                unsigned root_index) override {
     DropTrees(1);
     if (thread_temp.size() == 0) {
       thread_temp.resize(1, RegTree::FVec());
-      thread_temp[0].Init(mparam.num_feature);
+      thread_temp[0].Init(model_.param.num_feature);
     }
-    out_preds->resize(mparam.num_output_group);
-    ntree_limit *= mparam.num_output_group;
-    if (ntree_limit == 0 || ntree_limit > trees.size()) {
-      ntree_limit = static_cast<unsigned>(trees.size());
+    out_preds->resize(model_.param.num_output_group);
+    ntree_limit *= model_.param.num_output_group;
+    if (ntree_limit == 0 || ntree_limit > model_.trees.size()) {
+      ntree_limit = static_cast<unsigned>(model_.trees.size());
     }
     // loop over output groups
-    for (int gid = 0; gid < mparam.num_output_group; ++gid) {
+    for (int gid = 0; gid < model_.param.num_output_group; ++gid) {
       (*out_preds)[gid]
           = PredValue(inst, gid, root_index,
-                      &thread_temp[0], 0, ntree_limit) + base_margin_;
+                      &thread_temp[0], 0, ntree_limit) + model_.base_margin;
     }
   }
 
  protected:
   friend class GBTree;
+  // internal prediction loop
+  // add predictions to out_preds
+  template<typename Derived>
+  inline void PredLoopInternal(
+      DMatrix* p_fmat,
+      std::vector<bst_float>* out_preds,
+      unsigned tree_begin,
+      unsigned ntree_limit,
+      bool init_out_preds) {
+    int num_group = model_.param.num_output_group;
+    ntree_limit *= num_group;
+    if (ntree_limit == 0 || ntree_limit > model_.trees.size()) {
+      ntree_limit = static_cast<unsigned>(model_.trees.size());
+    }
+
+    if (init_out_preds) {
+      size_t n = num_group * p_fmat->info().num_row;
+      const std::vector<bst_float>& base_margin = p_fmat->info().base_margin;
+      out_preds->resize(n);
+      if (base_margin.size() != 0) {
+        CHECK_EQ(out_preds->size(), n);
+        std::copy(base_margin.begin(), base_margin.end(), out_preds->begin());
+      } else {
+        std::fill(out_preds->begin(), out_preds->end(), model_.base_margin);
+      }
+    }
+
+    if (num_group == 1) {
+      PredLoopSpecalize<Derived>(p_fmat, out_preds, 1,
+                                 tree_begin, ntree_limit);
+    } else {
+      PredLoopSpecalize<Derived>(p_fmat, out_preds, num_group,
+                                 tree_begin, ntree_limit);
+    }
+  }
+
+  template<typename Derived>
+  inline void PredLoopSpecalize(
+      DMatrix* p_fmat,
+      std::vector<bst_float>* out_preds,
+      int num_group,
+      unsigned tree_begin,
+      unsigned tree_end) {
+    const MetaInfo& info = p_fmat->info();
+    const int nthread = omp_get_max_threads();
+    CHECK_EQ(num_group, model_.param.num_output_group);
+    InitThreadTemp(nthread);
+    std::vector<bst_float>& preds = *out_preds;
+    CHECK_EQ(model_.param.size_leaf_vector, 0)
+        << "size_leaf_vector is enforced to 0 so far";
+    CHECK_EQ(preds.size(), p_fmat->info().num_row * num_group);
+    // start collecting the prediction
+    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();
+    Derived* self = static_cast<Derived*>(this);
+    iter->BeforeFirst();
+    while (iter->Next()) {
+      const RowBatch &batch = iter->Value();
+      // parallel over local batch
+      const int K = 8;
+      const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
+      const bst_omp_uint rest = nsize % K;
+      #pragma omp parallel for schedule(static)
+      for (bst_omp_uint i = 0; i < nsize - rest; i += K) {
+        const int tid = omp_get_thread_num();
+        RegTree::FVec& feats = thread_temp[tid];
+        int64_t ridx[K];
+        RowBatch::Inst inst[K];
+        for (int k = 0; k < K; ++k) {
+          ridx[k] = static_cast<int64_t>(batch.base_rowid + i + k);
+        }
+        for (int k = 0; k < K; ++k) {
+          inst[k] = batch[i + k];
+        }
+        for (int k = 0; k < K; ++k) {
+          for (int gid = 0; gid < num_group; ++gid) {
+            const size_t offset = ridx[k] * num_group + gid;
+            preds[offset] +=
+                self->PredValue(inst[k], gid, info.GetRoot(ridx[k]),
+                                &feats, tree_begin, tree_end);
+          }
+        }
+      }
+      for (bst_omp_uint i = nsize - rest; i < nsize; ++i) {
+        RegTree::FVec& feats = thread_temp[0];
+        const int64_t ridx = static_cast<int64_t>(batch.base_rowid + i);
+        const RowBatch::Inst inst = batch[i];
+        for (int gid = 0; gid < num_group; ++gid) {
+          const size_t offset = ridx * num_group + gid;
+          preds[offset] +=
+              self->PredValue(inst, gid, info.GetRoot(ridx),
+                              &feats, tree_begin, tree_end);
+        }
+      }
+    }
+  }
   // commit new trees all at once
   void CommitModel(std::vector<std::unique_ptr<RegTree> >&& new_trees,
                    int bst_group) override {
     for (size_t i = 0; i < new_trees.size(); ++i) {
-      trees.push_back(std::move(new_trees[i]));
-      tree_info.push_back(bst_group);
+      model_.trees.push_back(std::move(new_trees[i]));
+      model_.tree_info.push_back(bst_group);
     }
-    mparam.num_trees += static_cast<int>(new_trees.size());
+    model_.param.num_trees += static_cast<int>(new_trees.size());
     size_t num_drop = NormalizeTrees(new_trees.size());
     if (dparam.silent != 1) {
       LOG(INFO) << "drop " << num_drop << " trees, "
@@ -735,11 +482,11 @@ class Dart : public GBTree {
     bst_float psum = 0.0f;
     p_feats->Fill(inst);
     for (size_t i = tree_begin; i < tree_end; ++i) {
-      if (tree_info[i] == bst_group) {
+      if (model_.tree_info[i] == bst_group) {
         bool drop = (std::binary_search(idx_drop.begin(), idx_drop.end(), i));
         if (!drop) {
-          int tid = trees[i]->GetLeafIndex(*p_feats, root_index);
-          psum += weight_drop[i] * (*trees[i])[tid].leaf_value();
+          int tid = model_.trees[i]->GetLeafIndex(*p_feats, root_index);
+          psum += weight_drop[i] * (*model_.trees[i])[tid].leaf_value();
         }
       }
     }
@@ -825,13 +572,26 @@ class Dart : public GBTree {
     return num_drop;
   }
 
+  // init thread buffers
+  inline void InitThreadTemp(int nthread) {
+    int prev_thread_temp_size = thread_temp.size();
+    if (prev_thread_temp_size < nthread) {
+      thread_temp.resize(nthread, RegTree::FVec());
+      for (int i = prev_thread_temp_size; i < nthread; ++i) {
+        thread_temp[i].Init(model_.param.num_feature);
+      }
+    }
+  }
+
   // --- data structure ---
   // training parameter
   DartTrainParam dparam;
   /*! \brief prediction buffer */
   std::vector<bst_float> weight_drop;
   // indexes of dropped trees
   std::vector<size_t> idx_drop;
+  // temporal storage for per thread
+  std::vector<RegTree::FVec> thread_temp;
 };
 
 // register the objective functions