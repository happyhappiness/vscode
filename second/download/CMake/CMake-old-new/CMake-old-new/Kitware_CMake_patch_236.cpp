@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -22,122 +22,89 @@
 
 #include "curl_setup.h"
 
-#ifdef HAVE_GSSAPI
-#ifdef HAVE_OLD_GSSMIT
-#define GSS_C_NT_HOSTBASED_SERVICE gss_nt_service_name
-#define NCOMPAT 1
-#endif
-
-#ifndef CURL_DISABLE_HTTP
+#if defined(HAVE_GSSAPI) && !defined(CURL_DISABLE_HTTP) && defined(USE_SPNEGO)
 
 #include "urldata.h"
 #include "sendf.h"
 #include "curl_gssapi.h"
 #include "rawstr.h"
 #include "curl_base64.h"
 #include "http_negotiate.h"
-#include "curl_memory.h"
+#include "curl_sasl.h"
 #include "url.h"
+#include "curl_printf.h"
 
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
-static int
-get_gss_name(struct connectdata *conn, bool proxy, gss_name_t *server)
-{
-  OM_uint32 major_status, minor_status;
-  gss_buffer_desc token = GSS_C_EMPTY_BUFFER;
-  char name[2048];
-  const char* service = "HTTP";
-
-  token.length = strlen(service) + 1 + strlen(proxy ? conn->proxy.name :
-                                              conn->host.name) + 1;
-  if(token.length + 1 > sizeof(name))
-    return EMSGSIZE;
-
-  snprintf(name, sizeof(name), "%s@%s", service, proxy ? conn->proxy.name :
-           conn->host.name);
-
-  token.value = (void *) name;
-  major_status = gss_import_name(&minor_status,
-                                 &token,
-                                 GSS_C_NT_HOSTBASED_SERVICE,
-                                 server);
-
-  return GSS_ERROR(major_status) ? -1 : 0;
-}
-
-static void
-log_gss_error(struct connectdata *conn, OM_uint32 error_status,
-              const char *prefix)
-{
-  OM_uint32 maj_stat, min_stat;
-  OM_uint32 msg_ctx = 0;
-  gss_buffer_desc status_string;
-  char buf[1024];
-  size_t len;
-
-  snprintf(buf, sizeof(buf), "%s", prefix);
-  len = strlen(buf);
-  do {
-    maj_stat = gss_display_status(&min_stat,
-                                  error_status,
-                                  GSS_C_MECH_CODE,
-                                  GSS_C_NO_OID,
-                                  &msg_ctx,
-                                  &status_string);
-      if(sizeof(buf) > len + status_string.length + 1) {
-        snprintf(buf + len, sizeof(buf) - len,
-                 ": %s", (char*) status_string.value);
-      len += status_string.length;
-    }
-    gss_release_buffer(&min_stat, &status_string);
-  } while(!GSS_ERROR(maj_stat) && msg_ctx != 0);
-
-  infof(conn->data, "%s\n", buf);
-}
-
-/* returning zero (0) means success, everything else is treated as "failure"
-   with no care exactly what the failure was */
-int Curl_input_negotiate(struct connectdata *conn, bool proxy,
-                         const char *header)
+CURLcode Curl_input_negotiate(struct connectdata *conn, bool proxy,
+                              const char *header)
 {
   struct SessionHandle *data = conn->data;
   struct negotiatedata *neg_ctx = proxy?&data->state.proxyneg:
     &data->state.negotiate;
   OM_uint32 major_status, minor_status, discard_st;
+  gss_buffer_desc spn_token = GSS_C_EMPTY_BUFFER;
   gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
   gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
-  int ret;
   size_t len;
   size_t rawlen = 0;
-  CURLcode error;
+  CURLcode result;
 
   if(neg_ctx->context && neg_ctx->status == GSS_S_COMPLETE) {
     /* We finished successfully our part of authentication, but server
      * rejected it (since we're again here). Exit with an error since we
      * can't invent anything better */
     Curl_cleanup_negotiate(data);
-    return -1;
+    return CURLE_LOGIN_DENIED;
   }
 
-  if(neg_ctx->server_name == NULL &&
-      (ret = get_gss_name(conn, proxy, &neg_ctx->server_name)))
-    return ret;
+  if(!neg_ctx->server_name) {
+    /* Generate our SPN */
+    char *spn = Curl_sasl_build_gssapi_spn(
+      proxy ? data->set.str[STRING_PROXY_SERVICE_NAME] :
+      data->set.str[STRING_SERVICE_NAME],
+      proxy ? conn->proxy.name : conn->host.name);
+    if(!spn)
+      return CURLE_OUT_OF_MEMORY;
+
+    /* Populate the SPN structure */
+    spn_token.value = spn;
+    spn_token.length = strlen(spn);
+
+    /* Import the SPN */
+    major_status = gss_import_name(&minor_status, &spn_token,
+                                   GSS_C_NT_HOSTBASED_SERVICE,
+                                   &neg_ctx->server_name);
+    if(GSS_ERROR(major_status)) {
+      Curl_gss_log_error(data, minor_status, "gss_import_name() failed: ");
+
+      free(spn);
+
+      return CURLE_OUT_OF_MEMORY;
+    }
+
+    free(spn);
+  }
 
   header += strlen("Negotiate");
   while(*header && ISSPACE(*header))
     header++;
 
   len = strlen(header);
   if(len > 0) {
-    error = Curl_base64_decode(header,
-                               (unsigned char **)&input_token.value, &rawlen);
-    if(error || rawlen == 0)
-      return -1;
+    result = Curl_base64_decode(header, (unsigned char **)&input_token.value,
+                                &rawlen);
+    if(result)
+      return result;
+
+    if(!rawlen) {
+      infof(data, "Negotiate handshake failure (empty challenge message)\n");
+
+      return CURLE_BAD_CONTENT_ENCODING;
+    }
+
     input_token.length = rawlen;
 
     DEBUGASSERT(input_token.value != NULL);
@@ -151,27 +118,29 @@ int Curl_input_negotiate(struct connectdata *conn, bool proxy,
                                            GSS_C_NO_CHANNEL_BINDINGS,
                                            &input_token,
                                            &output_token,
+                                           TRUE,
                                            NULL);
   Curl_safefree(input_token.value);
 
   neg_ctx->status = major_status;
   if(GSS_ERROR(major_status)) {
     if(output_token.value)
       gss_release_buffer(&discard_st, &output_token);
-    log_gss_error(conn, minor_status, "gss_init_sec_context() failed: ");
-    return -1;
+    Curl_gss_log_error(conn->data, minor_status,
+                       "gss_init_sec_context() failed: ");
+    return CURLE_OUT_OF_MEMORY;
   }
 
   if(!output_token.value || !output_token.length) {
     if(output_token.value)
       gss_release_buffer(&discard_st, &output_token);
-    return -1;
+    return CURLE_OUT_OF_MEMORY;
   }
 
   neg_ctx->output_token = output_token;
-  return 0;
-}
 
+  return CURLE_OK;
+}
 
 CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
 {
@@ -180,18 +149,18 @@ CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
   char *encoded = NULL;
   size_t len = 0;
   char *userp;
-  CURLcode error;
+  CURLcode result;
   OM_uint32 discard_st;
 
-  error = Curl_base64_encode(conn->data,
-                             neg_ctx->output_token.value,
-                             neg_ctx->output_token.length,
-                             &encoded, &len);
-  if(error) {
+  result = Curl_base64_encode(conn->data,
+                              neg_ctx->output_token.value,
+                              neg_ctx->output_token.length,
+                              &encoded, &len);
+  if(result) {
     gss_release_buffer(&discard_st, &neg_ctx->output_token);
     neg_ctx->output_token.value = NULL;
     neg_ctx->output_token.length = 0;
-    return error;
+    return result;
   }
 
   if(!encoded || !len) {
@@ -212,7 +181,7 @@ CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
     conn->allocptr.userpwd = userp;
   }
 
-  Curl_safefree(encoded);
+  free(encoded);
 
   return (userp == NULL) ? CURLE_OUT_OF_MEMORY : CURLE_OK;
 }
@@ -238,6 +207,4 @@ void Curl_cleanup_negotiate(struct SessionHandle *data)
   cleanup(&data->state.proxyneg);
 }
 
-
-#endif
-#endif
+#endif /* HAVE_GSSAPI && !CURL_DISABLE_HTTP && USE_SPNEGO */