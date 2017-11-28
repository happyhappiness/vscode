 {
     assert(TheSslErrorShortcuts.empty());
     for (int i = 0; TheSslErrorShortcutsArray[i].name; ++i)
         TheSslErrorShortcuts[TheSslErrorShortcutsArray[i].name] = TheSslErrorShortcutsArray[i].errors;
 }
 
-Ssl::ssl_error_t Ssl::GetErrorCode(const char *name)
+Security::ErrorCode Ssl::GetErrorCode(const char *name)
 {
     //TODO: use a std::map?
     for (int i = 0; TheSslErrorArray[i].name != NULL; ++i) {
         if (strcmp(name, TheSslErrorArray[i].name) == 0)
             return TheSslErrorArray[i].value;
     }
     return SSL_ERROR_NONE;
 }
 
-Ssl::Errors *
-Ssl::ParseErrorString(const char *name)
+bool
+Ssl::ParseErrorString(const char *name, Security::Errors &errors)
 {
     assert(name);
 
-    const Ssl::ssl_error_t ssl_error = GetErrorCode(name);
-    if (ssl_error != SSL_ERROR_NONE)
-        return new Ssl::Errors(ssl_error);
+    const Security::ErrorCode ssl_error = GetErrorCode(name);
+    if (ssl_error != SSL_ERROR_NONE) {
+        errors.emplace(ssl_error);
+        return true;
+    }
 
     if (xisdigit(*name)) {
         const long int value = strtol(name, NULL, 0);
-        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
-            return new Ssl::Errors(value);
-        fatalf("Too small or too bug SSL error code '%s'", name);
+        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX) {
+            errors.emplace(value);
+            return true;
+        }
+        fatalf("Too small or too big TLS error code '%s'", name);
     }
 
     if (TheSslErrorShortcuts.empty())
         loadSslErrorShortcutsMap();
 
     const SslErrorShortcuts::const_iterator it = TheSslErrorShortcuts.find(name);
     if (it != TheSslErrorShortcuts.end()) {
         // Should not be empty...
         assert(it->second[0] != SSL_ERROR_NONE);
-        Ssl::Errors *errors = new Ssl::Errors(it->second[0]);
-        for (int i =1; it->second[i] != SSL_ERROR_NONE; ++i) {
-            errors->push_back_unique(it->second[i]);
+        for (int i = 0; it->second[i] != SSL_ERROR_NONE; ++i) {
+            errors.emplace(it->second[i]);
         }
-        return errors;
+        return true;
     }
 
-    fatalf("Unknown SSL error name '%s'", name);
-    return NULL; // not reached
+    fatalf("Unknown TLS error name '%s'", name);
+    return false; // not reached
 }
 
-const char *Ssl::GetErrorName(Ssl::ssl_error_t value)
+const char *Ssl::GetErrorName(Security::ErrorCode value)
 {
     if (TheSslErrors.empty())
         loadSslErrorMap();
 
     const SslErrors::const_iterator it = TheSslErrors.find(value);
     if (it != TheSslErrors.end())
