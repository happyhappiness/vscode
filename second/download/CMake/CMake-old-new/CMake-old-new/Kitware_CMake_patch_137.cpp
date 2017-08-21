@@ -46,10 +46,9 @@
 #include "openssl.h"
 #include "connect.h"
 #include "slist.h"
-#include "strequal.h"
 #include "select.h"
 #include "vtls.h"
-#include "rawstr.h"
+#include "strcase.h"
 #include "hostcheck.h"
 #include "curl_printf.h"
 
@@ -95,11 +94,6 @@
 
 #if (OPENSSL_VERSION_NUMBER >= 0x10000000L)
 #define HAVE_ERR_REMOVE_THREAD_STATE 1
-#if (OPENSSL_VERSION_NUMBER >= 0x10100004L) && \
-  !defined(LIBRESSL_VERSION_NUMBER)
-/* OpenSSL 1.1.0 deprecates the function */
-#define HAVE_ERR_REMOVE_THREAD_STATE_DEPRECATED 1
-#endif
 #endif
 
 #if !defined(HAVE_SSLV2_CLIENT_METHOD) || \
@@ -110,11 +104,28 @@
 
 #if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && /* OpenSSL 1.1.0+ */ \
   !defined(LIBRESSL_VERSION_NUMBER)
-#define SSLeay_add_ssl_algorithms() SSL_library_init()
 #define SSLEAY_VERSION_NUMBER OPENSSL_VERSION_NUMBER
 #define HAVE_X509_GET0_EXTENSIONS 1 /* added in 1.1.0 -pre1 */
 #define HAVE_OPAQUE_EVP_PKEY 1 /* since 1.1.0 -pre3 */
 #define HAVE_OPAQUE_RSA_DSA_DH 1 /* since 1.1.0 -pre5 */
+#define CONST_EXTS const
+#define CONST_ASN1_BIT_STRING const
+#define HAVE_ERR_REMOVE_THREAD_STATE_DEPRECATED 1
+#else
+/* For OpenSSL before 1.1.0 */
+#define ASN1_STRING_get0_data(x) ASN1_STRING_data(x)
+#define X509_get0_notBefore(x) X509_get_notBefore(x)
+#define X509_get0_notAfter(x) X509_get_notAfter(x)
+#define CONST_EXTS /* nope */
+#define CONST_ASN1_BIT_STRING /* nope */
+#ifdef LIBRESSL_VERSION_NUMBER
+static unsigned long OpenSSL_version_num(void)
+{
+  return LIBRESSL_VERSION_NUMBER;
+}
+#else
+#define OpenSSL_version_num() SSLeay()
+#endif
 #endif
 
 #if (OPENSSL_VERSION_NUMBER >= 0x1000200fL) && /* 1.0.2 or later */ \
@@ -278,13 +289,13 @@ static int do_file_type(const char *type)
 {
   if(!type || !type[0])
     return SSL_FILETYPE_PEM;
-  if(Curl_raw_equal(type, "PEM"))
+  if(strcasecompare(type, "PEM"))
     return SSL_FILETYPE_PEM;
-  if(Curl_raw_equal(type, "DER"))
+  if(strcasecompare(type, "DER"))
     return SSL_FILETYPE_ASN1;
-  if(Curl_raw_equal(type, "ENG"))
+  if(strcasecompare(type, "ENG"))
     return SSL_FILETYPE_ENGINE;
-  if(Curl_raw_equal(type, "P12"))
+  if(strcasecompare(type, "P12"))
     return SSL_FILETYPE_PKCS12;
   return -1;
 }
@@ -711,6 +722,10 @@ int Curl_ossl_init(void)
                          CONF_MFLAGS_DEFAULT_SECTION|
                          CONF_MFLAGS_IGNORE_MISSING_FILE);
 
+#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && \
+    !defined(LIBRESSL_VERSION_NUMBER)
+  /* OpenSSL 1.1.0+ takes care of initialization itself */
+#else
   /* Lets get nice error messages */
   SSL_load_error_strings();
 
@@ -719,13 +734,19 @@ int Curl_ossl_init(void)
     return 0;
 
   OpenSSL_add_all_algorithms();
