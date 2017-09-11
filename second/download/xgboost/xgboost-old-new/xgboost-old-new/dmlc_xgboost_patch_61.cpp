@@ -27,7 +27,7 @@
 #else
 #ifdef _FILE_OFFSET_BITS
 #if _FILE_OFFSET_BITS == 32
-#pragma message ("Warning: FILE OFFSET BITS defined to be 32 bit")
+#pragma message("Warning: FILE OFFSET BITS defined to be 32 bit")
 #endif
 #endif
 
@@ -59,17 +59,17 @@ namespace utils {
 const int kPrintBuffer = 1 << 12;
 
 #ifndef RABIT_CUSTOMIZE_MSG_
-/*! 
+/*!
  * \brief handling of Assert error, caused by inappropriate input
- * \param msg error message 
+ * \param msg error message
  */
 inline void HandleAssertError(const char *msg) {
   fprintf(stderr, "AssertError:%s\n", msg);
   exit(-1);
 }
-/*! 
+/*!
  * \brief handling of Check error, caused by inappropriate input
- * \param msg error message 
+ * \param msg error message
  */
 inline void HandleCheckError(const char *msg) {
   fprintf(stderr, "%s\n", msg);
@@ -163,7 +163,7 @@ inline std::FILE *FopenCheck(const char *fname, const char *flag) {
 // easy utils that can be directly accessed in xgboost
 /*! \brief get the beginning address of a vector */
 template<typename T>
-inline T *BeginPtr(std::vector<T> &vec) {
+inline T *BeginPtr(std::vector<T> &vec) {  // NOLINT(*)
   if (vec.size() == 0) {
     return NULL;
   } else {
@@ -172,14 +172,14 @@ inline T *BeginPtr(std::vector<T> &vec) {
 }
 /*! \brief get the beginning address of a vector */
 template<typename T>
-inline const T *BeginPtr(const std::vector<T> &vec) {
+inline const T *BeginPtr(const std::vector<T> &vec) {  // NOLINT(*)
   if (vec.size() == 0) {
     return NULL;
   } else {
     return &vec[0];
   }
 }
-inline char* BeginPtr(std::string &str) {
+inline char* BeginPtr(std::string &str) {  // NOLINT(*)
   if (str.length() == 0) return NULL;
   return &str[0];
 }