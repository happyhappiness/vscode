 #define failf Curl_failf
 
 #define CLIENTWRITE_BODY   1
 #define CLIENTWRITE_HEADER 2
 #define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)
 
-CURLcode Curl_client_write(struct SessionHandle *data, int type, char *ptr,
+CURLcode Curl_client_write(struct connectdata *conn, int type, char *ptr,
                            size_t len);
 
+void Curl_read_rewind(struct connectdata *conn,
+                      size_t extraBytesRead);
+
 /* internal read-function, does plain socket, SSL and krb4 */
 int Curl_read(struct connectdata *conn, curl_socket_t sockfd,
               char *buf, size_t buffersize,
               ssize_t *n);
 /* internal write-function, does plain socket, SSL and krb4 */
 CURLcode Curl_write(struct connectdata *conn,
