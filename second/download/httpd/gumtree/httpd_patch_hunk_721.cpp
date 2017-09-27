  *  ssl_engine_init.c
  *  Initialization of Servers
  */
                              /* ``Recursive, adj.;
                                   see Recursive.''
                                         -- Unknown   */
-#include "mod_ssl.h"
+#include "ssl_private.h"
 
 /*  _________________________________________________________________
 **
 **  Module Initialization
 **  _________________________________________________________________
 */
 
-
-static void ssl_add_version_components(apr_pool_t *p,
-                                       server_rec *s)
+static char *ssl_add_version_component(apr_pool_t *p,
+                                       server_rec *s,
+                                       char *name)
 {
-    char *modver = ssl_var_lookup(p, s, NULL, NULL, "SSL_VERSION_INTERFACE");
-    char *libver = ssl_var_lookup(p, s, NULL, NULL, "SSL_VERSION_LIBRARY");
-    char *incver = ssl_var_lookup(p, s, NULL, NULL, 
-                                  "SSL_VERSION_LIBRARY_INTERFACE");
+    char *val = ssl_var_lookup(p, s, NULL, NULL, name);
 
-    ap_add_version_component(p, modver);
-    ap_add_version_component(p, libver);
+    if (val && *val) {
+        ap_add_version_component(p, val);
+    }
 
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
-                 "%s compiled against Server: %s, Library: %s",
-                 modver, AP_SERVER_BASEVERSION, incver);
+    return val;
 }
 
+static char *version_components[] = {
+    "SSL_VERSION_PRODUCT",
+    "SSL_VERSION_INTERFACE",
+    "SSL_VERSION_LIBRARY",
+    NULL
+};
 
-/*
- *  Initialize SSL library
- */
-static void ssl_init_SSLLibrary(server_rec *s)
+static void ssl_add_version_components(apr_pool_t *p,
+                                       server_rec *s)
 {
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
-                 "Init: Initializing %s library", SSL_LIBRARY_NAME);
+    char *vals[sizeof(version_components)/sizeof(char *)];
+    int i;
 
-    SSL_load_error_strings();
-    SSL_library_init();
-    OpenSSL_add_all_algorithms(); /* Required for eg SHA256 client certs */
+    for (i=0; version_components[i]; i++) {
+        vals[i] = ssl_add_version_component(p, s,
+                                            version_components[i]);
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
+                 "Server: %s, Interface: %s, Library: %s",
+                 AP_SERVER_BASEVERSION,
+                 vals[1],  /* SSL_VERSION_INTERFACE */
+                 vals[2]); /* SSL_VERSION_LIBRARY */
 }
 
+
 /*
  * Handle the Temporary RSA Keys and DH Params
  */
 
 #define MODSSL_TMP_KEY_FREE(mc, type, idx) \
     if (mc->pTmpKeys[idx]) { \
