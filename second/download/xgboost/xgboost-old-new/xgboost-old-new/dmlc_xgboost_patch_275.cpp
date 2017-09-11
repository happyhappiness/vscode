@@ -1,13 +1,20 @@
 // implementations in ctypes
+#define _CRT_SECURE_NO_WARNINGS
+#define _CRT_SECURE_NO_DEPRECATE
 #include <cstdio>
 #include <vector>
 #include <string>
 #include <cstring>
 #include <algorithm>
+// include all std functions
+using namespace std;
+
 #include "./xgboost_wrapper.h"
 #include "../src/data.h"
 #include "../src/learner/learner-inl.hpp"
 #include "../src/io/io.h"
+#include "../src/utils/utils.h"
+#include "../src/utils/matrix_csr.h"
 #include "../src/io/simple_dmatrix-inl.hpp"
 
 using namespace xgboost;
@@ -16,18 +23,18 @@ using namespace xgboost::io;
 namespace xgboost {
 namespace wrapper {
 // booster wrapper class
-class Booster: public learner::BoostLearner<FMatrixS> {
+class Booster: public learner::BoostLearner {
  public:
   explicit Booster(const std::vector<DataMatrix*>& mats) {
     this->silent = 1;
     this->init_model = false;
     this->SetCacheData(mats);
   }
-  const float *Pred(const DataMatrix &dmat, int output_margin, bst_ulong *len) {
+  inline const float *Pred(const DataMatrix &dmat, int output_margin, unsigned ntree_limit, bst_ulong *len) {
     this->CheckInitModel();
-    this->Predict(dmat, output_margin, &this->preds_);
-    *len = this->preds_.size();
-    return &this->preds_[0];
+    this->Predict(dmat, output_margin != 0, &this->preds_, ntree_limit);
+    *len = static_cast<bst_ulong>(this->preds_.size());
+    return BeginPtr(this->preds_);
   }
   inline void BoostOneIter(const DataMatrix &train,
                            float *grad, float *hess, bst_ulong len) {
@@ -37,15 +44,15 @@ class Booster: public learner::BoostLearner<FMatrixS> {
     for (bst_omp_uint j = 0; j < ndata; ++j) {
       gpair_[j] = bst_gpair(grad[j], hess[j]);
     }
-    gbm_->DoBoost(train.fmat, train.info.info, &gpair_);
+    gbm_->DoBoost(train.fmat(), train.info.info, &gpair_);
   }
   inline void CheckInitModel(void) {
     if (!init_model) {
       this->InitModel(); init_model = true;
     }
   }
   inline void LoadModel(const char *fname) {
-    learner::BoostLearner<FMatrixS>::LoadModel(fname);
+    learner::BoostLearner::LoadModel(fname);
     this->init_model = true;
   }
   inline const char** GetModelDump(const utils::FeatMap& fmap, bool with_stats, bst_ulong *len) {
@@ -54,8 +61,8 @@ class Booster: public learner::BoostLearner<FMatrixS> {
     for (size_t i = 0; i < model_dump.size(); ++i) {
       model_dump_cptr[i] = model_dump[i].c_str();
     }
-    *len = model_dump.size();
-    return &model_dump_cptr[0];
+    *len = static_cast<bst_ulong>(model_dump.size());
+    return BeginPtr(model_dump_cptr);
   }
   // temporal fields
   // temporal data to save evaluation dump
@@ -74,7 +81,7 @@ using namespace xgboost::wrapper;
 
 extern "C"{
   void* XGDMatrixCreateFromFile(const char *fname, int silent) {
-    return LoadDataMatrix(fname, silent, false);
+    return LoadDataMatrix(fname, silent != 0, false);
   }
   void* XGDMatrixCreateFromCSR(const bst_ulong *indptr,
                                const unsigned *indices,
@@ -89,13 +96,38 @@ extern "C"{
     }
     mat.row_data_.resize(nelem);
     for (bst_ulong i = 0; i < nelem; ++i) {
-      mat.row_data_[i] = SparseBatch::Entry(indices[i], data[i]);
+      mat.row_data_[i] = RowBatch::Entry(indices[i], data[i]);
       mat.info.info.num_col = std::max(mat.info.info.num_col,
                                        static_cast<size_t>(indices[i]+1));
     }
     mat.info.info.num_row = nindptr - 1;
     return p_mat;
   }
+  XGB_DLL void* XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
+                                       const unsigned *indices,
+                                       const float *data,
+                                       bst_ulong nindptr,
+                                       bst_ulong nelem) {
+    DMatrixSimple *p_mat = new DMatrixSimple();
+    DMatrixSimple &mat = *p_mat;
+    utils::SparseCSRMBuilder<RowBatch::Entry, false> builder(mat.row_ptr_, mat.row_data_);
+    builder.InitBudget();
+    bst_ulong ncol = nindptr - 1;
+    for (bst_ulong i = 0; i < ncol; ++i) {
+      for (unsigned j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
+        builder.AddBudget(indices[j]);
+      }
+    }
+    builder.InitStorage();
+    for (bst_ulong i = 0; i < ncol; ++i) {
+      for (unsigned j = col_ptr[i]; j < col_ptr[i+1]; ++j) {
+        builder.PushElem(indices[j], RowBatch::Entry(static_cast<bst_uint>(i), data[j]));
+      }
+    }
+    mat.info.info.num_row = mat.row_ptr_.size() - 1;
+    mat.info.info.num_col = static_cast<size_t>(ncol);
+    return p_mat;
+  }
   void* XGDMatrixCreateFromMat(const float *data,
                                bst_ulong nrow,
                                bst_ulong ncol,
@@ -108,7 +140,7 @@ extern "C"{
       bst_ulong nelem = 0;
       for (bst_ulong j = 0; j < ncol; ++j) {
         if (data[j] != missing) {
-          mat.row_data_.push_back(SparseBatch::Entry(j, data[j]));
+          mat.row_data_.push_back(RowBatch::Entry(j, data[j]));
           ++nelem;
         }
       }
@@ -135,17 +167,17 @@ extern "C"{
     ret.info.info.num_row = len;
     ret.info.info.num_col = src.info.num_col();
 
-    utils::IIterator<SparseBatch> *iter = src.fmat.RowIterator();
+    utils::IIterator<RowBatch> *iter = src.fmat()->RowIterator();
     iter->BeforeFirst();
     utils::Assert(iter->Next(), "slice");
-    const SparseBatch &batch = iter->Value();
+    const RowBatch &batch = iter->Value();
     for (bst_ulong i = 0; i < len; ++i) {
       const int ridx = idxset[i];
-      SparseBatch::Inst inst = batch[ridx];
+      RowBatch::Inst inst = batch[ridx];
       utils::Check(static_cast<bst_ulong>(ridx) < batch.size, "slice index exceed number of rows");
       ret.row_data_.resize(ret.row_data_.size() + inst.length);
       memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
-             sizeof(SparseBatch::Entry) * inst.length);
+             sizeof(RowBatch::Entry) * inst.length);
       ret.row_ptr_.push_back(ret.row_ptr_.back() + inst.length);
       if (src.info.labels.size() != 0) {
         ret.info.labels.push_back(src.info.labels[ridx]);
@@ -156,49 +188,52 @@ extern "C"{
       if (src.info.info.root_index.size() != 0) {
         ret.info.info.root_index.push_back(src.info.info.root_index[ridx]);
       }
+      if (src.info.info.fold_index.size() != 0) {
+        ret.info.info.fold_index.push_back(src.info.info.fold_index[ridx]);
+      }
     }
     return p_ret;
   }
   void XGDMatrixFree(void *handle) {
     delete static_cast<DataMatrix*>(handle);
   }
   void XGDMatrixSaveBinary(void *handle, const char *fname, int silent) {
-    SaveDataMatrix(*static_cast<DataMatrix*>(handle), fname, silent);
+    SaveDataMatrix(*static_cast<DataMatrix*>(handle), fname, silent != 0);
   }
   void XGDMatrixSetFloatInfo(void *handle, const char *field, const float *info, bst_ulong len) {
     std::vector<float> &vec = 
         static_cast<DataMatrix*>(handle)->info.GetFloatInfo(field);
     vec.resize(len);
-    memcpy(&vec[0], info, sizeof(float) * len);
+    memcpy(BeginPtr(vec), info, sizeof(float) * len);
   }
   void XGDMatrixSetUIntInfo(void *handle, const char *field, const unsigned *info, bst_ulong len) {
     std::vector<unsigned> &vec =
         static_cast<DataMatrix*>(handle)->info.GetUIntInfo(field);
     vec.resize(len);
-    memcpy(&vec[0], info, sizeof(unsigned) * len);
+    memcpy(BeginPtr(vec), info, sizeof(unsigned) * len);
   }
   void XGDMatrixSetGroup(void *handle, const unsigned *group, bst_ulong len) {
     DataMatrix *pmat = static_cast<DataMatrix*>(handle);
     pmat->info.group_ptr.resize(len + 1);
     pmat->info.group_ptr[0] = 0;
-    for (bst_ulong i = 0; i < len; ++i) {
+    for (uint64_t i = 0; i < len; ++i) {
       pmat->info.group_ptr[i+1] = pmat->info.group_ptr[i]+group[i];
     }
   }
   const float* XGDMatrixGetFloatInfo(const void *handle, const char *field, bst_ulong* len) {
     const std::vector<float> &vec =
         static_cast<const DataMatrix*>(handle)->info.GetFloatInfo(field);
-    *len = vec.size();
-    return &vec[0];
+    *len = static_cast<bst_ulong>(vec.size());
+    return BeginPtr(vec);
   }
   const unsigned* XGDMatrixGetUIntInfo(const void *handle, const char *field, bst_ulong* len) {
     const std::vector<unsigned> &vec =
         static_cast<const DataMatrix*>(handle)->info.GetUIntInfo(field);
-    *len = vec.size();
-    return &vec[0];
+    *len = static_cast<bst_ulong>(vec.size());
+    return BeginPtr(vec);
   }
   bst_ulong XGDMatrixNumRow(const void *handle) {
-    return static_cast<const DataMatrix*>(handle)->info.num_row();
+    return static_cast<bst_ulong>(static_cast<const DataMatrix*>(handle)->info.num_row());
   }
 
   // xgboost implementation
@@ -244,8 +279,8 @@ extern "C"{
     bst->eval_str = bst->EvalOneIter(iter, mats, names);
     return bst->eval_str.c_str();
   }
-  const float *XGBoosterPredict(void *handle, void *dmat, int output_margin, bst_ulong *len) {
-    return static_cast<Booster*>(handle)->Pred(*static_cast<DataMatrix*>(dmat), output_margin, len);
+  const float *XGBoosterPredict(void *handle, void *dmat, int output_margin, unsigned ntree_limit, bst_ulong *len) {
+    return static_cast<Booster*>(handle)->Pred(*static_cast<DataMatrix*>(dmat), output_margin, ntree_limit, len);
   }
   void XGBoosterLoadModel(void *handle, const char *fname) {
     static_cast<Booster*>(handle)->LoadModel(fname);
@@ -260,4 +295,4 @@ extern "C"{
     }
     return static_cast<Booster*>(handle)->GetModelDump(featmap, false, len);
   }
-};
+}