@@ -1,4 +1,6 @@
 // implementations in ctypes
+#define _CRT_SECURE_NO_WARNINGS
+#define _CRT_SECURE_NO_DEPRECATE
 #include <cstdio>
 #include <vector>
 #include <string>
@@ -16,7 +18,7 @@ using namespace xgboost::io;
 namespace xgboost {
 namespace wrapper {
 // booster wrapper class
-class Booster: public learner::BoostLearner<FMatrixS> {
+class Booster: public learner::BoostLearner {
  public:
   explicit Booster(const std::vector<DataMatrix*>& mats) {
     this->silent = 1;
@@ -25,8 +27,8 @@ class Booster: public learner::BoostLearner<FMatrixS> {
   }
   const float *Pred(const DataMatrix &dmat, int output_margin, bst_ulong *len) {
     this->CheckInitModel();
-    this->Predict(dmat, output_margin, &this->preds_);
-    *len = this->preds_.size();
+    this->Predict(dmat, output_margin != 0, &this->preds_);
+    *len = static_cast<bst_ulong>(this->preds_.size());
     return &this->preds_[0];
   }
   inline void BoostOneIter(const DataMatrix &train,
@@ -37,15 +39,15 @@ class Booster: public learner::BoostLearner<FMatrixS> {
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
@@ -54,7 +56,7 @@ class Booster: public learner::BoostLearner<FMatrixS> {
     for (size_t i = 0; i < model_dump.size(); ++i) {
       model_dump_cptr[i] = model_dump[i].c_str();
     }
-    *len = model_dump.size();
+    *len = static_cast<bst_ulong>(model_dump.size());
     return &model_dump_cptr[0];
   }
   // temporal fields
@@ -74,7 +76,7 @@ using namespace xgboost::wrapper;
 
 extern "C"{
   void* XGDMatrixCreateFromFile(const char *fname, int silent) {
-    return LoadDataMatrix(fname, silent, false);
+    return LoadDataMatrix(fname, silent != 0, false);
   }
   void* XGDMatrixCreateFromCSR(const bst_ulong *indptr,
                                const unsigned *indices,
@@ -89,7 +91,7 @@ extern "C"{
     }
     mat.row_data_.resize(nelem);
     for (bst_ulong i = 0; i < nelem; ++i) {
-      mat.row_data_[i] = SparseBatch::Entry(indices[i], data[i]);
+      mat.row_data_[i] = RowBatch::Entry(indices[i], data[i]);
       mat.info.info.num_col = std::max(mat.info.info.num_col,
                                        static_cast<size_t>(indices[i]+1));
     }
@@ -108,7 +110,7 @@ extern "C"{
       bst_ulong nelem = 0;
       for (bst_ulong j = 0; j < ncol; ++j) {
         if (data[j] != missing) {
-          mat.row_data_.push_back(SparseBatch::Entry(j, data[j]));
+          mat.row_data_.push_back(RowBatch::Entry(j, data[j]));
           ++nelem;
         }
       }
@@ -135,17 +137,17 @@ extern "C"{
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
@@ -156,14 +158,17 @@ extern "C"{
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
@@ -181,24 +186,24 @@ extern "C"{
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
+    *len = static_cast<bst_ulong>(vec.size());
     return &vec[0];
   }
   const unsigned* XGDMatrixGetUIntInfo(const void *handle, const char *field, bst_ulong* len) {
     const std::vector<unsigned> &vec =
         static_cast<const DataMatrix*>(handle)->info.GetUIntInfo(field);
-    *len = vec.size();
+    *len = static_cast<bst_ulong>(vec.size());
     return &vec[0];
   }
   bst_ulong XGDMatrixNumRow(const void *handle) {
-    return static_cast<const DataMatrix*>(handle)->info.num_row();
+    return static_cast<bst_ulong>(static_cast<const DataMatrix*>(handle)->info.num_row());
   }
 
   // xgboost implementation