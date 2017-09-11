@@ -32,7 +32,7 @@ class Booster: public learner::BoostLearner<FMatrixS> {
   inline void BoostOneIter(const DataMatrix &train,
                            float *grad, float *hess, size_t len) {
     this->gpair_.resize(len);
-    const unsigned ndata = static_cast<unsigned>(len);    
+    const unsigned ndata = static_cast<unsigned>(len);
     #pragma omp parallel for schedule(static)
     for (unsigned j = 0; j < ndata; ++j) {
       gpair_[j] = bst_gpair(grad[j], hess[j]);
@@ -42,15 +42,15 @@ class Booster: public learner::BoostLearner<FMatrixS> {
   inline void CheckInitModel(void) {
     if (!init_model) {
       this->InitModel(); init_model = true;
-    }  
+    }
   }
   inline void LoadModel(const char *fname) {
     learner::BoostLearner<FMatrixS>::LoadModel(fname);
     this->init_model = true;
   }
   inline const char** GetModelDump(const utils::FeatMap& fmap, bool with_stats, size_t *len) {
     model_dump = this->DumpModel(fmap, with_stats);
-    model_dump_cptr.resize(model_dump.size()); 
+    model_dump_cptr.resize(model_dump.size());
     for (size_t i = 0; i < model_dump.size(); ++i) {
       model_dump_cptr[i] = model_dump[i].c_str();
     }
@@ -82,11 +82,11 @@ extern "C"{
                                size_t nindptr,
                                size_t nelem) {
     DMatrixSimple *p_mat = new DMatrixSimple();
-    DMatrixSimple &mat = *p_mat; 
+    DMatrixSimple &mat = *p_mat;
     mat.row_ptr_.resize(nindptr);
     memcpy(&mat.row_ptr_[0], indptr, sizeof(size_t)*nindptr);
     mat.row_data_.resize(nelem);
-    for (size_t i = 0; i < nelem; ++ i) {
+    for (size_t i = 0; i < nelem; ++i) {
       mat.row_data_[i] = SparseBatch::Entry(indices[i], data[i]);
       mat.info.num_col = std::max(mat.info.num_col,
                                   static_cast<size_t>(indices[i]+1));
@@ -133,15 +133,15 @@ extern "C"{
     ret.info.num_row = len;
     ret.info.num_col = src.info.num_col;
 
-    utils::IIterator<SparseBatch> *iter = src.fmat.RowIterator();    
+    utils::IIterator<SparseBatch> *iter = src.fmat.RowIterator();
     iter->BeforeFirst();
     utils::Assert(iter->Next(), "slice");
     const SparseBatch &batch = iter->Value();
-    for(size_t i = 0; i < len; ++i) {
+    for (size_t i = 0; i < len; ++i) {
       const int ridx = idxset[i];
       SparseBatch::Inst inst = batch[ridx];
       utils::Check(ridx < batch.size, "slice index exceed number of rows");
-      ret.row_data_.resize(ret.row_data_.size() + inst.length);      
+      ret.row_data_.resize(ret.row_data_.size() + inst.length);
       memcpy(&ret.row_data_[ret.row_ptr_.back()], inst.data,
              sizeof(SparseBatch::Entry) * inst.length);
       ret.row_ptr_.push_back(ret.row_ptr_.back() + inst.length);
@@ -160,9 +160,9 @@ extern "C"{
   void XGDMatrixFree(void *handle) {
     delete static_cast<DataMatrix*>(handle);
   }
-  void XGDMatrixSaveBinary(void *handle, const char *fname, int silent) {    
+  void XGDMatrixSaveBinary(void *handle, const char *fname, int silent) {
     SaveDataMatrix(*static_cast<DataMatrix*>(handle), fname, silent);
-  }  
+  }
   void XGDMatrixSetLabel(void *handle, const float *label, size_t len) {
     DataMatrix *pmat = static_cast<DataMatrix*>(handle);
     pmat->info.labels.resize(len);
@@ -173,11 +173,11 @@ extern "C"{
     pmat->info.weights.resize(len);
     memcpy(&(pmat->info).weights[0], weight, sizeof(float) * len);
   }
-  void XGDMatrixSetGroup(void *handle, const unsigned *group, size_t len){
+  void XGDMatrixSetGroup(void *handle, const unsigned *group, size_t len) {
     DataMatrix *pmat = static_cast<DataMatrix*>(handle);
     pmat->info.group_ptr.resize(len + 1);
     pmat->info.group_ptr[0] = 0;
-    for (size_t i = 0; i < len; ++ i) {
+    for (size_t i = 0; i < len; ++i) {
       pmat->info.group_ptr[i+1] = pmat->info.group_ptr[i]+group[i];
     }
   }
@@ -217,16 +217,17 @@ extern "C"{
     bst->CheckInit(dtr);
     bst->UpdateOneIter(iter, *dtr);
   }
-  void XGBoosterBoostOneIter(void *handle, void *dtrain, 
+  void XGBoosterBoostOneIter(void *handle, void *dtrain,
                              float *grad, float *hess, size_t len) {
     Booster *bst = static_cast<Booster*>(handle);
     DataMatrix *dtr = static_cast<DataMatrix*>(dtrain);
     bst->CheckInitModel();
     bst->CheckInit(dtr);
     bst->BoostOneIter(*dtr, grad, hess, len);
   }
-  const char* XGBoosterEvalOneIter(void *handle, int iter, void *dmats[], const char *evnames[], size_t len) {
-    Booster *bst = static_cast<Booster*>(handle);    
+  const char* XGBoosterEvalOneIter(void *handle, int iter, void *dmats[],
+                                   const char *evnames[], size_t len) {
+    Booster *bst = static_cast<Booster*>(handle);
     std::vector<std::string> names;
     std::vector<const DataMatrix*> mats;
     for (size_t i = 0; i < len; ++i) {
@@ -243,13 +244,12 @@ extern "C"{
   void XGBoosterLoadModel(void *handle, const char *fname) {
     static_cast<Booster*>(handle)->LoadModel(fname);
   }
-  void XGBoosterSaveModel( const void *handle, const char *fname) {
+  void XGBoosterSaveModel(const void *handle, const char *fname) {
     static_cast<const Booster*>(handle)->SaveModel(fname);
   }
   const char** XGBoosterDumpModel(void *handle, const char *fmap, size_t *len){
-    using namespace xgboost::utils;
-    FeatMap featmap; 
-    if(strlen(fmap) != 0) {
+    utils::FeatMap featmap;
+    if (strlen(fmap) != 0) {
       featmap.LoadText(fmap);
     }
     return static_cast<Booster*>(handle)->GetModelDump(featmap, false, len);