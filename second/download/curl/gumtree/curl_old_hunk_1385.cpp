
/* --- parse FTP server responses --- */

#define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
			isdigit((int)line[2]) && (' ' == line[3]))

/*
 * We allow the ftpcode pointer to be NULL if no reply integer is wanted
 */

int Curl_GetFTPResponse(int sockfd, char *buf,
                        struct connectdata *conn,
                        int *ftpcode)
{
  int nread;
  ssize_t keepon=TRUE;
  char *ptr;
  int timeout = 3600; /* in seconds */
  struct timeval interval;
  fd_set rkeepfd;
  fd_set readfd;
  struct UrlData *data = conn->data;
