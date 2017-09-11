@@ -1,46 +1,41 @@
 /*!
  * Copyright 2014 by Contributors
- * \file updater_colmaker-inl.hpp
+ * \file updater_colmaker.cc
  * \brief use columnwise update to construct a tree
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_TREE_UPDATER_COLMAKER_INL_HPP_
-#define XGBOOST_TREE_UPDATER_COLMAKER_INL_HPP_
-
+#include <xgboost/tree_updater.h>
 #include <vector>
 #include <cmath>
 #include <algorithm>
 #include "./param.h"
-#include "./updater.h"
-#include "../utils/omp.h"
-#include "../utils/random.h"
+#include "../common/random.h"
+#include "../common/bitmap.h"
+#include "../common/sync.h"
 
 namespace xgboost {
 namespace tree {
 /*! \brief column-wise update to construct a tree */
 template<typename TStats>
-class ColMaker: public IUpdater {
+class ColMaker: public TreeUpdater {
  public:
-  virtual ~ColMaker(void) {}
-  // set training parameter
-  virtual void SetParam(const char *name, const char *val) {
-    param.SetParam(name, val);
+  void Init(const std::vector<std::pair<std::string, std::string> >& args) override {
+    param.Init(args);
   }
-  virtual void Update(const std::vector<bst_gpair> &gpair,
-                      IFMatrix *p_fmat,
-                      const BoosterInfo &info,
-                      const std::vector<RegTree*> &trees) {
-    TStats::CheckInfo(info);
+
+  void Update(const std::vector<bst_gpair> &gpair,
+              DMatrix* dmat,
+              const std::vector<RegTree*> &trees) override {
+    TStats::CheckInfo(dmat->info());
     // rescale learning rate according to size of trees
-    float lr = param.learning_rate;
-    param.learning_rate = lr / trees.size();
+    float lr = param.eta;
+    param.eta = lr / trees.size();
     // build tree
     for (size_t i = 0; i < trees.size(); ++i) {
       Builder builder(param);
-      builder.Update(gpair, p_fmat, info, trees[i]);
+      builder.Update(gpair, dmat, trees[i]);
     }
-
-    param.learning_rate = lr;
+    param.eta = lr;
   }
 
  protected:
@@ -74,34 +69,33 @@ class ColMaker: public IUpdater {
     /*! \brief current best solution */
     SplitEntry best;
     // constructor
-    explicit NodeEntry(const TrainParam &param)
+    explicit NodeEntry(const TrainParam& param)
         : stats(param), root_gain(0.0f), weight(0.0f){
     }
   };
   // actual builder that runs the algorithm
-  struct Builder{
+  struct Builder {
    public:
     // constructor
-    explicit Builder(const TrainParam &param) : param(param) {}
+    explicit Builder(const TrainParam& param) : param(param) {}
     // update one tree, growing
-    virtual void Update(const std::vector<bst_gpair> &gpair,
-                        IFMatrix *p_fmat,
-                        const BoosterInfo &info,
-                        RegTree *p_tree) {
-      this->InitData(gpair, *p_fmat, info.root_index, *p_tree);
-      this->InitNewNode(qexpand_, gpair, *p_fmat, info, *p_tree);
+    virtual void Update(const std::vector<bst_gpair>& gpair,
+                        DMatrix* p_fmat,
+                        RegTree* p_tree) {
+      this->InitData(gpair, *p_fmat, *p_tree);
+      this->InitNewNode(qexpand_, gpair, *p_fmat, *p_tree);
       for (int depth = 0; depth < param.max_depth; ++depth) {
-        this->FindSplit(depth, qexpand_, gpair, p_fmat, info, p_tree);
+        this->FindSplit(depth, qexpand_, gpair, p_fmat, p_tree);
         this->ResetPosition(qexpand_, p_fmat, *p_tree);
         this->UpdateQueueExpand(*p_tree, &qexpand_);
-        this->InitNewNode(qexpand_, gpair, *p_fmat, info, *p_tree);
+        this->InitNewNode(qexpand_, gpair, *p_fmat, *p_tree);
         // if nothing left to be expand, break
         if (qexpand_.size() == 0) break;
       }
       // set all the rest expanding nodes to leaf
       for (size_t i = 0; i < qexpand_.size(); ++i) {
         const int nid = qexpand_[i];
-        (*p_tree)[nid].set_leaf(snode[nid].weight * param.learning_rate);
+        (*p_tree)[nid].set_leaf(snode[nid].weight * param.eta);
       }
       // remember auxiliary statistics in the tree node
       for (int nid = 0; nid < p_tree->param.num_nodes; ++nid) {
@@ -114,13 +108,13 @@ class ColMaker: public IUpdater {
 
    protected:
     // initialize temp data structure
-    inline void InitData(const std::vector<bst_gpair> &gpair,
-                         const IFMatrix &fmat,
-                         const std::vector<unsigned> &root_index,
-                         const RegTree &tree) {
-      utils::Assert(tree.param.num_nodes == tree.param.num_roots,
-                    "ColMaker: can only grow new tree");
-      const std::vector<bst_uint> &rowset = fmat.buffered_rowset();
+    inline void InitData(const std::vector<bst_gpair>& gpair,
+                         const DMatrix& fmat,
+                         const RegTree& tree) {
+      CHECK_EQ(tree.param.num_nodes, tree.param.num_roots)
+          << "ColMaker: can only grow new tree";
+      const std::vector<unsigned>& root_index = fmat.info().root_index;
+      const std::vector<bst_uint>& rowset = fmat.buffered_rowset();
       {
         // setup position
         position.resize(gpair.size());
@@ -132,8 +126,7 @@ class ColMaker: public IUpdater {
           for (size_t i = 0; i < rowset.size(); ++i) {
             const bst_uint ridx = rowset[i];
             position[ridx] = root_index[ridx];
-            utils::Assert(root_index[ridx] < (unsigned)tree.param.num_roots,
-                          "root index exceed setting");
+            CHECK_LT(root_index[ridx], (unsigned)tree.param.num_roots);
           }
         }
         // mark delete for the deleted datas
@@ -143,25 +136,28 @@ class ColMaker: public IUpdater {
         }
         // mark subsample
         if (param.subsample < 1.0f) {
+          std::bernoulli_distribution coin_flip(param.subsample);
+          auto& rnd = common::GlobalRandom();
           for (size_t i = 0; i < rowset.size(); ++i) {
             const bst_uint ridx = rowset[i];
             if (gpair[ridx].hess < 0.0f) continue;
-            if (random::SampleBinary(param.subsample) == 0) position[ridx] = ~position[ridx];
+            if (!coin_flip(rnd)) position[ridx] = ~position[ridx];
           }
         }
       }
       {
         // initialize feature index
-        unsigned ncol = static_cast<unsigned>(fmat.NumCol());
+        unsigned ncol = static_cast<unsigned>(fmat.info().num_col);
         for (unsigned i = 0; i < ncol; ++i) {
           if (fmat.GetColSize(i) != 0) {
             feat_index.push_back(i);
           }
         }
         unsigned n = static_cast<unsigned>(param.colsample_bytree * feat_index.size());
-        random::Shuffle(feat_index);
-        utils::Check(n > 0, "colsample_bytree=%g is too small that no feature can be included",
-                     param.colsample_bytree);
+        std::shuffle(feat_index.begin(), feat_index.end(), common::GlobalRandom());
+        CHECK_GT(n, 0)
+            << "colsample_bytree=" << param.colsample_bytree
+            << " is too small that no feature can be included";
         feat_index.resize(n);
       }
       {
@@ -190,11 +186,10 @@ class ColMaker: public IUpdater {
      * \brief initialize the base_weight, root_gain,
      *  and NodeEntry for all the new nodes in qexpand
      */
-    inline void InitNewNode(const std::vector<int> &qexpand,
-                            const std::vector<bst_gpair> &gpair,
-                            const IFMatrix &fmat,
-                            const BoosterInfo &info,
-                            const RegTree &tree) {
+    inline void InitNewNode(const std::vector<int>& qexpand,
+                            const std::vector<bst_gpair>& gpair,
+                            const DMatrix& fmat,
+                            const RegTree& tree) {
       {
         // setup statistics space for each tree node
         for (size_t i = 0; i < stemp.size(); ++i) {
@@ -203,6 +198,7 @@ class ColMaker: public IUpdater {
         snode.resize(tree.param.num_nodes, NodeEntry(param));
       }
       const std::vector<bst_uint> &rowset = fmat.buffered_rowset();
+      const MetaInfo& info = fmat.info();
       // setup position
       const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
       #pragma omp parallel for schedule(static)
@@ -226,7 +222,7 @@ class ColMaker: public IUpdater {
       }
     }
     /*! \brief update queue expand add in new leaves */
-    inline void UpdateQueueExpand(const RegTree &tree, std::vector<int> *p_qexpand) {
+    inline void UpdateQueueExpand(const RegTree& tree, std::vector<int>* p_qexpand) {
       std::vector<int> &qexpand = *p_qexpand;
       std::vector<int> newnodes;
       for (size_t i = 0; i < qexpand.size(); ++i) {
@@ -243,9 +239,9 @@ class ColMaker: public IUpdater {
     // this function does not support nested functions
     inline void ParallelFindSplit(const ColBatch::Inst &col,
                                   bst_uint fid,
-                                  const IFMatrix &fmat,
-                                  const std::vector<bst_gpair> &gpair,
-                                  const BoosterInfo &info) {
+                                  const DMatrix &fmat,
+                                  const std::vector<bst_gpair> &gpair) {
+      const MetaInfo& info = fmat.info();
       const bool ind = col.length != 0 && col.data[0].fvalue == col.data[col.length - 1].fvalue;
       bool need_forward = param.need_forward_search(fmat.GetColDensity(fid), ind);
       bool need_backward = param.need_backward_search(fmat.GetColDensity(fid), ind);
@@ -484,7 +480,7 @@ class ColMaker: public IUpdater {
                                int d_step,
                                bst_uint fid,
                                const std::vector<bst_gpair> &gpair,
-                               const BoosterInfo &info,
+                               const MetaInfo &info,
                                std::vector<ThreadEntry> &temp) { // NOLINT(*)
       // use cacheline aware optimization
       if (TStats::kSimpleStats != 0 && param.cache_opt != 0) {
@@ -542,10 +538,10 @@ class ColMaker: public IUpdater {
     }
 
     // update the solution candidate
-    virtual void UpdateSolution(const ColBatch &batch,
-                                const std::vector<bst_gpair> &gpair,
-                                const IFMatrix &fmat,
-                                const BoosterInfo &info) {
+    virtual void UpdateSolution(const ColBatch& batch,
+                                const std::vector<bst_gpair>& gpair,
+                                const DMatrix& fmat) {
+      const MetaInfo& info = fmat.info();
       // start enumeration
       const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
       #if defined(_OPENMP)
@@ -574,27 +570,27 @@ class ColMaker: public IUpdater {
       } else {
         for (bst_omp_uint i = 0; i < nsize; ++i) {
           this->ParallelFindSplit(batch[i], batch.col_index[i],
-                                  fmat, gpair, info);
+                                  fmat, gpair);
         }
       }
     }
     // find splits at current level, do split per level
     inline void FindSplit(int depth,
                           const std::vector<int> &qexpand,
                           const std::vector<bst_gpair> &gpair,
-                          IFMatrix *p_fmat,
-                          const BoosterInfo &info,
+                          DMatrix *p_fmat,
                           RegTree *p_tree) {
       std::vector<bst_uint> feat_set = feat_index;
       if (param.colsample_bylevel != 1.0f) {
-        random::Shuffle(feat_set);
+        std::shuffle(feat_set.begin(), feat_set.end(), common::GlobalRandom());
         unsigned n = static_cast<unsigned>(param.colsample_bylevel * feat_index.size());
-        utils::Check(n > 0, "colsample_bylevel is too small that no feature can be included");
+        CHECK_GT(n, 0)
+            << "colsample_bylevel is too small that no feature can be included";
         feat_set.resize(n);
       }
-      utils::IIterator<ColBatch> *iter = p_fmat->ColIterator(feat_set);
+      dmlc::DataIter<ColBatch>* iter = p_fmat->ColIterator(feat_set);
       while (iter->Next()) {
-        this->UpdateSolution(iter->Value(), gpair, *p_fmat, info);
+        this->UpdateSolution(iter->Value(), gpair, *p_fmat);
       }
       // after this each thread's stemp will get the best candidates, aggregate results
       this->SyncBestSolution(qexpand);
@@ -610,13 +606,14 @@ class ColMaker: public IUpdater {
           (*p_tree)[(*p_tree)[nid].cleft()].set_leaf(0.0f, 0);
           (*p_tree)[(*p_tree)[nid].cright()].set_leaf(0.0f, 0);
         } else {
-          (*p_tree)[nid].set_leaf(e.weight * param.learning_rate);
+          (*p_tree)[nid].set_leaf(e.weight * param.eta);
         }
       }
     }
     // reset position of each data points after split is created in the tree
     inline void ResetPosition(const std::vector<int> &qexpand,
-                              IFMatrix *p_fmat, const RegTree &tree) {
+                              DMatrix* p_fmat,
+                              const RegTree& tree) {
       // set the positions in the nondefault
       this->SetNonDefaultPosition(qexpand, p_fmat, tree);
       // set rest of instances to default position
@@ -630,7 +627,7 @@ class ColMaker: public IUpdater {
       for (bst_omp_uint i = 0; i < ndata; ++i) {
         const bst_uint ridx = rowset[i];
         if (ridx >= position.size()) {
-          utils::Printf("ridx exceed bound\n");
+          LOG(INFO) << "ridx exceed bound\n";
         }
         const int nid = this->DecodePosition(ridx);
         if (tree[nid].is_leaf()) {
@@ -660,7 +657,8 @@ class ColMaker: public IUpdater {
       }
     }
     virtual void SetNonDefaultPosition(const std::vector<int> &qexpand,
-                                       IFMatrix *p_fmat, const RegTree &tree) {
+                                       DMatrix *p_fmat,
+                                       const RegTree &tree) {
       // step 1, classify the non-default data into right places
       std::vector<unsigned> fsplits;
       for (size_t i = 0; i < qexpand.size(); ++i) {
@@ -671,8 +669,7 @@ class ColMaker: public IUpdater {
       }
       std::sort(fsplits.begin(), fsplits.end());
       fsplits.resize(std::unique(fsplits.begin(), fsplits.end()) - fsplits.begin());
-
-      utils::IIterator<ColBatch> *iter = p_fmat->ColIterator(fsplits);
+      dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator(fsplits);
       while (iter->Next()) {
         const ColBatch &batch = iter->Value();
         for (size_t i = 0; i < batch.size; ++i) {
@@ -711,7 +708,7 @@ class ColMaker: public IUpdater {
       }
     }
     //  --data fields--
-    const TrainParam &param;
+    const TrainParam& param;
     // number of omp thread used during training
     int nthread;
     // Per feature: shuffle index of each feature index
@@ -727,6 +724,171 @@ class ColMaker: public IUpdater {
   };
 };
 
+// distributed column maker
+template<typename TStats>
+class DistColMaker : public ColMaker<TStats> {
+ public:
+  DistColMaker() : builder(param) {
+    pruner.reset(TreeUpdater::Create("prune"));
+  }
+  void Init(const std::vector<std::pair<std::string, std::string> >& args) override {
+    param.Init(args);
+    pruner->Init(args);
+  }
+  void Update(const std::vector<bst_gpair> &gpair,
+              DMatrix* dmat,
+              const std::vector<RegTree*> &trees) override {
+    TStats::CheckInfo(dmat->info());
+    CHECK_EQ(trees.size(), 1) << "DistColMaker: only support one tree at a time";
+    // build the tree
+    builder.Update(gpair, dmat, trees[0]);
+    //// prune the tree, note that pruner will sync the tree
+    pruner->Update(gpair, dmat, trees);
+    // update position after the tree is pruned
+    builder.UpdatePosition(dmat, *trees[0]);
+  }
+  virtual const int* GetLeafPosition() const {
+    return builder.GetLeafPosition();
+  }
+
+ private:
+  struct Builder : public ColMaker<TStats>::Builder {
+   public:
+    explicit Builder(const TrainParam &param)
+        : ColMaker<TStats>::Builder(param) {
+    }
+    inline void UpdatePosition(DMatrix* p_fmat, const RegTree &tree) {
+      const std::vector<bst_uint> &rowset = p_fmat->buffered_rowset();
+      const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
+      #pragma omp parallel for schedule(static)
+      for (bst_omp_uint i = 0; i < ndata; ++i) {
+        const bst_uint ridx = rowset[i];
+        int nid = this->DecodePosition(ridx);
+        while (tree[nid].is_deleted()) {
+          nid = tree[nid].parent();
+          CHECK_GE(nid, 0);
+        }
+        this->position[ridx] = nid;
+      }
+    }
+    const int* GetLeafPosition() const override {
+      return dmlc::BeginPtr(this->position);
+    }
+
+   protected:
+    void SetNonDefaultPosition(const std::vector<int> &qexpand,
+                               DMatrix *p_fmat,
+                               const RegTree &tree) override {
+     // step 2, classify the non-default data into right places
+      std::vector<unsigned> fsplits;
+      for (size_t i = 0; i < qexpand.size(); ++i) {
+        const int nid = qexpand[i];
+        if (!tree[nid].is_leaf()) {
+          fsplits.push_back(tree[nid].split_index());
+        }
+      }
+      // get the candidate split index
+      std::sort(fsplits.begin(), fsplits.end());
+      fsplits.resize(std::unique(fsplits.begin(), fsplits.end()) - fsplits.begin());
+      while (fsplits.size() != 0 && fsplits.back() >= p_fmat->info().num_col) {
+        fsplits.pop_back();
+      }
+      // bitmap is only word concurrent, set to bool first
+      {
+        bst_omp_uint ndata = static_cast<bst_omp_uint>(this->position.size());
+        boolmap.resize(ndata);
+        #pragma omp parallel for schedule(static)
+        for (bst_omp_uint j = 0; j < ndata; ++j) {
+            boolmap[j] = 0;
+        }
+      }
+      dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator(fsplits);
+      while (iter->Next()) {
+        const ColBatch &batch = iter->Value();
+        for (size_t i = 0; i < batch.size; ++i) {
+          ColBatch::Inst col = batch[i];
+          const bst_uint fid = batch.col_index[i];
+          const bst_omp_uint ndata = static_cast<bst_omp_uint>(col.length);
+          #pragma omp parallel for schedule(static)
+          for (bst_omp_uint j = 0; j < ndata; ++j) {
+            const bst_uint ridx = col[j].index;
+            const float fvalue = col[j].fvalue;
+            const int nid = this->DecodePosition(ridx);
+            if (!tree[nid].is_leaf() && tree[nid].split_index() == fid) {
+              if (fvalue < tree[nid].split_cond()) {
+                if (!tree[nid].default_left()) boolmap[ridx] = 1;
+              } else {
+                if (tree[nid].default_left()) boolmap[ridx] = 1;
+              }
+            }
+          }
+        }
+      }
+
+      bitmap.InitFromBool(boolmap);
+      // communicate bitmap
+      rabit::Allreduce<rabit::op::BitOR>(dmlc::BeginPtr(bitmap.data), bitmap.data.size());
+      const std::vector<bst_uint> &rowset = p_fmat->buffered_rowset();
+      // get the new position
+      const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
+      #pragma omp parallel for schedule(static)
+      for (bst_omp_uint i = 0; i < ndata; ++i) {
+        const bst_uint ridx = rowset[i];
+        const int nid = this->DecodePosition(ridx);
+        if (bitmap.Get(ridx)) {
+          CHECK(!tree[nid].is_leaf()) << "inconsistent reduce information";
+          if (tree[nid].default_left()) {
+            this->SetEncodePosition(ridx, tree[nid].cright());
+          } else {
+            this->SetEncodePosition(ridx, tree[nid].cleft());
+          }
+        }
+      }
+    }
+    // synchronize the best solution of each node
+    virtual void SyncBestSolution(const std::vector<int> &qexpand) {
+      std::vector<SplitEntry> vec;
+      for (size_t i = 0; i < qexpand.size(); ++i) {
+        const int nid = qexpand[i];
+        for (int tid = 0; tid < this->nthread; ++tid) {
+          this->snode[nid].best.Update(this->stemp[tid][nid].best);
+        }
+        vec.push_back(this->snode[nid].best);
+      }
+      // TODO(tqchen) lazy version
+      // communicate best solution
+      reducer.Allreduce(dmlc::BeginPtr(vec), vec.size());
+      // assign solution back
+      for (size_t i = 0; i < qexpand.size(); ++i) {
+        const int nid = qexpand[i];
+        this->snode[nid].best = vec[i];
+      }
+    }
+
+   private:
+    common::BitMap bitmap;
+    std::vector<int> boolmap;
+    rabit::Reducer<SplitEntry, SplitEntry::Reduce> reducer;
+  };
+  // we directly introduce pruner here
+  std::unique_ptr<TreeUpdater> pruner;
+  // training parameter
+  TrainParam param;
+  // pointer to the builder
+  Builder builder;
+};
+
+XGBOOST_REGISTER_TREE_UPDATER(ColMaker, "grow_colmaker")
+.describe("Grow tree with parallelization over columns.")
+.set_body([]() {
+    return new ColMaker<GradStats>();
+  });
+
+XGBOOST_REGISTER_TREE_UPDATER(DistColMaker, "distcol")
+.describe("Distributed column split version of tree maker.")
+.set_body([]() {
+    return new DistColMaker<GradStats>();
+  });
 }  // namespace tree
 }  // namespace xgboost
-#endif  // XGBOOST_TREE_UPDATER_COLMAKER_INL_HPP_
+