@@ -5,16 +5,17 @@
  * base64 is easier to store and pass as text format in mapreduce
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_UTILS_BASE64_INL_H_
-#define XGBOOST_UTILS_BASE64_INL_H_
+#ifndef XGBOOST_COMMON_BASE64_H_
+#define XGBOOST_COMMON_BASE64_H_
 
+#include <dmlc/logging.h>
 #include <cctype>
 #include <cstdio>
 #include <string>
 #include "./io.h"
 
 namespace xgboost {
-namespace utils {
+namespace common {
 /*! \brief buffer reader of the stream that allows you to get */
 class StreamBufferReader {
  public:
@@ -26,7 +27,7 @@ class StreamBufferReader {
   /*!
    * \brief set input stream
    */
-  inline void set_stream(IStream *stream) {
+  inline void set_stream(dmlc::Stream *stream) {
     stream_ = stream;
     read_len_ = read_ptr_ = 1;
   }
@@ -51,7 +52,7 @@ class StreamBufferReader {
 
  private:
   /*! \brief the underlying stream */
-  IStream *stream_;
+  dmlc::Stream *stream_;
   /*! \brief buffer to hold data */
   std::string buffer_;
   /*! \brief length of valid data in buffer */
@@ -80,9 +81,9 @@ static const char EncodeTable[] =
     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
 }  // namespace base64
 /*! \brief the stream that reads from base64, note we take from file pointers */
-class Base64InStream: public IStream {
+class Base64InStream: public dmlc::Stream {
  public:
-  explicit Base64InStream(IStream *fs) : reader_(256) {
+  explicit Base64InStream(dmlc::Stream *fs) : reader_(256) {
     reader_.set_stream(fs);
     num_prev = 0; tmp_ch = 0;
   }
@@ -134,20 +135,22 @@ class Base64InStream: public IStream {
       nvalue = DecodeTable[tmp_ch] << 18;
       {
         // second byte
-        utils::Check((tmp_ch = reader_.GetChar(), tmp_ch != EOF && !isspace(tmp_ch)),
-                     "invalid base64 format");
+        tmp_ch = reader_.GetChar();
+        CHECK(tmp_ch != EOF && !isspace(tmp_ch)) << "invalid base64 format";
         nvalue |= DecodeTable[tmp_ch] << 12;
         *cptr++ = (nvalue >> 16) & 0xFF; --tlen;
-      }
+        }
       {
         // third byte
-        utils::Check((tmp_ch = reader_.GetChar(), tmp_ch != EOF && !isspace(tmp_ch)),
-                     "invalid base64 format");
+        tmp_ch = reader_.GetChar();
+        CHECK(tmp_ch != EOF && !isspace(tmp_ch)) << "invalid base64 format";
         // handle termination
         if (tmp_ch == '=') {
-          utils::Check((tmp_ch = reader_.GetChar(), tmp_ch == '='), "invalid base64 format");
-          utils::Check((tmp_ch = reader_.GetChar(), tmp_ch == EOF || isspace(tmp_ch)),
-                       "invalid base64 format");
+          tmp_ch = reader_.GetChar();
+          CHECK(tmp_ch == '=') << "invalid base64 format";
+          tmp_ch = reader_.GetChar();
+          CHECK(tmp_ch == EOF || isspace(tmp_ch))
+              << "invalid base64 format";
           break;
         }
         nvalue |= DecodeTable[tmp_ch] << 6;
@@ -159,11 +162,13 @@ class Base64InStream: public IStream {
       }
       {
         // fourth byte
-        utils::Check((tmp_ch = reader_.GetChar(), tmp_ch != EOF && !isspace(tmp_ch)),
-                     "invalid base64 format");
+        tmp_ch = reader_.GetChar();
+        CHECK(tmp_ch != EOF && !isspace(tmp_ch))
+            << "invalid base64 format";
         if (tmp_ch == '=') {
-          utils::Check((tmp_ch = reader_.GetChar(), tmp_ch == EOF || isspace(tmp_ch)),
-                       "invalid base64 format");
+          tmp_ch = reader_.GetChar();
+          CHECK(tmp_ch == EOF || isspace(tmp_ch))
+              << "invalid base64 format";
           break;
         }
         nvalue |= DecodeTable[tmp_ch];
@@ -177,12 +182,12 @@ class Base64InStream: public IStream {
       tmp_ch = reader_.GetChar();
     }
     if (kStrictCheck) {
-      utils::Check(tlen == 0, "Base64InStream: read incomplete");
+      CHECK_EQ(tlen, 0) << "Base64InStream: read incomplete";
     }
     return size - tlen;
   }
   virtual void Write(const void *ptr, size_t size) {
-    utils::Error("Base64InStream do not support write");
+    LOG(FATAL) << "Base64InStream do not support write";
   }
 
  private:
@@ -194,9 +199,9 @@ class Base64InStream: public IStream {
   static const bool kStrictCheck = false;
 };
 /*! \brief the stream that write to base64, note we take from file pointers */
-class Base64OutStream: public IStream {
+class Base64OutStream: public dmlc::Stream {
  public:
-  explicit Base64OutStream(IStream *fp) : fp(fp) {
+  explicit Base64OutStream(dmlc::Stream *fp) : fp(fp) {
     buf_top = 0;
   }
   virtual void Write(const void *ptr, size_t size) {
@@ -218,7 +223,7 @@ class Base64OutStream: public IStream {
     }
   }
   virtual size_t Read(void *ptr, size_t size) {
-    utils::Error("Base64OutStream do not support read");
+    LOG(FATAL) << "Base64OutStream do not support read";
     return 0;
   }
   /*!
@@ -245,7 +250,7 @@ class Base64OutStream: public IStream {
   }
 
  private:
-  IStream *fp;
+  dmlc::Stream *fp;
   int buf_top;
   unsigned char buf[4];
   std::string out_buf;
@@ -262,6 +267,6 @@ class Base64OutStream: public IStream {
     }
   }
 };
-}  // namespace utils
+}  // namespace common
 }  // namespace xgboost
-#endif  // XGBOOST_UTILS_BASE64_INL_H_
+#endif  // XGBOOST_COMMON_BASE64_H_