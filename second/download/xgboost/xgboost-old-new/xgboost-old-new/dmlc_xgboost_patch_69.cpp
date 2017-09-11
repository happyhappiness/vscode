@@ -98,7 +98,14 @@ class Booster: public learner::BoostLearner {
  private:
   bool init_model;
 };
+}  // namespace wrapper
+}  // namespace xgboost
+
+using namespace xgboost::wrapper;
 
+#ifndef XGBOOST_STRICT_CXX98_
+namespace xgboost {
+namespace wrapper {
 // helper to support threadlocal
 struct ThreadLocalStore {
   std::vector<std::string*> data;
@@ -126,17 +133,17 @@ static ThreadLocalStore thread_local_store;
 }  // namespace wrapper
 }  // namespace xgboost
 
-using namespace xgboost::wrapper;
-
 /*! \brief  macro to guard beginning and end section of all functions */
 #define API_BEGIN() try {
 /*!
  * \brief every function starts with API_BEGIN(); and finishes with API_END();
  * \param Finalize optionally put in a finalizer
  */
-#define API_END(Finalize) } catch(std::exception &e) {  \
+#define API_END_FINALIZE(Finalize) } catch(std::exception &e) {  \
     Finalize; return XGBHandleException(e);             \
   } return 0;
+/*! \brief API End with no finalization */
+#define API_END() API_END_FINALIZE(;)
 
 // do not use threadlocal on OSX since it is not always available
 #ifndef DISABLE_THREAD_LOCAL
@@ -171,6 +178,17 @@ const char *XGBSetGetLastError_(const char *str_set) {
   }
   return last_error->c_str();
 }
+#else
+// crippled implementation for solaris case
+// exception handling is not needed for R, so it is OK.
+#define API_BEGIN()
+#define API_END_FINALIZE(Finalize) return 0
+#define API_END() return 0
+
+const char *XGBSetGetLastError_(const char *str_set) {
+  return NULL;
+}
+#endif  // XGBOOST_STRICT_CXX98_
 
 /*! \brief return str message of the last error */
 const char *XGBGetLastError() {
@@ -217,7 +235,7 @@ int XGDMatrixCreateFromCSR(const bst_ulong *indptr,
   }
   mat.info.info.num_row = nindptr - 1;
   *out = p_mat;
-  API_END(delete p_mat);
+  API_END_FINALIZE(delete p_mat);
 }
 
 int XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
@@ -258,7 +276,7 @@ int XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
   mat.info.info.num_row = mat.row_ptr_.size() - 1;
   mat.info.info.num_col = static_cast<size_t>(ncol);
   *out = p_mat;
-  API_END(delete p_mat);
+  API_END_FINALIZE(delete p_mat);
 }
 
 int XGDMatrixCreateFromMat(const float *data,
@@ -289,7 +307,7 @@ int XGDMatrixCreateFromMat(const float *data,
     mat.row_ptr_.push_back(mat.row_ptr_.back() + nelem);
   }
   *out = p_mat;
-  API_END(delete p_mat);
+  API_END_FINALIZE(delete p_mat);
 }
 
 int XGDMatrixSliceDMatrix(DMatrixHandle handle,
@@ -340,7 +358,7 @@ int XGDMatrixSliceDMatrix(DMatrixHandle handle,
     }
   }
   *out = p_ret;
-  API_END(delete p_ret);
+  API_END_FINALIZE(delete p_ret);
 }
 
 int XGDMatrixFree(DMatrixHandle handle) {