@@ -211,18 +211,20 @@ int Curl_gtls_cleanup(void)
   return 1;
 }
 
+#ifndef CURL_DISABLE_VERBOSE_STRINGS
 static void showtime(struct Curl_easy *data,
                      const char *text,
                      time_t stamp)
 {
   struct tm buffer;
   const struct tm *tm = &buffer;
+  char str[96];
   CURLcode result = Curl_gmtime(stamp, &buffer);
   if(result)
     return;
 
-  snprintf(data->state.buffer,
-           BUFSIZE,
+  snprintf(str,
+           sizeof(str),
            "\t %s: %s, %02d %s %4d %02d:%02d:%02d GMT",
            text,
            Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
@@ -232,8 +234,9 @@ static void showtime(struct Curl_easy *data,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec);
-  infof(data, "%s\n", data->state.buffer);
+  infof(data, "%s\n", str);
 }
+#endif
 
 static gnutls_datum_t load_file(const char *file)
 {
@@ -962,8 +965,6 @@ gtls_connect_step3(struct connectdata *conn,
   gnutls_datum_t issuerp;
   char certbuf[256] = ""; /* big enough? */
   size_t size;
-  unsigned int algo;
-  unsigned int bits;
   time_t certclock;
   const char *ptr;
   struct Curl_easy *data = conn->data;
@@ -974,6 +975,8 @@ gtls_connect_step3(struct connectdata *conn,
 #endif
   CURLcode result = CURLE_OK;
 #ifndef CURL_DISABLE_VERBOSE_STRINGS
+  unsigned int algo;
+  unsigned int bits;
   gnutls_protocol_t version = gnutls_protocol_get_version(session);
 #endif
   const char * const hostname = SSL_IS_PROXY() ? conn->http_proxy.host.name :
@@ -1344,6 +1347,7 @@ gtls_connect_step3(struct connectdata *conn,
 
   */
 
+#ifndef CURL_DISABLE_VERBOSE_STRINGS
   /* public key algorithm's parameters */
   algo = gnutls_x509_crt_get_pk_algorithm(x509_cert, &bits);
   infof(data, "\t certificate public key: %s\n",
@@ -1368,12 +1372,13 @@ gtls_connect_step3(struct connectdata *conn,
   gnutls_x509_crt_get_issuer_dn(x509_cert, certbuf, &size);
   infof(data, "\t issuer: %s\n", certbuf);
 
-  gnutls_x509_crt_deinit(x509_cert);
-
   /* compression algorithm (if any) */
   ptr = gnutls_compression_get_name(gnutls_compression_get(session));
   /* the *_get_name() says "NULL" if GNUTLS_COMP_NULL is returned */
   infof(data, "\t compression: %s\n", ptr);
+#endif
+
+  gnutls_x509_crt_deinit(x509_cert);
 
 #ifdef HAS_ALPN
   if(conn->bits.tls_enable_alpn) {