@@ -23,18 +23,18 @@ class Booster: public learner::BoostLearner<FMatrixS> {
     this->init_model = false;
     this->SetCacheData(mats);
   }
-  const float *Pred(const DataMatrix &dmat, int output_margin, uint64_t *len) {
+  const float *Pred(const DataMatrix &dmat, int output_margin, bst_ulong *len) {
     this->CheckInitModel();
     this->Predict(dmat, output_margin, &this->preds_);
     *len = this->preds_.size();
     return &this->preds_[0];
   }
   inline void BoostOneIter(const DataMatrix &train,
-                           float *grad, float *hess, uint64_t len) {
+                           float *grad, float *hess, bst_ulong len) {
     this->gpair_.resize(len);
-    const unsigned ndata = static_cast<unsigned>(len);
+    const bst_omp_uint ndata = static_cast<bst_omp_uint>(len);
     #pragma omp parallel for schedule(static)
-    for (unsigned j = 0; j < ndata; ++j) {
+    for (bst_omp_uint j = 0; j < ndata; ++j) {
       gpair_[j] = bst_gpair(grad[j], hess[j]);
     }
     gbm_->DoBoost(train.fmat, train.info.info, &gpair_);
@@ -48,7 +48,7 @@ class Booster: public learner::BoostLearner<FMatrixS> {
     learner::BoostLearner<FMatrixS>::LoadModel(fname);
     this->init_model = true;
   }
-  inline const char** GetModelDump(const utils::FeatMap& fmap, bool with_stats, uint64_t *len) {
+  inline const char** GetModelDump(const utils::FeatMap& fmap, bool with_stats, bst_ulong *len) {
     model_dump = this->DumpModel(fmap, with_stats);
     model_dump_cptr.resize(model_dump.size());
     for (size_t i = 0; i < model_dump.size(); ++i) {
@@ -76,19 +76,19 @@ extern "C"{
   void* XGDMatrixCreateFromFile(const char *fname, int silent) {
     return LoadDataMatrix(fname, silent, false);
   }
-  void* XGDMatrixCreateFromCSR(const uint64_t *indptr,
+  void* XGDMatrixCreateFromCSR(const bst_ulong *indptr,
                                const unsigned *indices,
                                const float *data,
-                               uint64_t nindptr,
-                               uint64_t nelem) {
+                               bst_ulong nindptr,
+                               bst_ulong nelem) {
     DMatrixSimple *p_mat = new DMatrixSimple();
     DMatrixSimple &mat = *p_mat;
     mat.row_ptr_.resize(nindptr);
-    for (uint64_t i = 0; i < nindptr; ++ i) {
+    for (bst_ulong i = 0; i < nindptr; ++i) {
       mat.row_ptr_[i] = static_cast<size_t>(indptr[i]);
     }
     mat.row_data_.resize(nelem);
-    for (uint64_t i = 0; i < nelem; ++i) {
+    for (bst_ulong i = 0; i < nelem; ++i) {
       mat.row_data_[i] = SparseBatch::Entry(indices[i], data[i]);
       mat.info.info.num_col = std::max(mat.info.info.num_col,
                                        static_cast<uint64_t>(indices[i]+1));
@@ -97,16 +97,16 @@ extern "C"{
     return p_mat;
   }
   void* XGDMatrixCreateFromMat(const float *data,
-                               uint64_t nrow,
-                               uint64_t ncol,
+                               bst_ulong nrow,
+                               bst_ulong ncol,
                                float  missing) {
     DMatrixSimple *p_mat = new DMatrixSimple();
     DMatrixSimple &mat = *p_mat;
     mat.info.info.num_row = nrow;
     mat.info.info.num_col = ncol;
-    for (uint64_t i = 0; i < nrow; ++i, data += ncol) {
-      uint64_t nelem = 0;
-      for (uint64_t j = 0; j < ncol; ++j) {
+    for (bst_ulong i = 0; i < nrow; ++i, data += ncol) {
+      bst_ulong nelem = 0;
+      for (bst_ulong j = 0; j < ncol; ++j) {
         if (data[j] != missing) {
           mat.row_data_.push_back(SparseBatch::Entry(j, data[j]));
           ++nelem;
@@ -118,7 +118,7 @@ extern "C"{
   }
   void* XGDMatrixSliceDMatrix(void *handle,
                               const int *idxset,
-                              uint64_t len) {
+                              bst_ulong len) {
     DMatrixSimple tmp;
     DataMatrix &dsrc = *static_cast<DataMatrix*>(handle);
     if (dsrc.magic != DMatrixSimple::kMagic) {
@@ -139,10 +139,10 @@ extern "C"{
     iter->BeforeFirst();
     utils::Assert(iter->Next(), "slice");
     const SparseBatch &batch = iter->Value();
-    for (uint64_t i = 0; i < len; ++i) {
+    for (bst_ulong i = 0; i < len; ++i) {
       const int ridx = idxset[i];
       SparseBatch::Inst inst = batch[ridx];
-      utils::Check(static_cast<uint64_t>(ridx) < batch.size, "slice index exceed number of rows");
+      utils::Check(static_cast<bst_ulong>(ridx) < batch.size, "slice index exceed number of rows");
       ret.row_data_.resize(ret.row_data_.size() + inst.length);
       memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
              sizeof(SparseBatch::Entry) * inst.length);
@@ -168,13 +168,13 @@ extern "C"{
   void XGDMatrixSaveBinary(void *handle, const char *fname, int silent) {
     SaveDataMatrix(*static_cast<DataMatrix*>(handle), fname, silent);
   }
-  void XGDMatrixSetFloatInfo(void *handle, const char *field, const float *info, uint64_t len) {
+  void XGDMatrixSetFloatInfo(void *handle, const char *field, const float *info, bst_ulong len) {
     std::vector<float> &vec = 
         static_cast<DataMatrix*>(handle)->info.GetFloatInfo(field);
     vec.resize(len);
     memcpy(&vec[0], info, sizeof(float) * len);
   }
-  void XGDMatrixSetUIntInfo(void *handle, const char *field, const unsigned *info, uint64_t len) {
+  void XGDMatrixSetUIntInfo(void *handle, const char *field, const unsigned *info, bst_ulong len) {
     std::vector<unsigned> &vec =
         static_cast<DataMatrix*>(handle)->info.GetUIntInfo(field);
     vec.resize(len);
@@ -194,20 +194,20 @@ extern "C"{
     *len = vec.size();
     return &vec[0];
   }
-  const unsigned* XGDMatrixGetUIntInfo(const void *handle, const char *field, uint64_t* len) {
+  const unsigned* XGDMatrixGetUIntInfo(const void *handle, const char *field, bst_ulong* len) {
     const std::vector<unsigned> &vec =
         static_cast<const DataMatrix*>(handle)->info.GetUIntInfo(field);
     *len = vec.size();
     return &vec[0];
   }
-  uint64_t XGDMatrixNumRow(const void *handle) {
+  bst_ulong XGDMatrixNumRow(const void *handle) {
     return static_cast<const DataMatrix*>(handle)->info.num_row();
   }
 
   // xgboost implementation
-  void *XGBoosterCreate(void *dmats[], uint64_t len) {
+  void *XGBoosterCreate(void *dmats[], bst_ulong len) {
     std::vector<DataMatrix*> mats;
-    for (uint64_t i = 0; i < len; ++i) {
+    for (bst_ulong i = 0; i < len; ++i) {
       DataMatrix *dtr = static_cast<DataMatrix*>(dmats[i]);
       mats.push_back(dtr);
     }
@@ -227,27 +227,27 @@ extern "C"{
     bst->UpdateOneIter(iter, *dtr);
   }
   void XGBoosterBoostOneIter(void *handle, void *dtrain,
-                             float *grad, float *hess, uint64_t len) {
+                             float *grad, float *hess, bst_ulong len) {
     Booster *bst = static_cast<Booster*>(handle);
     DataMatrix *dtr = static_cast<DataMatrix*>(dtrain);
     bst->CheckInitModel();
     bst->CheckInit(dtr);
     bst->BoostOneIter(*dtr, grad, hess, len);
   }
   const char* XGBoosterEvalOneIter(void *handle, int iter, void *dmats[],
-                                   const char *evnames[], uint64_t len) {
+                                   const char *evnames[], bst_ulong len) {
     Booster *bst = static_cast<Booster*>(handle);
     std::vector<std::string> names;
     std::vector<const DataMatrix*> mats;
-    for (uint64_t i = 0; i < len; ++i) {
+    for (bst_ulong i = 0; i < len; ++i) {
       mats.push_back(static_cast<DataMatrix*>(dmats[i]));
       names.push_back(std::string(evnames[i]));
     }
     bst->CheckInitModel();
     bst->eval_str = bst->EvalOneIter(iter, mats, names);
     return bst->eval_str.c_str();
   }
-  const float *XGBoosterPredict(void *handle, void *dmat, int output_margin, uint64_t *len) {
+  const float *XGBoosterPredict(void *handle, void *dmat, int output_margin, bst_ulong *len) {
     return static_cast<Booster*>(handle)->Pred(*static_cast<DataMatrix*>(dmat), output_margin, len);
   }
   void XGBoosterLoadModel(void *handle, const char *fname) {
@@ -256,7 +256,7 @@ extern "C"{
   void XGBoosterSaveModel(const void *handle, const char *fname) {
     static_cast<const Booster*>(handle)->SaveModel(fname);
   }
-  const char** XGBoosterDumpModel(void *handle, const char *fmap, uint64_t *len){
+  const char** XGBoosterDumpModel(void *handle, const char *fmap, bst_ulong *len){
     utils::FeatMap featmap;
     if (strlen(fmap) != 0) {
       featmap.LoadText(fmap);