#define infof Curl_infof

#endif /* CURL_DISABLE_VERBOSE_STRINGS */

#define failf Curl_failf

#define CLIENTWRITE_BODY   1
#define CLIENTWRITE_HEADER 2
#define CLIENTWRITE_BOTH   (CLIENTWRITE_BODY|CLIENTWRITE_HEADER)

CURLcode Curl_client_write(struct connectdata *conn, int type, char *ptr,
                           size_t len);

void Curl_read_rewind(struct connectdata *conn,
                      size_t extraBytesRead);

/* internal read-function, does plain socket only */
int Curl_read_plain(curl_socket_t sockfd,
                    char *buf,
                    size_t bytesfromsocket,
                    ssize_t *n);

