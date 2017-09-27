  *  Initialization of Servers
  */
                              /* ``Recursive, adj.;
                                   see Recursive.''
                                         -- Unknown   */
 #include "ssl_private.h"
+#include "mpm_common.h"
 
 /*  _________________________________________________________________
 **
 **  Module Initialization
 **  _________________________________________________________________
 */
 
+#ifndef OPENSSL_NO_EC
+#define KEYTYPES "RSA, DSA or ECC"
+#else 
+#define KEYTYPES "RSA or DSA"
+#endif
 
 static void ssl_add_version_components(apr_pool_t *p,
                                        server_rec *s)
 {
     char *modver = ssl_var_lookup(p, s, NULL, NULL, "SSL_VERSION_INTERFACE");
     char *libver = ssl_var_lookup(p, s, NULL, NULL, "SSL_VERSION_LIBRARY");
-    char *incver = ssl_var_lookup(p, s, NULL, NULL, 
+    char *incver = ssl_var_lookup(p, s, NULL, NULL,
                                   "SSL_VERSION_LIBRARY_INTERFACE");
 
-    ap_add_version_component(p, modver);
     ap_add_version_component(p, libver);
 
-    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01876)
                  "%s compiled against Server: %s, Library: %s",
                  modver, AP_SERVER_BASEVERSION, incver);
 }
 
 
 /*
