@@ -1,6 +1,8 @@
+// Copyright by Contributors
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
 #define NOMINMAX
+#include <string>
 #include "../utils/io.h"
 
 // implements a single no split version of DMLC
@@ -9,7 +11,7 @@
 namespace xgboost {
 namespace utils {
 /*!
- * \brief line split implementation from single FILE 
+ * \brief line split implementation from single FILE
  * simply returns lines of files, used for stdin
  */
 class SingleFileSplit : public dmlc::InputSplit {
@@ -32,7 +34,7 @@ class SingleFileSplit : public dmlc::InputSplit {
   }
   virtual size_t Read(void *ptr, size_t size) {
     return std::fread(ptr, 1, size, fp_);
-  }  
+  }
   virtual void Write(const void *ptr, size_t size) {
     utils::Error("cannot do write in inputsplit");
   }
@@ -47,13 +49,13 @@ class SingleFileSplit : public dmlc::InputSplit {
                                 chunk_end_);
     out_rec->dptr = chunk_begin_;
     out_rec->size = next - chunk_begin_;
-    chunk_begin_ = next;    
+    chunk_begin_ = next;
     return true;
   }
   virtual bool NextChunk(Blob *out_chunk) {
     if (chunk_begin_ == chunk_end_) {
       if (!LoadChunk()) return false;
-    }    
+    }
     out_chunk->dptr = chunk_begin_;
     out_chunk->size = chunk_end_ - chunk_begin_;
     chunk_begin_ = chunk_end_;
@@ -64,8 +66,8 @@ class SingleFileSplit : public dmlc::InputSplit {
     if (max_size <= overflow_.length()) {
       *size = 0; return true;
     }
-    if (overflow_.length() != 0) { 
-      std::memcpy(buf, BeginPtr(overflow_), overflow_.length());  
+    if (overflow_.length() != 0) {
+      std::memcpy(buf, BeginPtr(overflow_), overflow_.length());
     }
     size_t olen = overflow_.length();
     overflow_.resize(0);
@@ -88,13 +90,13 @@ class SingleFileSplit : public dmlc::InputSplit {
       return true;
     }
   }
-  
+
  protected:
   inline const char* FindLastRecordBegin(const char *begin,
                                          const char *end) {
     if (begin == end) return begin;
     for (const char *p = end - 1; p != begin; --p) {
-      if (*p == '\n' || *p == '\r') return p + 1; 
+      if (*p == '\n' || *p == '\r') return p + 1;
     }
     return begin;
   }
@@ -143,7 +145,7 @@ class StdFile : public dmlc::Stream {
  public:
   explicit StdFile(std::FILE *fp, bool use_stdio)
       : fp(fp), use_stdio(use_stdio) {
-  }  
+  }
   virtual ~StdFile(void) {
     this->Close();
   }
@@ -154,7 +156,7 @@ class StdFile : public dmlc::Stream {
     std::fwrite(ptr, size, 1, fp);
   }
   virtual void Seek(size_t pos) {
-    std::fseek(fp, static_cast<long>(pos), SEEK_SET);
+    std::fseek(fp, static_cast<long>(pos), SEEK_SET);  // NOLINT(*)
   }
   virtual size_t Tell(void) {
     return std::ftell(fp);
@@ -197,7 +199,7 @@ Stream *Stream::Create(const char *fname, const char * const mode, bool allow_nu
       "to use hdfs, s3 or distributed version, compile with make dmlc=1";
   utils::Check(strncmp(fname, "s3://", 5) != 0, msg);
   utils::Check(strncmp(fname, "hdfs://", 7) != 0, msg);
-  
+
   std::FILE *fp = NULL;
   bool use_stdio = false;
   using namespace std;