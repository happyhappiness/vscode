   if(ftpcode)
     *ftpcode=code; /* return the initial number like this */
 
   return nread; /* total amount of bytes read */
 }
 
-#if 0
-/*
- * We allow the ftpcode pointer to be NULL if no reply integer is wanted
- */
-
-int Curl_GetFTPResponse(int sockfd, char *buf,
-                        struct connectdata *conn,
-                        int *ftpcode)
-{
-  int nread;
-  ssize_t keepon=TRUE;
-  size_t got;
-  char *ptr;
-  int timeout = 3600; /* in seconds */
-  struct timeval interval;
-  fd_set rkeepfd;
-  fd_set readfd;
-  struct UrlData *data = conn->data;
-
-#define SELECT_OK      0
-#define SELECT_ERROR   1
-#define SELECT_TIMEOUT 2
-  int error = SELECT_OK;
-
-  if(ftpcode)
-    *ftpcode=0; /* 0 for errors */
-
-  if(data->timeout) {
-    /* if timeout is requested, find out how much remaining time we have */
-    timeout = data->timeout - /* timeout time */
-      (Curl_tvlong(Curl_tvnow()) - Curl_tvlong(conn->now)); /* spent time */
-    if(timeout <=0 ) {
-      failf(data, "Transfer aborted due to timeout");
-      return -SELECT_TIMEOUT; /* already too little time */
-    }
-  }
-
-  FD_ZERO (&readfd);		/* clear it */
-  FD_SET (sockfd, &readfd);     /* read socket */
-
-  /* get this in a backup variable to be able to restore it on each lap in the
-     select() loop */
-  rkeepfd = readfd;
-
-  do {
-    ptr=buf;
-
-    /* get us a full line, terminated with a newline */
-    nread=0;
-    keepon=TRUE;
-    while((nread<BUFSIZE) && (keepon && !error)) {
-      readfd = rkeepfd;		   /* set every lap */
-      interval.tv_sec = timeout;
-      interval.tv_usec = 0;
-
-      switch (select (sockfd+1, &readfd, NULL, NULL, &interval)) {
-      case -1: /* select() error, stop reading */
-        error = SELECT_ERROR;
-        failf(data, "Transfer aborted due to select() error");
-        break;
-      case 0: /* timeout */
-        error = SELECT_TIMEOUT;
-        failf(data, "Transfer aborted due to timeout");
-        break;
-      default:
-        /*
-         * This code previously didn't use the kerberos sec_read() code
-         * to read, but when we use Curl_read() it may do so. Do confirm
-         * that this is still ok and then remove this comment!
-         */
-        if(CURLE_OK != Curl_read(conn, sockfd, ptr, 1, &keepon))
-          keepon = FALSE;
-        else if(keepon <= 0) {
-          error = SELECT_ERROR;
-          failf(data, "Connection aborted");
-        }
-        else if ((*ptr == '\n') || (*ptr == '\r'))
-          keepon = FALSE;
-      }
-      if(keepon) {
-        nread++;
-        ptr++;
-      }
-    }
-    *ptr=0; /* zero terminate */
-
-#if KRB4
-    { /* handle the security-oriented responses 6xx ***/
-      /* FIXME: some errorchecking perhaps... ***/
-      if(strncmp(buf, "631", 3) == 0)
-        sec_read_msg(conn, buf, prot_safe);
-      else if(strncmp(buf, "632", 3) == 0)
-        sec_read_msg(conn, buf, prot_private);
-      else if(strncmp(buf, "633", 3) == 0)
-        sec_read_msg(conn, buf, prot_confidential);
-      nread = strlen(buf);
-    }
-#endif
-
-    if(data->bits.verbose && buf[0]) {
-      fputs("< ", data->err);
-      fwrite(buf, 1, nread, data->err);
-      fputs("\n", data->err);
-    }
-  } while(!error &&
-	  (nread<4 || !lastline(buf)) );
-  
-  if(error)
-    return -error;
-
-  if(ftpcode)
-    *ftpcode=atoi(buf); /* return the initial number like this */
-
-  return nread;
-}
-#endif
-
 /* -- who are we? -- */
-char *Curl_getmyhost(char *buf, int buf_size)
+static char *getmyhost(char *buf, int buf_size)
 {
 #if defined(HAVE_GETHOSTNAME)
   gethostname(buf, buf_size);
 #elif defined(HAVE_UNAME)
   struct utsname ugnm;
   strncpy(buf, uname(&ugnm) < 0 ? "localhost" : ugnm.nodename, buf_size - 1);
