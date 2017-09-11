@@ -4,18 +4,17 @@
  * \brief helper class to load in configures from file
  * \author Tianqi Chen
  */
-#ifndef XGBOOST_UTILS_CONFIG_H_
-#define XGBOOST_UTILS_CONFIG_H_
+#ifndef XGBOOST_COMMON_CONFIG_H_
+#define XGBOOST_COMMON_CONFIG_H_
 
 #include <cstdio>
 #include <cstring>
 #include <string>
 #include <istream>
 #include <fstream>
-#include "./utils.h"
 
 namespace xgboost {
-namespace utils {
+namespace common {
 /*!
  * \brief base implementation of config reader
  */
@@ -79,11 +78,11 @@ class ConfigReaderBase {
         case '\\': *tok += this->GetChar(); break;
         case '\"': return;
         case '\r':
-        case '\n': Error("ConfigReader: unterminated string");
+        case '\n': LOG(FATAL)<< "ConfigReader: unterminated string";
         default: *tok += ch_buf;
       }
     }
-    Error("ConfigReader: unterminated string");
+    LOG(FATAL) << "ConfigReader: unterminated string";
   }
   inline void ParseStrML(std::string *tok) {
     while ((ch_buf = this->GetChar()) != EOF) {
@@ -93,7 +92,7 @@ class ConfigReaderBase {
         default: *tok += ch_buf;
       }
     }
-    Error("unterminated string");
+    LOG(FATAL) << "unterminated string";
   }
   // return newline
   inline bool GetNextToken(std::string *tok) {
@@ -106,13 +105,13 @@ class ConfigReaderBase {
           if (tok->length() == 0) {
             ParseStr(tok); ch_buf = this->GetChar(); return new_line;
           } else {
-            Error("ConfigReader: token followed directly by string");
+            LOG(FATAL) << "ConfigReader: token followed directly by string";
           }
         case '\'':
           if (tok->length() == 0) {
             ParseStrML(tok); ch_buf = this->GetChar(); return new_line;
           } else {
-            Error("ConfigReader: token followed directly by string");
+            LOG(FATAL) << "ConfigReader: token followed directly by string";
           }
         case '=':
           if (tok->length() == 0) {
@@ -177,7 +176,7 @@ class ConfigIterator: public ConfigStreamReader {
   explicit ConfigIterator(const char *fname) : ConfigStreamReader(fi) {
     fi.open(fname);
     if (fi.fail()) {
-      utils::Error("cannot open file %s", fname);
+      LOG(FATAL) << "cannot open file " << fname;
     }
     ConfigReaderBase::Init();
   }
@@ -189,6 +188,6 @@ class ConfigIterator: public ConfigStreamReader {
  private:
   std::ifstream fi;
 };
-}  // namespace utils
+}  // namespace common
 }  // namespace xgboost
-#endif  // XGBOOST_UTILS_CONFIG_H_
+#endif  // XGBOOST_COMMON_CONFIG_H_