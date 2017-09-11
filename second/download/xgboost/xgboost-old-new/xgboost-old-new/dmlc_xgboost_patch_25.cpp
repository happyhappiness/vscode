@@ -1,64 +1,67 @@
 /*!
  * Copyright 2014 by Contributors
- * \file updater_basemaker-inl.hpp
+ * \file updater_basemaker-inl.h
  * \brief implement a common tree constructor
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_TREE_UPDATER_BASEMAKER_INL_HPP_
-#define XGBOOST_TREE_UPDATER_BASEMAKER_INL_HPP_
+#ifndef XGBOOST_TREE_UPDATER_BASEMAKER_INL_H_
+#define XGBOOST_TREE_UPDATER_BASEMAKER_INL_H_
+
+#include <xgboost/base.h>
+#include <xgboost/tree_updater.h>
 #include <vector>
 #include <algorithm>
 #include <string>
 #include <limits>
-#include "../sync/sync.h"
-#include "../utils/random.h"
-#include "../utils/quantile.h"
+#include <utility>
+#include "./param.h"
+#include "../common/sync.h"
+#include "../common/io.h"
+#include "../common/random.h"
+#include "../common/quantile.h"
 
 namespace xgboost {
 namespace tree {
 /*!
  * \brief base tree maker class that defines common operation
  *  needed in tree making
  */