+#endif
 
   return 1;
 }
 
 /* Global cleanup */
 void Curl_ossl_cleanup(void)
 {
+#if (OPENSSL_VERSION_NUMBER >= 0x10100000L) && \
+    !defined(LIBRESSL_VERSION_NUMBER)
+  /* OpenSSL 1.1 deprecates all these cleanup functions and
+     turns them into no-ops in OpenSSL 1.0 compatibility mode */
+#else
   /* Free ciphers and digests lists */
   EVP_cleanup();
 
@@ -734,18 +755,11 @@ void Curl_ossl_cleanup(void)
   ENGINE_cleanup();
 #endif
 
-#ifdef HAVE_CRYPTO_CLEANUP_ALL_EX_DATA
-  /* Free OpenSSL ex_data table */
-  CRYPTO_cleanup_all_ex_data();
-#endif
-
   /* Free OpenSSL error strings */
   ERR_free_strings();
 
   /* Free thread local error state, destroying hash upon zero refcount */
-#ifdef HAVE_ERR_REMOVE_THREAD_STATE_DEPRECATED
-
-#elif defined(HAVE_ERR_REMOVE_THREAD_STATE)
+#ifdef HAVE_ERR_REMOVE_THREAD_STATE
   ERR_remove_thread_state(NULL);
 #else
   ERR_remove_state(0);
@@ -757,6 +771,7 @@ void Curl_ossl_cleanup(void)
 #ifdef HAVE_SSL_COMP_FREE_COMPRESSION_METHODS
   SSL_COMP_free_compression_methods();
 #endif
+#endif
 }
 
 /*
@@ -949,8 +964,8 @@ int Curl_ossl_shutdown(struct connectdata *conn, int sockindex)
   if(connssl->handle) {
     buffsize = (int)sizeof(buf);
     while(!done) {
-      int what = Curl_socket_ready(conn->sock[sockindex],
-                                   CURL_SOCKET_BAD, SSL_SHUTDOWN_TIMEOUT);
+      int what = SOCKET_READABLE(conn->sock[sockindex],
+                                 SSL_SHUTDOWN_TIMEOUT);
       if(what > 0) {
         ERR_clear_error();
 
@@ -1043,6 +1058,14 @@ void Curl_ossl_close_all(struct Curl_easy *data)
 #else
   (void)data;
 #endif
+#if !defined(HAVE_ERR_REMOVE_THREAD_STATE_DEPRECATED) && \
+  defined(HAVE_ERR_REMOVE_THREAD_STATE)
+  /* OpenSSL 1.0.1 and 1.0.2 build an error queue that is stored per-thread
+     so we need to clean it here in case the thread will be killed. All OpenSSL
+     code should extract the error in association with the error so clearing
+     this queue here should be harmless at worst. */
+  ERR_remove_thread_state(NULL);
+#endif
 }
 
 /* ====================================================== */
@@ -1083,6 +1106,7 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
 #endif
   CURLcode result = CURLE_OK;
   bool dNSName = FALSE; /* if a dNSName field exists in the cert */
