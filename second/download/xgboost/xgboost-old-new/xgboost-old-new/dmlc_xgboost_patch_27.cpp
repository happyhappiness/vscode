@@ -1,57 +1,56 @@
 /*!
  * Copyright 2014 by Contributors
- * \file updater_skmaker-inl.hpp
+ * \file updater_skmaker.cc
  * \brief use approximation sketch to construct a tree,
           a refresh is needed to make the statistics exactly correct
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_TREE_UPDATER_SKMAKER_INL_HPP_
-#define XGBOOST_TREE_UPDATER_SKMAKER_INL_HPP_
 
+#include <xgboost/base.h>
+#include <xgboost/tree_updater.h>
 #include <vector>
 #include <algorithm>
-#include "../sync/sync.h"
-#include "../utils/quantile.h"
-#include "./updater_basemaker-inl.hpp"
+#include "../common/sync.h"
+#include "../common/quantile.h"
+#include "../common/group_data.h"
+#include "./updater_basemaker-inl.h"
 
 namespace xgboost {
 namespace tree {
+
 class SketchMaker: public BaseMaker {
  public:
-  virtual ~SketchMaker(void) {}
-  virtual void Update(const std::vector<bst_gpair> &gpair,
-                      IFMatrix *p_fmat,
-                      const BoosterInfo &info,
-                      const std::vector<RegTree*> &trees) {
+  void Update(const std::vector<bst_gpair> &gpair,
+              DMatrix *p_fmat,
+              const std::vector<RegTree*> &trees) override {
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
   inline void Update(const std::vector<bst_gpair> &gpair,
-                      IFMatrix *p_fmat,
-                      const BoosterInfo &info,
-                      RegTree *p_tree) {
-    this->InitData(gpair, *p_fmat, info.root_index, *p_tree);
+                     DMatrix *p_fmat,
+                     RegTree *p_tree) {
+    this->InitData(gpair, *p_fmat, *p_tree);
     for (int depth = 0; depth < param.max_depth; ++depth) {
-      this->GetNodeStats(gpair, *p_fmat, *p_tree, info,
+      this->GetNodeStats(gpair, *p_fmat, *p_tree,
                          &thread_stats, &node_stats);
-      this->BuildSketch(gpair, p_fmat, info, *p_tree);
+      this->BuildSketch(gpair, p_fmat, *p_tree);
       this->SyncNodeStats();
-      this->FindSplit(depth, gpair, p_fmat, info, p_tree);
+      this->FindSplit(depth, gpair, p_fmat, p_tree);
       this->ResetPositionCol(qexpand, p_fmat, *p_tree);
       this->UpdateQueueExpand(*p_tree);
       // if nothing left to be expand, break
       if (qexpand.size() == 0) break;
     }
     if (qexpand.size() != 0) {
-      this->GetNodeStats(gpair, *p_fmat, *p_tree, info,
+      this->GetNodeStats(gpair, *p_fmat, *p_tree,
                          &thread_stats, &node_stats);
       this->SyncNodeStats();
     }
@@ -68,11 +67,11 @@ class SketchMaker: public BaseMaker {
     // set left leaves
     for (size_t i = 0; i < qexpand.size(); ++i) {
       const int nid = qexpand[i];
-      (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.learning_rate);
+      (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.eta);
     }
   }
   // define the sketch we want to use
-  typedef utils::WXQuantileSketch<bst_float, bst_float> WXQSketch;
+  typedef common::WXQuantileSketch<bst_float, bst_float> WXQSketch;
 
  private:
   // statistics needed in the gradient calculation
@@ -94,7 +93,7 @@ class SketchMaker: public BaseMaker {
     }
     // accumulate statistics
     inline void Add(const std::vector<bst_gpair> &gpair,
-                    const BoosterInfo &info,
+                    const MetaInfo &info,
                     bst_uint ridx) {
       const bst_gpair &b = gpair[ridx];
       if (b.grad >= 0.0f) {
@@ -133,9 +132,9 @@ class SketchMaker: public BaseMaker {
     }
   };
   inline void BuildSketch(const std::vector<bst_gpair> &gpair,
-                          IFMatrix *p_fmat,
-                          const BoosterInfo &info,
+                          DMatrix *p_fmat,
                           const RegTree &tree) {
+    const MetaInfo& info = p_fmat->info();
     sketchs.resize(this->qexpand.size() * tree.param.num_feature * 3);
     for (size_t i = 0; i < sketchs.size(); ++i) {
       sketchs[i].Init(info.num_row, this->param.sketch_eps);
@@ -144,7 +143,7 @@ class SketchMaker: public BaseMaker {
     // number of rows in
     const size_t nrows = p_fmat->buffered_rowset().size();
     // start accumulating statistics
-    utils::IIterator<ColBatch> *iter = p_fmat->ColIterator();
+    dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator();
     iter->BeforeFirst();
     while (iter->Next()) {
       const ColBatch &batch = iter->Value();
@@ -164,13 +163,13 @@ class SketchMaker: public BaseMaker {
     // synchronize sketch
     summary_array.resize(sketchs.size());
     for (size_t i = 0; i < sketchs.size(); ++i) {
-      utils::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
+      common::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
       sketchs[i].GetSummary(&out);
       summary_array[i].Reserve(max_size);
       summary_array[i].SetPrune(out, max_size);
     }
     size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
-    sketch_reducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size());
+    sketch_reducer.Allreduce(dmlc::BeginPtr(summary_array), nbytes, summary_array.size());
   }
   // update sketch information in column fid
   inline void UpdateSketchCol(const std::vector<bst_gpair> &gpair,
@@ -256,20 +255,19 @@ class SketchMaker: public BaseMaker {
     }
   }
   inline void SyncNodeStats(void) {
-    utils::Assert(qexpand.size() != 0, "qexpand must not be empty");
+    CHECK_NE(qexpand.size(), 0);
     std::vector<SKStats> tmp(qexpand.size());
     for (size_t i = 0; i < qexpand.size(); ++i) {
       tmp[i] = node_stats[qexpand[i]];
     }
-    stats_reducer.Allreduce(BeginPtr(tmp), tmp.size());
+    stats_reducer.Allreduce(dmlc::BeginPtr(tmp), tmp.size());
     for (size_t i = 0; i < qexpand.size(); ++i) {
       node_stats[qexpand[i]] = tmp[i];
     }
   }
   inline void FindSplit(int depth,
                         const std::vector<bst_gpair> &gpair,
-                        IFMatrix *p_fmat,
-                        const BoosterInfo &info,
+                        DMatrix *p_fmat,
                         RegTree *p_tree) {
     const bst_uint num_feature = p_tree->param.num_feature;
     // get the best split condition for each node
@@ -278,8 +276,7 @@ class SketchMaker: public BaseMaker {
     #pragma omp parallel for schedule(dynamic, 1)
     for (bst_omp_uint wid = 0; wid < nexpand; ++wid) {
       const int nid = qexpand[wid];
-      utils::Assert(node2workindex[nid] == static_cast<int>(wid),
-                    "node2workindex inconsistent");
+      CHECK_EQ(node2workindex[nid], static_cast<int>(wid));
       SplitEntry &best = sol[wid];
       for (bst_uint fid = 0; fid < num_feature; ++fid) {
         unsigned base = (wid * p_tree->param.num_feature + fid) * 3;
@@ -305,7 +302,7 @@ class SketchMaker: public BaseMaker {
         (*p_tree)[(*p_tree)[nid].cleft()].set_leaf(0.0f, 0);
         (*p_tree)[(*p_tree)[nid].cright()].set_leaf(0.0f, 0);
       } else {
-        (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.learning_rate);
+        (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.eta);
       }
     }
   }
@@ -380,9 +377,9 @@ class SketchMaker: public BaseMaker {
 
   // thread temp data
   // used to hold temporal sketch
-  std::vector< std::vector<SketchEntry> > thread_sketch;
+  std::vector<std::vector<SketchEntry> > thread_sketch;
   // used to hold statistics
-  std::vector< std::vector<SKStats> > thread_stats;
+  std::vector<std::vector<SKStats> > thread_stats;
   // node statistics
   std::vector<SKStats> node_stats;
   // summary array
@@ -392,8 +389,14 @@ class SketchMaker: public BaseMaker {
   // reducer for summary
   rabit::SerializeReducer<WXQSketch::SummaryContainer> sketch_reducer;
   // per node, per feature sketch
-  std::vector< utils::WXQuantileSketch<bst_float, bst_float> > sketchs;
+  std::vector<common::WXQuantileSketch<bst_float, bst_float> > sketchs;
 };
+
+XGBOOST_REGISTER_TREE_UPDATER(SketchMaker, "grow_skmaker")
+.describe("Approximate sketching maker.")
+.set_body([]() {
+    return new SketchMaker();
+  });
 }  // namespace tree
 }  // namespace xgboost
-#endif  // XGBOOST_TREE_UPDATER_SKMAKER_INL_HPP_
+