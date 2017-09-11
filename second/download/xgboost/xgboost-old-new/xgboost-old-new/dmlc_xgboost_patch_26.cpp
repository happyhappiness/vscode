@@ -1,38 +1,35 @@
 /*!
  * Copyright 2014 by Contributors
- * \file updater_histmaker-inl.hpp
+ * \file updater_histmaker.cc
  * \brief use histogram counting to construct a tree
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_TREE_UPDATER_HISTMAKER_INL_HPP_
-#define XGBOOST_TREE_UPDATER_HISTMAKER_INL_HPP_
-
+#include <xgboost/base.h>
+#include <xgboost/tree_updater.h>
 #include <vector>
 #include <algorithm>
-#include "../sync/sync.h"
-#include "../utils/quantile.h"
-#include "../utils/group_data.h"
-#include "./updater_basemaker-inl.hpp"
+#include "../common/sync.h"
+#include "../common/quantile.h"
+#include "../common/group_data.h"
+#include "./updater_basemaker-inl.h"
 
 namespace xgboost {
 namespace tree {
 template<typename TStats>
 class HistMaker: public BaseMaker {
  public:
-  virtual ~HistMaker(void) {}
-  virtual void Update(const std::vector<bst_gpair> &gpair,
-                      IFMatrix *p_fmat,
-                      const BoosterInfo &info,
-                      const std::vector<RegTree*> &trees) {
-    TStats::CheckInfo(info);
+  void Update(const std::vector<bst_gpair> &gpair,
+              DMatrix *p_fmat,
+              const std::vector<RegTree*> &trees) override {
+    TStats::CheckInfo(p_fmat->info());
     // rescale learning rate according to size of trees
-    float lr = param.learning_rate;
-    param.learning_rate = lr / trees.size();
+    float lr = param.eta;
+    param.eta = lr / trees.size();
     // build tree
     for (size_t i = 0; i < trees.size(); ++i) {
-      this->Update(gpair, p_fmat, info, trees[i]);
+      this->Update(gpair, p_fmat, trees[i]);
     }
-    param.learning_rate = lr;
+    param.eta = lr;
   }
 
  protected:
@@ -45,19 +42,18 @@ class HistMaker: public BaseMaker {
     /*! \brief size of histogram */
     unsigned size;
     // default constructor
-    HistUnit(void) {}
+    HistUnit() {}
     // constructor
     HistUnit(const bst_float *cut, TStats *data, unsigned size)
         : cut(cut), data(data), size(size) {}
     /*! \brief add a histogram to data */
     inline void Add(bst_float fv,
                     const std::vector<bst_gpair> &gpair,
-                    const BoosterInfo &info,
+                    const MetaInfo &info,
                     const bst_uint ridx) {
       unsigned i = std::upper_bound(cut, cut + size, fv) - cut;
-      utils::Assert(size != 0, "try insert into size=0");
-      utils::Assert(i < size,
-                    "maximum value must be in cut, fv = %g, cutmax=%g", fv, cut[size-1]);
+      CHECK_NE(size, 0) << "try insert into size=0";
+      CHECK_LT(i, size);
       data[i].Add(gpair, info, ridx);
     }
   };
@@ -92,13 +88,13 @@ class HistMaker: public BaseMaker {
         for (size_t i = 0; i < hset[tid].data.size(); ++i) {
           hset[tid].data[i].Clear();
         }
-        hset[tid].rptr = BeginPtr(rptr);
-        hset[tid].cut = BeginPtr(cut);
+        hset[tid].rptr = dmlc::BeginPtr(rptr);
+        hset[tid].cut = dmlc::BeginPtr(cut);
         hset[tid].data.resize(cut.size(), TStats(param));
       }
     }
     // aggregate all statistics to hset[0]