-class BaseMaker: public IUpdater {
+class BaseMaker: public TreeUpdater {
  public:
-  // destructor
-  virtual ~BaseMaker(void) {}
-  // set training parameter
-  virtual void SetParam(const char *name, const char *val) {
-    param.SetParam(name, val);
+  void Init(const std::vector<std::pair<std::string, std::string> >& args) override {
+    param.Init(args);
   }
 
  protected:
   // helper to collect and query feature meta information
   struct FMetaHelper {
    public:
     /*! \brief find type of each feature, use column format */
-    inline void InitByCol(IFMatrix *p_fmat,
-                          const RegTree &tree) {
+    inline void InitByCol(DMatrix* p_fmat,
+                          const RegTree& tree) {
       fminmax.resize(tree.param.num_feature * 2);
       std::fill(fminmax.begin(), fminmax.end(),
                 -std::numeric_limits<bst_float>::max());
       // start accumulating statistics
-      utils::IIterator<ColBatch> *iter = p_fmat->ColIterator();
+      dmlc::DataIter<ColBatch>* iter = p_fmat->ColIterator();
       iter->BeforeFirst();
       while (iter->Next()) {
-        const ColBatch &batch = iter->Value();
+        const ColBatch& batch = iter->Value();
         for (bst_uint i = 0; i < batch.size; ++i) {
           const bst_uint fid = batch.col_index[i];
-          const ColBatch::Inst &c = batch[i];
+          const ColBatch::Inst& c = batch[i];
           if (c.length != 0) {
             fminmax[fid * 2 + 0] = std::max(-c[0].fvalue, fminmax[fid * 2 + 0]);
             fminmax[fid * 2 + 1] = std::max(c[c.length - 1].fvalue, fminmax[fid * 2 + 1]);
           }
         }
       }
-      rabit::Allreduce<rabit::op::Max>(BeginPtr(fminmax), fminmax.size());
+      rabit::Allreduce<rabit::op::Max>(dmlc::BeginPtr(fminmax), fminmax.size());
     }
     // get feature type, 0:empty 1:binary 2:real
     inline int Type(bst_uint fid) const {
-      utils::Assert(fid * 2 + 1 < fminmax.size(),
-                    "FeatHelper fid exceed query bound ");
+      CHECK_LT(fid * 2 + 1, fminmax.size())
+          << "FeatHelper fid exceed query bound ";
       bst_float a = fminmax[fid * 2];
       bst_float b = fminmax[fid * 2 + 1];
       if (a == -std::numeric_limits<bst_float>::max()) return 0;
@@ -79,12 +82,12 @@ class BaseMaker: public IUpdater {
         if (this->Type(fid) != 0) findex.push_back(fid);
       }
       unsigned n = static_cast<unsigned>(p * findex.size());
-      random::Shuffle(findex);
+      std::shuffle(findex.begin(), findex.end(), common::GlobalRandom());
       findex.resize(n);
       // sync the findex if it is subsample
       std::string s_cache;
-      utils::MemoryBufferStream fc(&s_cache);
-      utils::IStream &fs = fc;
+      common::MemoryBufferStream fc(&s_cache);
+      dmlc::Stream& fs = fc;
       if (rabit::GetRank() == 0) {
         fs.Write(findex);
       }
@@ -113,7 +116,7 @@ class BaseMaker: public IUpdater {
     return n.cdefault();
   }
   /*! \brief get number of omp thread in current context */
-  inline static int get_nthread(void) {
+  inline static int get_nthread() {
     int nthread;
     #pragma omp parallel
     {
@@ -124,11 +127,11 @@ class BaseMaker: public IUpdater {
   //  ------class member helpers---------
   /*! \brief initialize temp data structure */
   inline void InitData(const std::vector<bst_gpair> &gpair,
-                       const IFMatrix &fmat,
-                       const std::vector<unsigned> &root_index,
+                       const DMatrix &fmat,
                        const RegTree &tree) {
-    utils::Assert(tree.param.num_nodes == tree.param.num_roots,
-                  "TreeMaker: can only grow new tree");
+    CHECK_EQ(tree.param.num_nodes, tree.param.num_roots)
+        << "TreeMaker: can only grow new tree";
+    const std::vector<unsigned> &root_index =  fmat.info().root_index;
     {
       // setup position
       position.resize(gpair.size());
@@ -137,8 +140,8 @@ class BaseMaker: public IUpdater {
       } else {
         for (size_t i = 0; i < position.size(); ++i) {
           position[i] = root_index[i];
-          utils::Assert(root_index[i] < (unsigned)tree.param.num_roots,
-                        "root index exceed setting");
+          CHECK_LT(root_index[i], (unsigned)tree.param.num_roots)
+              << "root index exceed setting";
         }
       }
       // mark delete for the deleted datas
@@ -147,9 +150,11 @@ class BaseMaker: public IUpdater {
       }
       // mark subsample
       if (param.subsample < 1.0f) {
+        std::bernoulli_distribution coin_flip(param.subsample);
+        auto& rnd = common::GlobalRandom();
         for (size_t i = 0; i < position.size(); ++i) {
           if (gpair[i].hess < 0.0f) continue;
-          if (random::SampleBinary(param.subsample) == 0) position[i] = ~position[i];
+          if (!coin_flip(rnd)) position[i] = ~position[i];
         }
       }
     }
@@ -197,7 +202,8 @@ class BaseMaker: public IUpdater {
    * \param tree the regression tree structure
    */
   inline void ResetPositionCol(const std::vector<int> &nodes,
-                               IFMatrix *p_fmat, const RegTree &tree) {
+                               DMatrix *p_fmat,
+                               const RegTree &tree) {
     // set the positions in the nondefault
     this->SetNonDefaultPositionCol(nodes, p_fmat, tree);
     // set rest of instances to default position
@@ -234,7 +240,8 @@ class BaseMaker: public IUpdater {
    * \param tree the regression tree structure
    */
   virtual void SetNonDefaultPositionCol(const std::vector<int> &nodes,
-                                        IFMatrix *p_fmat, const RegTree &tree) {
+                                        DMatrix *p_fmat,
+                                        const RegTree &tree) {
     // step 1, classify the non-default data into right places
     std::vector<unsigned> fsplits;
     for (size_t i = 0; i < nodes.size(); ++i) {
@@ -246,7 +253,7 @@ class BaseMaker: public IUpdater {
     std::sort(fsplits.begin(), fsplits.end());
     fsplits.resize(std::unique(fsplits.begin(), fsplits.end()) - fsplits.begin());
 
-    utils::IIterator<ColBatch> *iter = p_fmat->ColIterator(fsplits);
+    dmlc::DataIter<ColBatch> *iter = p_fmat->ColIterator(fsplits);
     while (iter->Next()) {
       const ColBatch &batch = iter->Value();
       for (size_t i = 0; i < batch.size; ++i) {
@@ -273,12 +280,12 @@ class BaseMaker: public IUpdater {
   /*! \brief helper function to get statistics from a tree */
   template<typename TStats>
   inline void GetNodeStats(const std::vector<bst_gpair> &gpair,
-                           const IFMatrix &fmat,
+                           const DMatrix &fmat,
                            const RegTree &tree,
-                           const BoosterInfo &info,
                            std::vector< std::vector<TStats> > *p_thread_temp,
                            std::vector<TStats> *p_node_stats) {
     std::vector< std::vector<TStats> > &thread_temp = *p_thread_temp;
+    const MetaInfo &info = fmat.info();
     thread_temp.resize(this->get_nthread());
     p_node_stats->resize(tree.param.num_nodes);
     #pragma omp parallel
@@ -323,7 +330,7 @@ class BaseMaker: public IUpdater {
     /*! \brief current size of sketch */
     double next_goal;
     // pointer to the sketch to put things in
-    utils::WXQuantileSketch<bst_float, bst_float> *sketch;
+    common::WXQuantileSketch<bst_float, bst_float> *sketch;
     // initialize the space
     inline void Init(unsigned max_size) {
       next_goal = -1.0f;
@@ -351,13 +358,13 @@ class BaseMaker: public IUpdater {
               last_fvalue > sketch->temp.data[sketch->temp.size-1].value) {
             // push to sketch
             sketch->temp.data[sketch->temp.size] =
-                utils::WXQuantileSketch<bst_float, bst_float>::
+                common::WXQuantileSketch<bst_float, bst_float>::
                 Entry(static_cast<bst_float>(rmin),
                       static_cast<bst_float>(rmax),
                       static_cast<bst_float>(wmin), last_fvalue);
-            utils::Assert(sketch->temp.size < max_size,
-                          "invalid maximum size max_size=%u, stemp.size=%lu\n",
-                          max_size, sketch->temp.size);
+            CHECK_LT(sketch->temp.size, max_size)
+                << "invalid maximum size max_size=" << max_size
+                << ", stemp.size" << sketch->temp.size;
             ++sketch->temp.size;
           }
           if (sketch->temp.size == max_size) {
@@ -382,12 +389,12 @@ class BaseMaker: public IUpdater {
     inline void Finalize(unsigned max_size) {
       double rmax = rmin + wmin;
       if (sketch->temp.size == 0 || last_fvalue > sketch->temp.data[sketch->temp.size-1].value) {
-        utils::Assert(sketch->temp.size <= max_size,
-                      "Finalize: invalid maximum size, max_size=%u, stemp.size=%lu",
-                      sketch->temp.size, max_size);
+        CHECK_LE(sketch->temp.size, max_size)
+            << "Finalize: invalid maximum size, max_size=" << max_size
+            << ", stemp.size=" << sketch->temp.size;
         // push to sketch
         sketch->temp.data[sketch->temp.size] =
-            utils::WXQuantileSketch<bst_float, bst_float>::
+            common::WXQuantileSketch<bst_float, bst_float>::
             Entry(static_cast<bst_float>(rmin),
                   static_cast<bst_float>(rmax),
                   static_cast<bst_float>(wmin), last_fvalue);
@@ -424,4 +431,4 @@ class BaseMaker: public IUpdater {
 };
 }  // namespace tree
 }  // namespace xgboost
-#endif  // XGBOOST_TREE_UPDATER_BASEMAKER_INL_HPP_
+#endif  // XGBOOST_TREE_UPDATER_BASEMAKER_INL_H_