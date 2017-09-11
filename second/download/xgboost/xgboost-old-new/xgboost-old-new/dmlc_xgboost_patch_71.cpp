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
@@ -126,8 +133,6 @@ static ThreadLocalStore thread_local_store;
 }  // namespace wrapper
 }  // namespace xgboost
 
-using namespace xgboost::wrapper;
-
 /*! \brief  macro to guard beginning and end section of all functions */
 #define API_BEGIN() try {
 /*!
@@ -173,6 +178,17 @@ const char *XGBSetGetLastError_(const char *str_set) {
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