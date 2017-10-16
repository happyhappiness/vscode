  * furnished to do so, under the terms of the MPL or the MIT/X-derivate
  * licenses. You may pick one of these licenses.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
- * $Id: sendf.h,v 1.8 2001/01/03 09:29:34 bagder Exp $
+ * $Id: sendf.h,v 1.10 2001/01/25 12:20:30 bagder Exp $
  *****************************************************************************/
 
-size_t ftpsendf(int fd, struct connectdata *, char *fmt, ...);
-size_t sendf(int fd, struct UrlData *, char *fmt, ...);
-size_t ssend(int fd, struct connectdata *, void *fmt, size_t len);
-void infof(struct UrlData *, char *fmt, ...);
-void failf(struct UrlData *, char *fmt, ...);
+size_t Curl_sendf(int fd, struct connectdata *, char *fmt, ...);
+void Curl_infof(struct UrlData *, char *fmt, ...);
+void Curl_failf(struct UrlData *, char *fmt, ...);
+
+#define infof Curl_infof
+#define failf Curl_failf
 
 struct send_buffer {
   char *buffer;
   long size_max;
   long size_used;
 };
 typedef struct send_buffer send_buffer;
 
 #define CLIENTWRITE_BODY   1
 #define CLIENTWRITE_HEADER 2
 #define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)
 
-CURLcode client_write(struct UrlData *data, int type, char *ptr,
-                      size_t len);
-send_buffer *add_buffer_init(void);
-CURLcode add_buffer(send_buffer *in, void *inptr, size_t size);
-CURLcode add_bufferf(send_buffer *in, char *fmt, ...);
-size_t add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in);
+CURLcode Curl_client_write(struct UrlData *data, int type, char *ptr,
+                           size_t len);
 
+/* internal read-function, does plain socket, SSL and krb4 */
+CURLcode Curl_read(struct connectdata *conn, int sockfd,
+                   char *buf, size_t buffersize,
+                   size_t *n);
+/* internal write-function, does plain socket, SSL and krb4 */
+CURLcode Curl_write(struct connectdata *conn, int sockfd,
+                    void *mem, size_t len,
+                    size_t *written);
 
 #endif