+  bool iPAddress = FALSE; /* if a iPAddress field exists in the cert */
 
 #ifdef ENABLE_IPV6
   if(conn->bits.ipv6_ip &&
@@ -1115,15 +1139,15 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
       /* get a handle to alternative name number i */
       const GENERAL_NAME *check = sk_GENERAL_NAME_value(altnames, i);
 
-      /* If a subjectAltName extension of type dNSName is present, that MUST
-         be used as the identity. / RFC2818 section 3.1 */
       if(check->type == GEN_DNS)
         dNSName = TRUE;
+      else if(check->type == GEN_IPADD)
+        iPAddress = TRUE;
 
       /* only check alternatives of the same type the target is */
       if(check->type == target) {
         /* get data and length */
-        const char *altptr = (char *)ASN1_STRING_data(check->d.ia5);
+        const char *altptr = (char *)ASN1_STRING_get0_data(check->d.ia5);
         size_t altlen = (size_t) ASN1_STRING_length(check->d.ia5);
 
         switch(target) {
@@ -1164,18 +1188,14 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
     }
     GENERAL_NAMES_free(altnames);
 
-    if(dnsmatched || (!dNSName && ipmatched)) {
-      /* count as a match if the dnsname matched or if there was no dnsname
-         fields at all AND there was an IP field match */
+    if(dnsmatched || ipmatched)
       matched = TRUE;
-    }
   }
 
   if(matched)
     /* an alternative name matched */
     ;
-  else if(dNSName) {
-    /* an dNSName field existed, but didn't match and then we MUST fail */
+  else if(dNSName || iPAddress) {
     infof(data, " subjectAltName does not match %s\n", conn->host.dispname);
     failf(data, "SSL: no alternative certificate subject name matches "
           "target host name '%s'", conn->host.dispname);
@@ -1215,7 +1235,7 @@ static CURLcode verifyhost(struct connectdata *conn, X509 *server_cert)
           if(j >= 0) {
             peer_CN = OPENSSL_malloc(j+1);
             if(peer_CN) {
-              memcpy(peer_CN, ASN1_STRING_data(tmp), j);
+              memcpy(peer_CN, ASN1_STRING_get0_data(tmp), j);
               peer_CN[j] = '\0';
             }
           }
@@ -2178,6 +2198,7 @@ static CURLcode ossl_connect_step2(struct connectdata *conn, int sockindex)
 
         lerr = SSL_get_verify_result(connssl->handle);
         if(lerr != X509_V_OK) {
+          data->set.ssl.certverifyresult = lerr;
           snprintf(error_buffer, sizeof(error_buffer),
                    "SSL certificate problem: %s",
                    X509_verify_cert_error_string(lerr));
@@ -2309,7 +2330,7 @@ do {                              \
 
 static int X509V3_ext(struct Curl_easy *data,
                       int certnum,
-                      STACK_OF(X509_EXTENSION) *exts)
+                      CONST_EXTS STACK_OF(X509_EXTENSION) *exts)
 {
   int i;
   size_t j;
@@ -2391,7 +2412,7 @@ static CURLcode get_cert_chain(struct connectdata *conn,
     EVP_PKEY *pubkey=NULL;
     int j;
     char *ptr;
-    ASN1_BIT_STRING *psig = NULL;
+    CONST_ASN1_BIT_STRING ASN1_BIT_STRING *psig = NULL;
 
     X509_NAME_print_ex(mem, X509_get_subject_name(x), 0, XN_FLAG_ONELINE);
     push_certinfo("Subject", i);
@@ -2411,7 +2432,7 @@ static CURLcode get_cert_chain(struct connectdata *conn,
 
 #if defined(HAVE_X509_GET0_SIGNATURE) && defined(HAVE_X509_GET0_EXTENSIONS)
     {
-      X509_ALGOR *palg = NULL;
+      const X509_ALGOR *palg = NULL;
       ASN1_STRING *a = ASN1_STRING_new();
       if(a) {
         X509_get0_signature(&psig, &palg, x);
@@ -2442,10 +2463,10 @@ static CURLcode get_cert_chain(struct connectdata *conn,
     }
 #endif
 
-    ASN1_TIME_print(mem, X509_get_notBefore(x));
+    ASN1_TIME_print(mem, X509_get0_notBefore(x));
     push_certinfo("Start date", i);
 
-    ASN1_TIME_print(mem, X509_get_notAfter(x));
+    ASN1_TIME_print(mem, X509_get0_notAfter(x));
     push_certinfo("Expire date", i);
 
     pubkey = X509_get_pubkey(x);
@@ -2629,7 +2650,7 @@ static CURLcode pkp_pin_peer_pubkey(struct Curl_easy *data, X509* cert,
       break; /* failed */
 
     /* https://www.openssl.org/docs/crypto/buffer.html */
-    buff1 = temp = OPENSSL_malloc(len1);
+    buff1 = temp = malloc(len1);
     if(!buff1)
       break; /* failed */
 
@@ -2652,7 +2673,7 @@ static CURLcode pkp_pin_peer_pubkey(struct Curl_easy *data, X509* cert,
 
   /* https://www.openssl.org/docs/crypto/buffer.html */
   if(buff1)
-    OPENSSL_free(buff1);
+    free(buff1);
 
   return result;
 }
@@ -2698,12 +2719,12 @@ static CURLcode servercert(struct connectdata *conn,
                          buffer, BUFSIZE);
   infof(data, " subject: %s\n", rc?"[NONE]":buffer);
 
-  ASN1_TIME_print(mem, X509_get_notBefore(connssl->server_cert));
+  ASN1_TIME_print(mem, X509_get0_notBefore(connssl->server_cert));
   len = BIO_get_mem_data(mem, (char **) &ptr);
   infof(data, " start date: %.*s\n", len, ptr);
   rc = BIO_reset(mem);
 
-  ASN1_TIME_print(mem, X509_get_notAfter(connssl->server_cert));
+  ASN1_TIME_print(mem, X509_get0_notAfter(connssl->server_cert));
   len = BIO_get_mem_data(mem, (char **) &ptr);
   infof(data, " expire date: %.*s\n", len, ptr);
   rc = BIO_reset(mem);
@@ -2945,7 +2966,8 @@ static CURLcode ossl_connect_common(struct connectdata *conn,
       curl_socket_t readfd = ssl_connect_2_reading==
         connssl->connecting_state?sockfd:CURL_SOCKET_BAD;
 
-      what = Curl_socket_ready(readfd, writefd, nonblocking?0:timeout_ms);
+      what = Curl_socket_check(readfd, CURL_SOCKET_BAD, writefd,
+                               nonblocking?0:timeout_ms);
       if(what < 0) {
         /* fatal error */
         failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
@@ -3142,7 +3164,7 @@ size_t Curl_ossl_version(char *buffer, size_t size)
   unsigned long ssleay_value;
   sub[2]='\0';
   sub[1]='\0';
-  ssleay_value=SSLeay();
+  ssleay_value=OpenSSL_version_num();
   if(ssleay_value < 0x906000) {
     ssleay_value=SSLEAY_VERSION_NUMBER;
     sub[0]='\0';