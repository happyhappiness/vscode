@@ -62,15 +62,15 @@ const int kPrintBuffer = 1 << 12;
 
 #ifndef XGBOOST_CUSTOMIZE_MSG_
 /*!
- * \brief handling of Assert error, caused by in-apropriate input
+ * \brief handling of Assert error, caused by inappropriate input
  * \param msg error message
  */
 inline void HandleAssertError(const char *msg) {
   fprintf(stderr, "AssertError:%s\n", msg);
   exit(-1);
 }
 /*!
- * \brief handling of Check error, caused by in-apropriate input
+ * \brief handling of Check error, caused by inappropriate input
  * \param msg error message
  */
 inline void HandleCheckError(const char *msg) {
@@ -157,7 +157,7 @@ inline std::FILE *FopenCheck(const char *fname, const char *flag) {
   return fp;
 }
 }  // namespace utils
-// easy utils that can be directly acessed in xgboost
+// easy utils that can be directly accessed in xgboost
 /*! \brief get the beginning address of a vector */
 template<typename T>
 inline T *BeginPtr(std::vector<T> &vec) { // NOLINT(*)