-    inline void Aggregate(void) {
+    inline void Aggregate() {
       bst_omp_uint nsize = static_cast<bst_omp_uint>(cut.size());
       #pragma omp parallel for schedule(static)
       for (bst_omp_uint i = 0; i < nsize; ++i) {
@@ -108,11 +104,11 @@ class HistMaker: public BaseMaker {
       }
     }
     /*! \brief clear the workspace */
-    inline void Clear(void) {
+    inline void Clear() {
       cut.clear(); rptr.resize(1); rptr[0] = 0;
     }
     /*! \brief total size */
-    inline size_t Size(void) const {
+    inline size_t Size() const {
       return rptr.size() - 1;
     }
   };
@@ -124,18 +120,17 @@ class HistMaker: public BaseMaker {
   std::vector<bst_uint> fwork_set;
   // update function implementation
   virtual void Update(const std::vector<bst_gpair> &gpair,
-                      IFMatrix *p_fmat,
-                      const BoosterInfo &info,
+                      DMatrix *p_fmat,
                       RegTree *p_tree) {
-    this->InitData(gpair, *p_fmat, info.root_index, *p_tree);
+    this->InitData(gpair, *p_fmat, *p_tree);
     this->InitWorkSet(p_fmat, *p_tree, &fwork_set);
     for (int depth = 0; depth < param.max_depth; ++depth) {
       // reset and propose candidate split
-      this->ResetPosAndPropose(gpair, p_fmat, info, fwork_set, *p_tree);
+      this->ResetPosAndPropose(gpair, p_fmat, fwork_set, *p_tree);
       // create histogram
-      this->CreateHist(gpair, p_fmat, info, fwork_set, *p_tree);
+      this->CreateHist(gpair, p_fmat, fwork_set, *p_tree);
       // find split based on histogram statistics
-      this->FindSplit(depth, gpair, p_fmat, info, fwork_set, p_tree);
+      this->FindSplit(depth, gpair, p_fmat, fwork_set, p_tree);
       // reset position after split
       this->ResetPositionAfterSplit(p_fmat, *p_tree);
       this->UpdateQueueExpand(*p_tree);
@@ -144,19 +139,18 @@ class HistMaker: public BaseMaker {
     }
     for (size_t i = 0; i < qexpand.size(); ++i) {
       const int nid = qexpand[i];
-      (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.learning_rate);
+      (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.eta);
     }
   }
   // this function does two jobs
   // (1) reset the position in array position, to be the latest leaf id
   // (2) propose a set of candidate cuts and set wspace.rptr wspace.cut correctly
   virtual void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
-                                  IFMatrix *p_fmat,
-                                  const BoosterInfo &info,
+                                  DMatrix *p_fmat,
                                   const std::vector <bst_uint> &fset,
                                   const RegTree &tree) = 0;
   // initialize the current working set of features in this round
-  virtual void InitWorkSet(IFMatrix *p_fmat,
+  virtual void InitWorkSet(DMatrix *p_fmat,
                            const RegTree &tree,
                            std::vector<bst_uint> *p_fset) {
     p_fset->resize(tree.param.num_feature);
@@ -165,12 +159,11 @@ class HistMaker: public BaseMaker {
     }
   }
   // reset position after split, this is not a must, depending on implementation
-  virtual void ResetPositionAfterSplit(IFMatrix *p_fmat,
+  virtual void ResetPositionAfterSplit(DMatrix *p_fmat,
                                        const RegTree &tree) {
   }
   virtual void CreateHist(const std::vector<bst_gpair> &gpair,
-                          IFMatrix *p_fmat,
-                          const BoosterInfo &info,
+                          DMatrix *p_fmat,
                           const std::vector <bst_uint> &fset,
                           const RegTree &tree)  = 0;
 
@@ -212,8 +205,7 @@ class HistMaker: public BaseMaker {
   }
   inline void FindSplit(int depth,
                         const std::vector<bst_gpair> &gpair,
-                        IFMatrix *p_fmat,
-                        const BoosterInfo &info,
+                        DMatrix *p_fmat,
                         const std::vector <bst_uint> &fset,
                         RegTree *p_tree) {
     const size_t num_feature = fset.size();
@@ -224,8 +216,7 @@ class HistMaker: public BaseMaker {
     #pragma omp parallel for schedule(dynamic, 1)
     for (bst_omp_uint wid = 0; wid < nexpand; ++wid) {
       const int nid = qexpand[wid];
-      utils::Assert(node2workindex[nid] == static_cast<int>(wid),
-                    "node2workindex inconsistent");
+      CHECK_EQ(node2workindex[nid], static_cast<int>(wid));
       SplitEntry &best = sol[wid];
       TStats &node_sum = wspace.hset[0][num_feature + wid * (num_feature + 1)].data[0];
       for (size_t i = 0; i < fset.size(); ++i) {
@@ -255,7 +246,7 @@ class HistMaker: public BaseMaker {
         this->SetStats(p_tree, (*p_tree)[nid].cleft(), left_sum[wid]);
         this->SetStats(p_tree, (*p_tree)[nid].cright(), right_sum);
       } else {
-        (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.learning_rate);
+        (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.eta);
       }
     }
   }
@@ -279,10 +270,10 @@ class CQHistMaker: public HistMaker<TStats> {
      */
     inline void Add(bst_float fv,
                     const std::vector<bst_gpair> &gpair,
-                    const BoosterInfo &info,
+                    const MetaInfo &info,
                     const bst_uint ridx) {
       while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
-      utils::Assert(istart != hist.size, "the bound variable must be max");
+      CHECK_NE(istart, hist.size);
       hist.data[istart].Add(gpair, info, ridx);
     }
     /*!
@@ -292,25 +283,25 @@ class CQHistMaker: public HistMaker<TStats> {
     inline void Add(bst_float fv,
                     bst_gpair gstats) {
       while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
-      utils::Assert(istart != hist.size, "the bound variable must be max");
+      CHECK_NE(istart, hist.size);
       hist.data[istart].Add(gstats);
     }
   };
   // sketch type used for this
-  typedef utils::WXQuantileSketch<bst_float, bst_float> WXQSketch;
+  typedef common::WXQuantileSketch<bst_float, bst_float> WXQSketch;
   // initialize the work set of tree
-  virtual void InitWorkSet(IFMatrix *p_fmat,
-                           const RegTree &tree,
-                           std::vector<bst_uint> *p_fset) {
+  void InitWorkSet(DMatrix *p_fmat,
+                   const RegTree &tree,
+                   std::vector<bst_uint> *p_fset) override {
     feat_helper.InitByCol(p_fmat, tree);
     feat_helper.SampleCol(this->param.colsample_bytree, p_fset);
   }
   // code to create histogram
-  virtual void CreateHist(const std::vector<bst_gpair> &gpair,
-                          IFMatrix *p_fmat,
-                          const BoosterInfo &info,
-                          const std::vector<bst_uint> &fset,
-                          const RegTree &tree) {
+  void CreateHist(const std::vector<bst_gpair> &gpair,
+                  DMatrix *p_fmat,
+                  const std::vector<bst_uint> &fset,
+                  const RegTree &tree) override {
+    const MetaInfo &info = p_fmat->info();
     // fill in reverse map
     feat2workindex.resize(tree.param.num_feature);
     std::fill(feat2workindex.begin(), feat2workindex.end(), -1);
@@ -327,7 +318,7 @@ class CQHistMaker: public HistMaker<TStats> {
     {
       thread_hist.resize(this->get_nthread());
       // start accumulating statistics
-      utils::IIterator<ColBatch> *iter = p_fmat->ColIterator(fset);
+      dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator(fset);
       iter->BeforeFirst();
       while (iter->Next()) {
         const ColBatch &batch = iter->Value();
@@ -353,21 +344,22 @@ class CQHistMaker: public HistMaker<TStats> {
     // sync the histogram
     // if it is C++11, use lazy evaluation for Allreduce
 #if __cplusplus >= 201103L
-    this->histred.Allreduce(BeginPtr(this->wspace.hset[0].data),
+    this->histred.Allreduce(dmlc::BeginPtr(this->wspace.hset[0].data),
                             this->wspace.hset[0].data.size(), lazy_get_hist);
 #else
-    this->histred.Allreduce(BeginPtr(this->wspace.hset[0].data), this->wspace.hset[0].data.size());
+    this->histred.Allreduce(dmlc::BeginPtr(this->wspace.hset[0].data),
+                            this->wspace.hset[0].data.size());
 #endif
   }
-  virtual void ResetPositionAfterSplit(IFMatrix *p_fmat,
-                                       const RegTree &tree) {
+  void ResetPositionAfterSplit(DMatrix *p_fmat,
+                                       const RegTree &tree) override {
     this->ResetPositionCol(this->qexpand, p_fmat, tree);
   }
-  virtual void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
-                                  IFMatrix *p_fmat,
-                                  const BoosterInfo &info,
-                                  const std::vector<bst_uint> &fset,
-                                  const RegTree &tree) {
+  void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
+                          DMatrix *p_fmat,
+                          const std::vector<bst_uint> &fset,
+                          const RegTree &tree) override {
+    const MetaInfo &info = p_fmat->info();
     // fill in reverse map
     feat2workindex.resize(tree.param.num_feature);
     std::fill(feat2workindex.begin(), feat2workindex.end(), -1);
@@ -380,7 +372,7 @@ class CQHistMaker: public HistMaker<TStats> {
         feat2workindex[fset[i]] = -2;
       }
     }
-    this->GetNodeStats(gpair, *p_fmat, tree, info,
+    this->GetNodeStats(gpair, *p_fmat, tree,
                        &thread_stats, &node_stats);
     sketchs.resize(this->qexpand.size() * freal_set.size());
     for (size_t i = 0; i < sketchs.size(); ++i) {
@@ -403,7 +395,7 @@ class CQHistMaker: public HistMaker<TStats> {
       // number of rows in
       const size_t nrows = p_fmat->buffered_rowset().size();
       // start accumulating statistics
-      utils::IIterator<ColBatch> *iter = p_fmat->ColIterator(freal_set);
+      dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator(freal_set);
       iter->BeforeFirst();
       while (iter->Next()) {
         const ColBatch &batch = iter->Value();
@@ -422,18 +414,19 @@ class CQHistMaker: public HistMaker<TStats> {
         }
       }
       for (size_t i = 0; i < sketchs.size(); ++i) {
-        utils::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
+        common::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
         sketchs[i].GetSummary(&out);
         summary_array[i].SetPrune(out, max_size);
       }
-      utils::Assert(summary_array.size() == sketchs.size(), "shape mismatch");
+      CHECK_EQ(summary_array.size(), sketchs.size());
     };
     if (summary_array.size() != 0) {
       size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
 #if __cplusplus >= 201103L
-      sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size(), lazy_get_summary);
+      sreducer.Allreduce(dmlc::BeginPtr(summary_array),
+                         nbytes, summary_array.size(), lazy_get_summary);
 #else
-      sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size());
+      sreducer.Allreduce(dmlc::BeginPtr(summary_array), nbytes, summary_array.size());
 #endif
     }
     // now we get the final result of sketch, setup the cut
@@ -460,7 +453,7 @@ class CQHistMaker: public HistMaker<TStats> {
           }
           this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
         } else {
-          utils::Assert(offset == -2, "BUG in mark");
+          CHECK_EQ(offset, -2);
           bst_float cpt = feat_helper.MaxValue(fset[i]);
           this->wspace.cut.push_back(cpt + fabs(cpt) + rt_eps);
           this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
@@ -470,15 +463,14 @@ class CQHistMaker: public HistMaker<TStats> {
       this->wspace.cut.push_back(0.0f);
       this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
     }
-    utils::Assert(this->wspace.rptr.size() ==
-                  (fset.size() + 1) * this->qexpand.size() + 1,
-                  "cut space inconsistent");
+    CHECK_EQ(this->wspace.rptr.size(),
+             (fset.size() + 1) * this->qexpand.size() + 1);
   }
 
  private:
   inline void UpdateHistCol(const std::vector<bst_gpair> &gpair,
                             const ColBatch::Inst &c,
-                            const BoosterInfo &info,
+                            const MetaInfo &info,
                             const RegTree &tree,
                             const std::vector<bst_uint> &fset,
                             bst_uint fid_offset,
@@ -623,43 +615,44 @@ class CQHistMaker: public HistMaker<TStats> {
   // set of index from fset that are real
   std::vector<bst_uint> freal_set;
   // thread temp data
-  std::vector< std::vector<BaseMaker::SketchEntry> > thread_sketch;
+  std::vector<std::vector<BaseMaker::SketchEntry> > thread_sketch;
   // used to hold statistics
-  std::vector< std::vector<TStats> > thread_stats;
+  std::vector<std::vector<TStats> > thread_stats;
   // used to hold start pointer
-  std::vector< std::vector<HistEntry> > thread_hist;
+  std::vector<std::vector<HistEntry> > thread_hist;
   // node statistics
   std::vector<TStats> node_stats;
   // summary array
   std::vector<WXQSketch::SummaryContainer> summary_array;
   // reducer for summary
   rabit::SerializeReducer<WXQSketch::SummaryContainer> sreducer;
   // per node, per feature sketch
-  std::vector< utils::WXQuantileSketch<bst_float, bst_float> > sketchs;
+  std::vector<common::WXQuantileSketch<bst_float, bst_float> > sketchs;
 };
 
 template<typename TStats>
 class QuantileHistMaker: public HistMaker<TStats> {
  protected:
-  typedef utils::WXQuantileSketch<bst_float, bst_float> WXQSketch;
-  virtual void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
-                                  IFMatrix *p_fmat,
-                                  const BoosterInfo &info,
-                                  const std::vector <bst_uint> &fset,
-                                  const RegTree &tree) {
+  typedef common::WXQuantileSketch<bst_float, bst_float> WXQSketch;
+  void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
+                          DMatrix *p_fmat,
+                          const std::vector <bst_uint> &fset,
+                          const RegTree &tree) override {
+    const MetaInfo &info = p_fmat->info();
     // initialize the data structure
     int nthread = BaseMaker::get_nthread();
     sketchs.resize(this->qexpand.size() * tree.param.num_feature);
     for (size_t i = 0; i < sketchs.size(); ++i) {
       sketchs[i].Init(info.num_row, this->param.sketch_eps);
     }
     // start accumulating statistics
-    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
+    dmlc::DataIter<RowBatch> *iter = p_fmat->RowIterator();
     iter->BeforeFirst();
     while (iter->Next()) {
       const RowBatch &batch = iter->Value();
       // parallel convert to column major format
-      utils::ParallelGroupBuilder<SparseBatch::Entry> builder(&col_ptr, &col_data, &thread_col_ptr);
+      common::ParallelGroupBuilder<SparseBatch::Entry>
+          builder(&col_ptr, &col_data, &thread_col_ptr);
       builder.InitBudget(tree.param.num_feature, nthread);
 
       const bst_omp_uint nbatch = static_cast<bst_omp_uint>(batch.size);
@@ -711,14 +704,14 @@ class QuantileHistMaker: public HistMaker<TStats> {
     // synchronize sketch
     summary_array.resize(sketchs.size());
     for (size_t i = 0; i < sketchs.size(); ++i) {
-      utils::WQuantileSketch<bst_float, bst_float>::SummaryContainer out;
+      common::WQuantileSketch<bst_float, bst_float>::SummaryContainer out;
       sketchs[i].GetSummary(&out);
       summary_array[i].Reserve(max_size);
       summary_array[i].SetPrune(out, max_size);
     }
 
     size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
-    sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size());
+    sreducer.Allreduce(dmlc::BeginPtr(summary_array), nbytes, summary_array.size());
     // now we get the final result of sketch, setup the cut
     this->wspace.cut.clear();
     this->wspace.rptr.clear();
@@ -745,9 +738,8 @@ class QuantileHistMaker: public HistMaker<TStats> {
       this->wspace.cut.push_back(0.0f);
       this->wspace.rptr.push_back(this->wspace.cut.size());
     }
-    utils::Assert(this->wspace.rptr.size() ==
-                  (tree.param.num_feature + 1) * this->qexpand.size() + 1,
-                  "cut space inconsistent");
+    CHECK_EQ(this->wspace.rptr.size(),
+             (tree.param.num_feature + 1) * this->qexpand.size() + 1);
   }
 
  private:
@@ -759,11 +751,15 @@ class QuantileHistMaker: public HistMaker<TStats> {
   std::vector<size_t> col_ptr;
   // local storage of column data
   std::vector<SparseBatch::Entry> col_data;
-  std::vector< std::vector<size_t> > thread_col_ptr;
+  std::vector<std::vector<size_t> > thread_col_ptr;
   // per node, per feature sketch
-  std::vector< utils::WQuantileSketch<bst_float, bst_float> > sketchs;
+  std::vector<common::WQuantileSketch<bst_float, bst_float> > sketchs;
 };
 
+XGBOOST_REGISTER_TREE_UPDATER(HistMaker, "grow_histmaker")
+.describe("Tree constructor that uses approximate histogram construction.")
+.set_body([]() {
+    return new CQHistMaker<GradStats>();
+  });
 }  // namespace tree
 }  // namespace xgboost
-#endif  // XGBOOST_TREE_UPDATER_HISTMAKER_INL_HPP_