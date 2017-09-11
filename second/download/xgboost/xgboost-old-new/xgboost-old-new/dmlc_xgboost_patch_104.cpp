@@ -8,6 +8,7 @@
 #include <cstring>
 #include <cmath>
 #include <algorithm>
+#include <exception>
 // include all std functions
 using namespace std;
 #include "./xgboost_wrapper.h"
@@ -102,15 +103,79 @@ class Booster: public learner::BoostLearner {
 
 using namespace xgboost::wrapper;
 
-void* XGDMatrixCreateFromFile(const char *fname, int silent) {
-  return LoadDataMatrix(fname, silent != 0, false, false);
+/*! \brief  macro to guard beginning and end section of all functions */
+#define API_BEGIN() try {
+/*!
+ * \brief every function starts with API_BEGIN(); and finishes with API_END();
+ * \param Finalize optionally put in a finalizer
+ */
+#define API_END(Finalize) } catch(std::exception &e) {  \
+    Finalize; return XGBHandleException(e);             \
+  } return 0;
+
+// do not use threadlocal on OSX since it is not always available
+#ifndef DISABLE_THREAD_LOCAL
+#ifdef __GNUC__
+  #define XGB_TREAD_LOCAL __thread
+#elif __STDC_VERSION__ >= 201112L
+  #define XGB_TREAD_LOCAL _Thread_local
+#elif defined(_MSC_VER)
+  #define XGB_TREAD_LOCAL __declspec(thread)
+#endif
+#endif
+
+#ifndef XGB_TREAD_LOCAL
+#pragma message("Warning: Threadlocal not enabled, used single thread error handling")
+#define XGB_TREAD_LOCAL
+#endif
+
+/*!
+ * \brief a helper function for error handling
+ *  will set the last error to be str_set when it is not NULL
+ * \param str_set the error to set
+ * \return a pointer message to last error
+ */
+const char *XGBSetGetLastError_(const char *str_set) {
+  // use last_error to record last error
+  static XGB_TREAD_LOCAL std::string last_error;
+  if (str_set != NULL) {
+    last_error = str_set;
+  }
+  return last_error.c_str();
 }
-void* XGDMatrixCreateFromCSR(const bst_ulong *indptr,
-                             const unsigned *indices,
-                             const float *data,
-                             bst_ulong nindptr,
-                             bst_ulong nelem) {
-  DMatrixSimple *p_mat = new DMatrixSimple();
+
+/*! \brief return str message of the last error */
+const char *XGBGetLastError() {
+  return XGBSetGetLastError_(NULL);
+}
+
+/*!
+ * \brief handle exception throwed out
+ * \param e the exception
+ * \return the return value of API after exception is handled
+ */
+int XGBHandleException(const std::exception &e) {
+  XGBSetGetLastError_(e.what());
+  return -1;
+}
+
+int XGDMatrixCreateFromFile(const char *fname,
+                            int silent,
+                            DMatrixHandle *out) {
+  API_BEGIN();
+  *out = LoadDataMatrix(fname, silent != 0, false, false);
+  API_END();
+}
+
+int XGDMatrixCreateFromCSR(const bst_ulong *indptr,
+                           const unsigned *indices,
+                           const float *data,
+                           bst_ulong nindptr,
+                           bst_ulong nelem,
+                           DMatrixHandle *out) {
+  DMatrixSimple *p_mat = NULL;
+  API_BEGIN();
+  p_mat = new DMatrixSimple();
   DMatrixSimple &mat = *p_mat;
   mat.row_ptr_.resize(nindptr);
   for (bst_ulong i = 0; i < nindptr; ++i) {
@@ -123,20 +188,24 @@ void* XGDMatrixCreateFromCSR(const bst_ulong *indptr,
                                      static_cast<size_t>(indices[i]+1));
   }
   mat.info.info.num_row = nindptr - 1;
-  return p_mat;
+  *out = p_mat;
+  API_END(delete p_mat);
 }
-void* XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
-                             const unsigned *indices,
-                             const float *data,
-                             bst_ulong nindptr,
-                             bst_ulong nelem) {
+
+int XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
+                           const unsigned *indices,
+                           const float *data,
+                           bst_ulong nindptr,
+                           bst_ulong nelem,
+                           DMatrixHandle *out) {
+  DMatrixSimple *p_mat = NULL;
+  API_BEGIN();
   int nthread;
   #pragma omp parallel
   {
     nthread = omp_get_num_threads();
   }
-
-  DMatrixSimple *p_mat = new DMatrixSimple();
+  p_mat = new DMatrixSimple();
   DMatrixSimple &mat = *p_mat;
   utils::ParallelGroupBuilder<RowBatch::Entry> builder(&mat.row_ptr_, &mat.row_data_);
   builder.InitBudget(0, nthread);
@@ -160,14 +229,19 @@ void* XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
   }
   mat.info.info.num_row = mat.row_ptr_.size() - 1;
   mat.info.info.num_col = static_cast<size_t>(ncol);
-  return p_mat;
+  *out = p_mat;
+  API_END(delete p_mat);
 }
