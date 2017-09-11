@@ -36,6 +36,9 @@ class SingleFileSplit : public dmlc::InputSplit {
   virtual void Write(const void *ptr, size_t size) {
     utils::Error("cannot do write in inputsplit");
   }
+  virtual void BeforeFirst(void) {
+    std::fseek(fp_, 0, SEEK_SET);
+  }
   virtual bool NextRecord(Blob *out_rec) {
     if (chunk_begin_ == chunk_end_) {
       if (!LoadChunk()) return false;
@@ -138,25 +141,8 @@ class SingleFileSplit : public dmlc::InputSplit {
 
 class StdFile : public dmlc::Stream {
  public:
-  explicit StdFile(const char *fname, const char *mode)
-      : use_stdio(false) {
-    using namespace std;
-#ifndef XGBOOST_STRICT_CXX98_
-    if (!strcmp(fname, "stdin")) {
-      use_stdio = true; fp = stdin;
-    }
-    if (!strcmp(fname, "stdout")) {
-      use_stdio = true; fp = stdout;
-    }
-#endif
-    if (!strncmp(fname, "file://", 7)) fname += 7;
-    if (!use_stdio) {
-      std::string flag = mode;
-      if (flag == "w") flag = "wb";
-      if (flag == "r") flag = "rb";
-      fp = utils::FopenCheck(fname, flag.c_str());
-      
-    }
+  explicit StdFile(FILE *fp, bool use_stdio)
+      : fp(fp), use_stdio(use_stdio) {
   }  
   virtual ~StdFile(void) {
     this->Close();
@@ -203,13 +189,37 @@ InputSplit* InputSplit::Create(const char *uri,
   return new utils::SingleFileSplit(uri);
 }
 
-Stream *Stream::Create(const char *uri, const char * const flag) {
+Stream *Stream::Create(const char *fname, const char * const mode, bool allow_null) {
   using namespace xgboost;
   const char *msg = "xgboost is compiled in local mode\n"\
       "to use hdfs, s3 or distributed version, compile with make dmlc=1";
-  utils::Check(strncmp(uri, "s3://", 5) != 0, msg);
-  utils::Check(strncmp(uri, "hdfs://", 7) != 0, msg);
-  return new utils::StdFile(uri, flag);
+  utils::Check(strncmp(fname, "s3://", 5) != 0, msg);
+  utils::Check(strncmp(fname, "hdfs://", 7) != 0, msg);
+  
+  FILE *fp = NULL;
+  bool use_stdio = false;
+  using namespace std;
+#ifndef XGBOOST_STRICT_CXX98_
+  if (!strcmp(fname, "stdin")) {
+    use_stdio = true; fp = stdin;
+  }
+  if (!strcmp(fname, "stdout")) {
+    use_stdio = true; fp = stdout;
+  }
+#endif
+  if (!strncmp(fname, "file://", 7)) fname += 7;
+  if (!use_stdio) {
+    std::string flag = mode;
+    if (flag == "w") flag = "wb";
+    if (flag == "r") flag = "rb";
+    fp = fopen64(fname, flag.c_str());
+  }
+  if (fp != NULL) {
+    return new utils::StdFile(fp, use_stdio);
+  } else {
+    utils::Check(allow_null, "fail to open file %s", fname);
+    return NULL;
+  }
 }
 }  // namespace dmlc
 