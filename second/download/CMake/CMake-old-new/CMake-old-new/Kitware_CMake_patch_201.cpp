@@ -11,7 +11,7 @@
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -26,8 +26,8 @@
 
 CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *,
                     const char *fmt, ...);
-void Curl_infof(struct SessionHandle *, const char *fmt, ...);
-void Curl_failf(struct SessionHandle *, const char *fmt, ...);
+void Curl_infof(struct Curl_easy *, const char *fmt, ...);
+void Curl_failf(struct Curl_easy *, const char *fmt, ...);
 
 #if defined(CURL_DISABLE_VERBOSE_STRINGS)
 
@@ -84,7 +84,7 @@ CURLcode Curl_write_plain(struct connectdata *conn,
                           ssize_t *written);
 
 /* the function used to output verbose information */
-int Curl_debug(struct SessionHandle *handle, curl_infotype type,
+int Curl_debug(struct Curl_easy *handle, curl_infotype type,
                char *data, size_t size,
                struct connectdata *conn);
 