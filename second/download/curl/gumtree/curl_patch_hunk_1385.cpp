 
 /* --- parse FTP server responses --- */
 
 #define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
 			isdigit((int)line[2]) && (' ' == line[3]))
 
+
+int Curl_GetFTPResponse(int sockfd,
+                        char *buf,
+                        struct connectdata *conn,
+                        int *ftpcode)
+{
+  /* Brand new implementation.
+   * We cannot read just one byte per read() and then go back to select()
+   * as it seems that the OpenSSL read() stuff doesn't grok that properly.
+   *
+   * Alas, read as much as possible, split up into lines, use the ending
+   * line in a response or continue reading.
+   */
+
+  int nread;   /* total size read */
+  int perline; /* count bytes per line */
+  bool keepon=TRUE;
+  ssize_t gotbytes;
+  char *ptr;
+  int timeout = 3600; /* default timeout in seconds */
+  struct timeval interval;
+  fd_set rkeepfd;
+  fd_set readfd;
+  struct UrlData *data = conn->data;
+  char *line_start;
+  int code;
+
+#define SELECT_OK      0
+#define SELECT_ERROR   1
+#define SELECT_TIMEOUT 2
+  int error = SELECT_OK;
+
+  if(ftpcode)
+    *ftpcode=0; /* 0 for errors */
+
+  if(data->timeout) {
+    /* if timeout is requested, find out how much remaining time we have */
+    timeout = data->timeout - /* timeout time */
+      (Curl_tvlong(Curl_tvnow()) - Curl_tvlong(conn->now)); /* spent time */
+    if(timeout <=0 ) {
+      failf(data, "Transfer aborted due to timeout");
+      return -SELECT_TIMEOUT; /* already too little time */
+    }
+  }
+
+  FD_ZERO (&readfd);		/* clear it */
+  FD_SET (sockfd, &readfd);     /* read socket */
+
+  /* get this in a backup variable to be able to restore it on each lap in the
+     select() loop */
+  rkeepfd = readfd;
+
+  ptr=buf;
+  line_start = buf;
+
+  nread=0;
+  perline=0;
+  keepon=TRUE;
+
+  while((nread<BUFSIZE) && (keepon && !error)) {
+    readfd = rkeepfd;		   /* set every lap */
+    interval.tv_sec = timeout;
+    interval.tv_usec = 0;
+
+    switch (select (sockfd+1, &readfd, NULL, NULL, &interval)) {
+    case -1: /* select() error, stop reading */
+      error = SELECT_ERROR;
+      failf(data, "Transfer aborted due to select() error");
+      break;
+    case 0: /* timeout */
+      error = SELECT_TIMEOUT;
+      failf(data, "Transfer aborted due to timeout");
+      break;
+    default:
+      /*
+       * This code previously didn't use the kerberos sec_read() code
+       * to read, but when we use Curl_read() it may do so. Do confirm
+       * that this is still ok and then remove this comment!
+       */
+      if(CURLE_OK != Curl_read(conn, sockfd, ptr, BUFSIZE-nread, &gotbytes))
+        keepon = FALSE;
+      else if(gotbytes <= 0) {
+        keepon = FALSE;
+        error = SELECT_ERROR;
+        failf(data, "Connection aborted");
+      }
+      else {
+        /* we got a whole chunk of data, which can be anything from one
+         * byte to a set of lines and possible just a piece of the last
+         * line */
+        int i;
+
+        nread += gotbytes;
+        for(i=0; i< gotbytes; ptr++, i++) {
+          perline++;
+          if(*ptr=='\n') {
+            /* a newline is CRLF in ftp-talk, so the CR is ignored as
+               the line isn't really terminated until the LF comes */
+
+            /* output debug output if that is requested */
+            if(data->bits.verbose) {
+              fputs("< ", data->err);
+              fwrite(line_start, 1, perline, data->err);
+              /* no need to output LF here, it is part of the data */
+            }
+
+            if(perline>3 && lastline(line_start)) {
+              /* This is the end of the last line, copy the last
+               * line to the start of the buffer and zero terminate,
+               * for old times sake (and krb4)! */
+              char *moo;
+              int i;
+              for(moo=line_start, i=0; moo<ptr; moo++, i++)
+                buf[i] = *moo;
+              moo[i]=0; /* zero terminate */
+              keepon=FALSE;
+              break;
+            }
+            perline=0; /* line starts over here */
+            line_start = ptr+1;
+          }
+        }
+      }
+      break;
+    } /* switch */
+  } /* while there's buffer left and loop is requested */
+
+  if(!error)
+    code = atoi(buf);
+
+#if KRB4
+  /* handle the security-oriented responses 6xx ***/
+  /* FIXME: some errorchecking perhaps... ***/
+  switch(code) {
+  case 631:
+    sec_read_msg(conn, buf, prot_safe);
+    break;
+  case 632:
+    sec_read_msg(conn, buf, prot_private);
+    break;
+  case 633:
+    sec_read_msg(conn, buf, prot_confidential);
+    break;
+  default:
+    /* normal ftp stuff we pass through! */
+    break;
+  }
+#endif
+
+  if(error)
+    return -error;
+
+  if(ftpcode)
+    *ftpcode=code; /* return the initial number like this */
+
+  return nread; /* total amount of bytes read */
+}
+
+#if 0
 /*
  * We allow the ftpcode pointer to be NULL if no reply integer is wanted
  */
 
 int Curl_GetFTPResponse(int sockfd, char *buf,
                         struct connectdata *conn,
                         int *ftpcode)
 {
   int nread;
   ssize_t keepon=TRUE;
+  size_t got;
   char *ptr;
   int timeout = 3600; /* in seconds */
   struct timeval interval;
   fd_set rkeepfd;
   fd_set readfd;
   struct UrlData *data = conn->data;
