@@ -24,25 +24,25 @@ class ConfigReaderBase {
    * \return current parameter name 
    */
   inline const char *name(void) const {
-    return s_name;
+    return s_name.c_str();
   }
   /*! 
    * \brief get current value, called after Next returns true
    * \return current parameter value 
    */
   inline const char *val(void) const {
-    return s_val;
+    return s_val.c_str();
   }
   /*! 
    * \brief move iterator to next position
    * \return true if there is value in next position
    */
   inline bool Next(void) {
     while (!this->IsEnd()) {
-      GetNextToken(s_name);
-      if (s_name[0] == '=') return false;
-      if (GetNextToken( s_buf ) || s_buf[0] != '=') return false;
-      if (GetNextToken( s_val ) || s_val[0] == '=') return false;
+      GetNextToken(&s_name);
+      if (s_name == "=") return false;
+      if (GetNextToken(&s_buf) || s_buf != "=")  return false;
+      if (GetNextToken(&s_val) || s_val == "=")  return false;
       return true;
     }
     return false;
@@ -63,84 +63,80 @@ class ConfigReaderBase {
 
  private:
   char ch_buf;
-  char s_name[100000], s_val[100000], s_buf[100000];
+  std::string s_name, s_val, s_buf;
 
   inline void SkipLine(void) {
     do {
       ch_buf = this->GetChar();
     } while (ch_buf != EOF && ch_buf != '\n' && ch_buf != '\r');
   }
 
-  inline void ParseStr(char tok[]) {
-    int i = 0;
+  inline void ParseStr(std::string *tok) {
     while ((ch_buf = this->GetChar()) != EOF) {
       switch (ch_buf) {
-        case '\\': tok[i++] = this->GetChar(); break;
-        case '\"': tok[i++] = '\0'; return;
+        case '\\': *tok += this->GetChar(); break;
+        case '\"': return;
         case '\r':
         case '\n': Error("ConfigReader: unterminated string");
-        default: tok[i++] = ch_buf;
+        default: *tok += ch_buf;
       }
     }
     Error("ConfigReader: unterminated string");
   }
-  inline void ParseStrML(char tok[]) {
-    int i = 0;
+  inline void ParseStrML(std::string *tok) {
     while ((ch_buf = this->GetChar()) != EOF) {
       switch (ch_buf) {
-        case '\\': tok[i++] = this->GetChar(); break;
-        case '\'': tok[i++] = '\0'; return;
-        default: tok[i++] = ch_buf;
+        case '\\': *tok += this->GetChar(); break;
+        case '\'': return;
+        default: *tok += ch_buf;
       }
     }
     Error("unterminated string");
   }
   // return newline
-  inline bool GetNextToken(char tok[]) {
-    int i = 0;
+  inline bool GetNextToken(std::string *tok) {
+    tok->clear();
     bool new_line = false;
     while (ch_buf != EOF) {
       switch (ch_buf) {
         case '#' : SkipLine(); new_line = true; break;
         case '\"':
-          if (i == 0) {
+          if (tok->length() == 0) {
             ParseStr(tok); ch_buf = this->GetChar(); return new_line;
           } else {
             Error("ConfigReader: token followed directly by string");
           }
         case '\'':
-          if (i == 0) {
-            ParseStrML( tok ); ch_buf = this->GetChar(); return new_line;
+          if (tok->length() == 0) {
+            ParseStrML(tok); ch_buf = this->GetChar(); return new_line;
           } else {
             Error("ConfigReader: token followed directly by string");
           }
         case '=':
-          if (i == 0) {
+          if (tok->length() == 0) {
             ch_buf = this->GetChar();
-            tok[0] = '=';
-            tok[1] = '\0';
-          } else {
-            tok[i] = '\0';
+            *tok = '=';
           }
           return new_line;
         case '\r':
         case '\n':
-          if (i == 0) new_line = true;
+          if (tok->length() == 0) new_line = true;
         case '\t':
         case ' ' :
           ch_buf = this->GetChar();
-          if (i > 0) {
-            tok[i] = '\0';
-            return new_line;
-          }
+          if (tok->length() != 0) return new_line;
           break;
         default:
-          tok[i++] = ch_buf;
+          *tok += ch_buf;
           ch_buf = this->GetChar();
           break;
       }
     }
-    return true;
+    if (tok->length() == 0) {
+      return true;
+    } else {
+      return false;
+    }
   }
 };
 /*!