-void* XGDMatrixCreateFromMat(const float *data,
-                             bst_ulong nrow,
-                             bst_ulong ncol,
-                             float  missing) {
+
+int XGDMatrixCreateFromMat(const float *data,
+                           bst_ulong nrow,
+                           bst_ulong ncol,
+                           float  missing,
+                           DMatrixHandle *out) {
+  DMatrixSimple *p_mat = NULL;
+  API_BEGIN();
+  p_mat = new DMatrixSimple();
   bool nan_missing = utils::CheckNAN(missing);
-  DMatrixSimple *p_mat = new DMatrixSimple();
   DMatrixSimple &mat = *p_mat;
   mat.info.info.num_row = nrow;
   mat.info.info.num_col = ncol;
@@ -186,19 +260,24 @@ void* XGDMatrixCreateFromMat(const float *data,
     }
     mat.row_ptr_.push_back(mat.row_ptr_.back() + nelem);
   }
-  return p_mat;
+  *out = p_mat;
+  API_END(delete p_mat);
 }
-void* XGDMatrixSliceDMatrix(void *handle,
-                            const int *idxset,
-                            bst_ulong len) {
+
+int XGDMatrixSliceDMatrix(DMatrixHandle handle,
+                          const int *idxset,
+                          bst_ulong len,
+                          DMatrixHandle *out) {
+  DMatrixSimple *p_ret = NULL;
+  API_BEGIN();
   DMatrixSimple tmp;
   DataMatrix &dsrc = *static_cast<DataMatrix*>(handle);
   if (dsrc.magic != DMatrixSimple::kMagic) {
     tmp.CopyFrom(dsrc);
   }
   DataMatrix &src = (dsrc.magic == DMatrixSimple::kMagic ?
                      *static_cast<DMatrixSimple*>(handle): tmp);
-  DMatrixSimple *p_ret = new DMatrixSimple();
+  p_ret = new DMatrixSimple();
   DMatrixSimple &ret = *p_ret;
 
   utils::Check(src.info.group_ptr.size() == 0,
@@ -232,82 +311,151 @@ void* XGDMatrixSliceDMatrix(void *handle,
       ret.info.info.fold_index.push_back(src.info.info.fold_index[ridx]);
     }
   }
-  return p_ret;
+  *out = p_ret;
+  API_END(delete p_ret);
 }
-void XGDMatrixFree(void *handle) {
+
+int XGDMatrixFree(DMatrixHandle handle) {
+  API_BEGIN();
   delete static_cast<DataMatrix*>(handle);
+  API_END();
 }
-void XGDMatrixSaveBinary(void *handle, const char *fname, int silent) {
+
+int XGDMatrixSaveBinary(DMatrixHandle handle,
+                        const char *fname,
+                        int silent) {
+  API_BEGIN();
   SaveDataMatrix(*static_cast<DataMatrix*>(handle), fname, silent != 0);
+  API_END();
 }
-void XGDMatrixSetFloatInfo(void *handle, const char *field, const float *info, bst_ulong len) {
+
+int XGDMatrixSetFloatInfo(DMatrixHandle handle,
+                          const char *field,
+                          const float *info,
+                          bst_ulong len) {
+  API_BEGIN();
   std::vector<float> &vec =
       static_cast<DataMatrix*>(handle)->info.GetFloatInfo(field);
   vec.resize(len);
   memcpy(BeginPtr(vec), info, sizeof(float) * len);
+  API_END();
 }
-void XGDMatrixSetUIntInfo(void *handle, const char *field, const unsigned *info, bst_ulong len) {
+
+int XGDMatrixSetUIntInfo(DMatrixHandle handle,
+                         const char *field,
+                         const unsigned *info,
+                         bst_ulong len) {
+  API_BEGIN();
   std::vector<unsigned> &vec =
       static_cast<DataMatrix*>(handle)->info.GetUIntInfo(field);
   vec.resize(len);
   memcpy(BeginPtr(vec), info, sizeof(unsigned) * len);
+  API_END();
 }
-void XGDMatrixSetGroup(void *handle, const unsigned *group, bst_ulong len) {
+
+int XGDMatrixSetGroup(DMatrixHandle handle,
+                      const unsigned *group,
+                      bst_ulong len) {
+  API_BEGIN();
   DataMatrix *pmat = static_cast<DataMatrix*>(handle);
   pmat->info.group_ptr.resize(len + 1);
   pmat->info.group_ptr[0] = 0;
   for (uint64_t i = 0; i < len; ++i) {
     pmat->info.group_ptr[i+1] = pmat->info.group_ptr[i] + group[i];
   }
+  API_END();
 }
-const float* XGDMatrixGetFloatInfo(const void *handle, const char *field, bst_ulong* len) {
+
+int XGDMatrixGetFloatInfo(const DMatrixHandle handle,
+                          const char *field,
+                          bst_ulong *out_len,
+                          const float **out_dptr) {
+  API_BEGIN();
   const std::vector<float> &vec =
       static_cast<const DataMatrix*>(handle)->info.GetFloatInfo(field);
-  *len = static_cast<bst_ulong>(vec.size());
-  return BeginPtr(vec);
+  *out_len = static_cast<bst_ulong>(vec.size());
+  *out_dptr = BeginPtr(vec);
+  API_END();
 }
-const unsigned* XGDMatrixGetUIntInfo(const void *handle, const char *field, bst_ulong* len) {
+
+int XGDMatrixGetUIntInfo(const DMatrixHandle handle,
+                         const char *field,
+                         bst_ulong *out_len,
+                         const unsigned **out_dptr) {
+  API_BEGIN();
   const std::vector<unsigned> &vec =
       static_cast<const DataMatrix*>(handle)->info.GetUIntInfo(field);
-  *len = static_cast<bst_ulong>(vec.size());
-  return BeginPtr(vec);
+  *out_len = static_cast<bst_ulong>(vec.size());
+  *out_dptr = BeginPtr(vec);
+  API_END();
 }
-bst_ulong XGDMatrixNumRow(const void *handle) {
-  return static_cast<bst_ulong>(static_cast<const DataMatrix*>(handle)->info.num_row());
+int XGDMatrixNumRow(const DMatrixHandle handle,
+                    bst_ulong *out) {
+  API_BEGIN();
+  *out = static_cast<bst_ulong>(static_cast<const DataMatrix*>(handle)->info.num_row());
+  API_END();
 }
 
 // xgboost implementation
-void *XGBoosterCreate(void *dmats[], bst_ulong len) {
+int XGBoosterCreate(DMatrixHandle dmats[],
+                    bst_ulong len,
+                    BoosterHandle *out) {
+  API_BEGIN();
   std::vector<DataMatrix*> mats;
   for (bst_ulong i = 0; i < len; ++i) {
     DataMatrix *dtr = static_cast<DataMatrix*>(dmats[i]);
     mats.push_back(dtr);
   }
-  return new Booster(mats);
+  *out = new Booster(mats);
+  API_END();
 }
-void XGBoosterFree(void *handle) {
+
+int XGBoosterFree(BoosterHandle handle) {
+  API_BEGIN();
   delete static_cast<Booster*>(handle);
+  API_END();
 }
-void XGBoosterSetParam(void *handle, const char *name, const char *value) {
+
+int XGBoosterSetParam(BoosterHandle handle,
+                      const char *name, const char *value) {
+  API_BEGIN();
   static_cast<Booster*>(handle)->SetParam(name, value);
+  API_END();
 }
-void XGBoosterUpdateOneIter(void *handle, int iter, void *dtrain) {
+
+int XGBoosterUpdateOneIter(BoosterHandle handle,
+                           int iter,
+                           DMatrixHandle dtrain) {
+  API_BEGIN();
   Booster *bst = static_cast<Booster*>(handle);
   DataMatrix *dtr = static_cast<DataMatrix*>(dtrain);
   bst->CheckInitModel();
   bst->CheckInit(dtr);
   bst->UpdateOneIter(iter, *dtr);
+  API_END();
 }
-void XGBoosterBoostOneIter(void *handle, void *dtrain,
-                           float *grad, float *hess, bst_ulong len) {
+
+int XGBoosterBoostOneIter(BoosterHandle handle,
+                          DMatrixHandle dtrain,
+                          float *grad,
+                          float *hess,
+                          bst_ulong len) {
+  API_BEGIN();
   Booster *bst = static_cast<Booster*>(handle);
   DataMatrix *dtr = static_cast<DataMatrix*>(dtrain);
   bst->CheckInitModel();
   bst->CheckInit(dtr);
   bst->BoostOneIter(*dtr, grad, hess, len);
+  API_END();
 }
-const char* XGBoosterEvalOneIter(void *handle, int iter, void *dmats[],
-                                 const char *evnames[], bst_ulong len) {
+
+int XGBoosterEvalOneIter(BoosterHandle handle,
+                         int iter,
+                         DMatrixHandle dmats[],
+                         const char *evnames[],
+                         bst_ulong len,
+                         const char **out_str) {
+  API_BEGIN();
   Booster *bst = static_cast<Booster*>(handle);
   std::vector<std::string> names;
   std::vector<const DataMatrix*> mats;
@@ -317,32 +465,64 @@ const char* XGBoosterEvalOneIter(void *handle, int iter, void *dmats[],
   }
   bst->CheckInitModel();
   bst->eval_str = bst->EvalOneIter(iter, mats, names);
-  return bst->eval_str.c_str();
+  *out_str = bst->eval_str.c_str();
+  API_END();
 }
-const float *XGBoosterPredict(void *handle, void *dmat, int option_mask,
-                              unsigned ntree_limit, bst_ulong *len) {
-  return static_cast<Booster*>(handle)->Pred(*static_cast<DataMatrix*>(dmat),
-                                             option_mask, ntree_limit, len);
+
+int XGBoosterPredict(BoosterHandle handle,
+                     DMatrixHandle dmat,
+                     int option_mask,
+                     unsigned ntree_limit,
+                     bst_ulong *len,
+                     const float **out_result) {
+  API_BEGIN();
+  *out_result = static_cast<Booster*>(handle)->
+      Pred(*static_cast<DataMatrix*>(dmat),
+           option_mask, ntree_limit, len);
+  API_END();
 }
-void XGBoosterLoadModel(void *handle, const char *fname) {
+
+int XGBoosterLoadModel(BoosterHandle handle, const char *fname) {
+  API_BEGIN();
   static_cast<Booster*>(handle)->LoadModel(fname);
+  API_END();
 }
-void XGBoosterSaveModel(void *handle, const char *fname) {
+
+int XGBoosterSaveModel(BoosterHandle handle, const char *fname) {
+  API_BEGIN();
   Booster *bst = static_cast<Booster*>(handle);
   bst->CheckInitModel();
   bst->SaveModel(fname, false);
+  API_END();
 }
-void XGBoosterLoadModelFromBuffer(void *handle, const void *buf, bst_ulong len) {
+
+int XGBoosterLoadModelFromBuffer(BoosterHandle handle,
+                                 const void *buf,
+                                 bst_ulong len) {
+  API_BEGIN();
   static_cast<Booster*>(handle)->LoadModelFromBuffer(buf, len);
+  API_END();
 }
-const char *XGBoosterGetModelRaw(void *handle, bst_ulong *out_len) {
-  return static_cast<Booster*>(handle)->GetModelRaw(out_len);
+
+int XGBoosterGetModelRaw(BoosterHandle handle,
+                         bst_ulong *out_len,
+                         const char **out_dptr) {
+  API_BEGIN();
+  *out_dptr = static_cast<Booster*>(handle)->GetModelRaw(out_len);
+  API_END();
 }
-const char** XGBoosterDumpModel(void *handle, const char *fmap,
-                                int with_stats, bst_ulong *len) {
+
+int XGBoosterDumpModel(BoosterHandle handle,
+                       const char *fmap,
+                       int with_stats,
+                       bst_ulong *len,
+                       const char ***out_models) {
+  API_BEGIN();
   utils::FeatMap featmap;
   if (strlen(fmap) != 0) {
     featmap.LoadText(fmap);
   }
-  return static_cast<Booster*>(handle)->GetModelDump(featmap, with_stats != 0, len);
+  *out_models = static_cast<Booster*>(handle)->GetModelDump(
+      featmap, with_stats != 0, len);
+  API_END();
 }