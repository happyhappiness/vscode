#define failf Curl_failf

#define CLIENTWRITE_BODY   (1<<0)
#define CLIENTWRITE_HEADER (1<<1)
#define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)

CURLcode Curl_client_chop_write(struct connectdata *conn, int type, char *ptr,
                                size_t len) WARN_UNUSED_RESULT;
CURLcode Curl_client_write(struct connectdata *conn, int type, char *ptr,
                           size_t len) WARN_UNUSED_RESULT;

/* internal read-function, does plain socket only */
CURLcode Curl_read_plain(curl_socket_t sockfd,
                         char *buf,
                         size_t bytesfromsocket,
                         ssize_t *n);
