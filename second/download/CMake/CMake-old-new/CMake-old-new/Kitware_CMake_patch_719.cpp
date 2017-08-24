@@ -173,9 +173,9 @@ static CURLcode AllowServerConnect(struct SessionHandle *data,
  * response and extract the relevant return code for the invoking function.
  */
 
-int Curl_GetFTPResponse(char *buf,
-                        struct connectdata *conn,
-                        int *ftpcode)
+CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
+                             struct connectdata *conn,
+                             int *ftpcode) /* return the ftp-code */
 {
   /* Brand new implementation.
    * We cannot read just one byte per read() and then go back to select()
@@ -185,28 +185,21 @@ int Curl_GetFTPResponse(char *buf,
    * line in a response or continue reading.  */
 
   int sockfd = conn->firstsocket;
-  int nread;   /* total size read */
   int perline; /* count bytes per line */
   bool keepon=TRUE;
   ssize_t gotbytes;
   char *ptr;
-  int timeout = 3600; /* default timeout in seconds */
+  int timeout;              /* timeout in seconds */
   struct timeval interval;
   fd_set rkeepfd;
   fd_set readfd;
   struct SessionHandle *data = conn->data;
   char *line_start;
-  int code=0; /* default "error code" to return */
-
-#define SELECT_OK       0
-#define SELECT_ERROR    1 /* select() problems */
-#define SELECT_TIMEOUT  2 /* took too long */
-#define SELECT_MEMORY   3 /* no available memory */
-#define SELECT_CALLBACK 4 /* aborted by callback */
-
-  int error = SELECT_OK;
-
+  int code=0; /* default ftp "error code" to return */
+  char *buf = data->state.buffer;
+  CURLcode result = CURLE_OK;
   struct FTP *ftp = conn->proto.ftp;
+  struct timeval now = Curl_tvnow();
 
   if (ftpcode)
     *ftpcode = 0; /* 0 for errors */
@@ -221,20 +214,25 @@ int Curl_GetFTPResponse(char *buf,
   ptr=buf;
   line_start = buf;
 
-  nread=0;
+  *nreadp=0;
   perline=0;
   keepon=TRUE;
 
-  while((nread<BUFSIZE) && (keepon && !error)) {
+  while((*nreadp<BUFSIZE) && (keepon && !result)) {
     /* check and reset timeout value every lap */
-    if(data->set.timeout) {
+    if(data->set.timeout)
       /* if timeout is requested, find out how much remaining time we have */
       timeout = data->set.timeout - /* timeout time */
         Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
-      if(timeout <=0 ) {
-        failf(data, "Transfer aborted due to timeout");
-        return -SELECT_TIMEOUT; /* already too little time */
-      }
+    else
+      /* Even without a requested timeout, we only wait response_time
+         seconds for the full response to arrive before we bail out */
+      timeout = ftp->response_time -
+        Curl_tvdiff(Curl_tvnow(), now)/1000; /* spent time */
+
+    if(timeout <=0 ) {
+      failf(data, "Transfer aborted due to timeout");
+      return CURLE_OPERATION_TIMEDOUT; /* already too little time */
     }
 
     if(!ftp->cache) {
@@ -244,19 +242,18 @@ int Curl_GetFTPResponse(char *buf,
 
       switch (select (sockfd+1, &readfd, NULL, NULL, &interval)) {
       case -1: /* select() error, stop reading */
-        error = SELECT_ERROR;
-        failf(data, "Transfer aborted due to select() error");
+        result = CURLE_RECV_ERROR;
+        failf(data, "Transfer aborted due to select() error: %d", errno);
         break;
       case 0: /* timeout */
-        error = SELECT_TIMEOUT;
+        result = CURLE_OPERATION_TIMEDOUT;
         failf(data, "Transfer aborted due to timeout");
         break;
       default:
-        error = SELECT_OK;
         break;
       }
     }
-    if(SELECT_OK == error) {
+    if(CURLE_OK == result) {
       /*
        * This code previously didn't use the kerberos sec_read() code
        * to read, but when we use Curl_read() it may do so. Do confirm
@@ -272,8 +269,7 @@ int Curl_GetFTPResponse(char *buf,
         ftp->cache_size = 0; /* zero the size just in case */
       }
       else {
-        int res = Curl_read(conn, sockfd, ptr,
-                            BUFSIZE-nread, &gotbytes);
+        int res = Curl_read(conn, sockfd, ptr, BUFSIZE-*nreadp, &gotbytes);
         if(res < 0)
           /* EWOULDBLOCK */
           continue; /* go looping again */
@@ -286,7 +282,7 @@ int Curl_GetFTPResponse(char *buf,
         ;
       else if(gotbytes <= 0) {
         keepon = FALSE;
-        error = SELECT_ERROR;
+        result = CURLE_RECV_ERROR;
         failf(data, "Connection aborted");
       }
       else {
@@ -295,7 +291,7 @@ int Curl_GetFTPResponse(char *buf,
          * line */
         int i;
 
-        nread += gotbytes;
+        *nreadp += gotbytes;
         for(i = 0; i < gotbytes; ptr++, i++) {
           perline++;
           if(*ptr=='\n') {
@@ -315,7 +311,7 @@ int Curl_GetFTPResponse(char *buf,
             result = Curl_client_write(data, CLIENTWRITE_HEADER,
                                        line_start, perline);
             if(result)
-              return -SELECT_CALLBACK;
+              return result;
                                        
 #define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
                         isdigit((int)line[2]) && (' ' == line[3]))
@@ -350,13 +346,13 @@ int Curl_GetFTPResponse(char *buf,
           if(ftp->cache)
             memcpy(ftp->cache, line_start, ftp->cache_size);
           else
-            return -SELECT_MEMORY; /**BANG**/
+            return CURLE_OUT_OF_MEMORY; /**BANG**/
         }
       } /* there was data */
     } /* if(no error) */
   } /* while there's buffer left and loop is requested */
 
-  if(!error)
+  if(!result)
     code = atoi(buf);
 
 #ifdef KRB4
@@ -378,13 +374,10 @@ int Curl_GetFTPResponse(char *buf,
   }
 #endif
 
-  if(error)
-    return -error;
-
   if(ftpcode)
     *ftpcode=code; /* return the initial number like this */
 
-  return nread; /* total amount of bytes read */
+  return result;
 }
 
 /*
@@ -417,6 +410,7 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
   /* no need to duplicate them, the data struct won't change */
   ftp->user = data->state.user;
   ftp->passwd = data->state.passwd;
+  ftp->response_time = 3600; /* set default response time-out */
 
   if (data->set.tunnel_thru_httpproxy) {
     /* We want "seamless" FTP operations through HTTP proxy tunnel */
@@ -436,9 +430,9 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
 
 
   /* The first thing we do is wait for the "220*" line: */
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
 
   if(ftpcode != 220) {
     failf(data, "This doesn't seem like a nice ftp-server response");
@@ -467,9 +461,9 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
   FTPSENDF(conn, "USER %s", ftp->user);
 
   /* wait for feedback */
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
 
   if(ftpcode == 530) {
     /* 530 User ... access denied
@@ -481,9 +475,9 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     /* 331 Password required for ...
        (the server requires to send the user's password too) */
     FTPSENDF(conn, "PASS %s", ftp->passwd);
-    nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-    if(nread < 0)
-      return CURLE_OPERATION_TIMEOUTED;
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if(result)
+      return result;
 
     if(ftpcode == 530) {
       /* 530 Login incorrect.
@@ -516,8 +510,11 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     /* we may need to issue a KAUTH here to have access to the files
      * do it if user supplied a password
      */
-    if(data->state.passwd && *data->state.passwd)
-      Curl_krb_kauth(conn);
+    if(data->state.passwd && *data->state.passwd) {
+      result = Curl_krb_kauth(conn);
+      if(result)
+        return result;
+    }
 #endif
   }
   else {
@@ -529,9 +526,9 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
   FTPSENDF(conn, "PWD", NULL);
 
   /* wait for feedback */
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
 
   if(ftpcode == 257) {
     char *dir = (char *)malloc(nread+1);
@@ -544,7 +541,7 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
        The directory name can contain any character; embedded double-quotes
        should be escaped by double-quotes (the "quote-doubling" convention).
     */
-    if('\"' == *ptr) {
+    if(dir && ('\"' == *ptr)) {
       /* it started good */
       ptr++;
       while(ptr && *ptr) {
@@ -570,6 +567,8 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     }
     else {
       /* couldn't get the path */
+      free(dir);
+      infof(data, "Failed to figure out path\n");
     }
 
   }
@@ -594,7 +593,6 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
   struct SessionHandle *data = conn->data;
   struct FTP *ftp = conn->proto.ftp;
   ssize_t nread;
-  char *buf = data->state.buffer; /* this is our buffer */
   int ftpcode;
   CURLcode result=CURLE_OK;
 
@@ -633,11 +631,24 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
   conn->secondarysocket = -1;
 
   if(!ftp->no_transfer) {
-    /* now let's see what the server says about the transfer we just
-       performed: */
-    nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-    if(nread < 0)
-      return CURLE_OPERATION_TIMEOUTED;
+    /* Let's see what the server says about the transfer we just performed,
+       but lower the timeout as sometimes this connection has died while 
+       the data has been transfered. This happens when doing through NATs
+       etc that abandon old silent connections.
+    */
+    ftp->response_time = 60; /* give it only a minute for now */
+
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+
+    ftp->response_time = 3600; /* set this back to one hour waits */
+  
+    if(!nread && (CURLE_OPERATION_TIMEDOUT == result)) {
+      failf(data, "control connection looks dead");
+      return result;
+    }
+
+    if(result)
+      return result;
 
     if(!ftp->dont_check) {
       /* 226 Transfer complete, 250 Requested file action okay, completed. */
@@ -680,9 +691,9 @@ CURLcode ftp_sendquote(struct connectdata *conn, struct curl_slist *quote)
     if (item->data) {
       FTPSENDF(conn, "%s", item->data);
 
-      nread = Curl_GetFTPResponse(conn->data->state.buffer, conn, &ftpcode);
-      if (nread < 0)
-        return CURLE_OPERATION_TIMEOUTED;
+      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+      if (result)
+        return result;
 
       if (ftpcode >= 400) {
         failf(conn->data, "QUOT string not accepted: %s", item->data);
@@ -711,9 +722,9 @@ CURLcode ftp_cwd(struct connectdata *conn, char *path)
   CURLcode result;
   
   FTPSENDF(conn, "CWD %s", path);
-  nread = Curl_GetFTPResponse(conn->data->state.buffer, conn, &ftpcode);
-  if (nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if (result)
+    return result;
 
   if (ftpcode != 250) {
     failf(conn->data, "Couldn't cd to %s", path);
@@ -741,26 +752,34 @@ CURLcode ftp_getfiletime(struct connectdata *conn, char *file)
      again a grey area as the MDTM is not kosher RFC959 */
   FTPSENDF(conn, "MDTM %s", file);
 
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
 
-  if(ftpcode == 213) {
-    /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the
-       last .sss part is optional and means fractions of a second */
-    int year, month, day, hour, minute, second;
-    if(6 == sscanf(buf+4, "%04d%02d%02d%02d%02d%02d",
-                   &year, &month, &day, &hour, &minute, &second)) {
-      /* we have a time, reformat it */
-      time_t secs=time(NULL);
-      sprintf(buf, "%04d%02d%02d %02d:%02d:%02d",
-              year, month, day, hour, minute, second);
-      /* now, convert this into a time() value: */
-      conn->data->info.filetime = curl_getdate(buf, &secs);
-    }
-    else {
-      infof(conn->data, "unsupported MDTM reply format\n");
+  switch(ftpcode) {
+  case 213:
+    {
+      /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the
+         last .sss part is optional and means fractions of a second */
+      int year, month, day, hour, minute, second;
+      if(6 == sscanf(buf+4, "%04d%02d%02d%02d%02d%02d",
+                     &year, &month, &day, &hour, &minute, &second)) {
+        /* we have a time, reformat it */
+        time_t secs=time(NULL);
+        sprintf(buf, "%04d%02d%02d %02d:%02d:%02d",
+                year, month, day, hour, minute, second);
+        /* now, convert this into a time() value: */
+        conn->data->info.filetime = curl_getdate(buf, &secs);
+      }
     }
+    break;
+  default:
+    infof(conn->data, "unsupported MDTM reply format\n");
+    break;
+  case 550: /* "No such file or directory" */
+    failf(conn->data, "Given file does not exist");
+    result = CURLE_FTP_COULDNT_RETR_FILE;
+    break;
   }
   return  result;
 }
@@ -778,14 +797,13 @@ static CURLcode ftp_transfertype(struct connectdata *conn,
   struct SessionHandle *data = conn->data;
   int ftpcode;
   ssize_t nread;
-  char *buf=data->state.buffer;
   CURLcode result;
 
   FTPSENDF(conn, "TYPE %s", ascii?"A":"I");
 
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
   
   if(ftpcode != 200) {
     failf(data, "Couldn't set %s mode",
@@ -814,9 +832,9 @@ CURLcode ftp_getsize(struct connectdata *conn, char *file,
   CURLcode result;
 
   FTPSENDF(conn, "SIZE %s", file);
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
 
   if(ftpcode == 213) {
     /* get the size from the ascii string: */
@@ -975,7 +993,6 @@ CURLcode ftp_use_port(struct connectdata *conn)
   struct SessionHandle *data=conn->data;
   int portsock=-1;
   ssize_t nread;
-  char *buf = data->state.buffer; /* this is our buffer */
   int ftpcode; /* receive FTP response codes in this */
   CURLcode result;
 
@@ -1155,9 +1172,9 @@ CURLcode ftp_use_port(struct connectdata *conn)
         return result;
     }
     
-    nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-    if(nread < 0)
-      return CURLE_OPERATION_TIMEOUTED;
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if(result)
+      return result;
     
     if (ftpcode != 200) {
       failf(data, "Server does not grok %s", *modep);
@@ -1301,9 +1318,9 @@ CURLcode ftp_use_port(struct connectdata *conn)
       return result;
   }
 
-  nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-  if(nread < 0)
-    return CURLE_OPERATION_TIMEOUTED;
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
 
   if(ftpcode != 200) {
     failf(data, "Server does not grok PORT, try without it!");
@@ -1375,9 +1392,9 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
     result = Curl_ftpsendf(conn, "%s", mode[modeoff]);
     if(result)
       return result;
-    nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-    if(nread < 0)
-      return CURLE_OPERATION_TIMEOUTED;
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if(result)
+      return result;
     if (ftpcode == results[modeoff])
       break;
   }
@@ -1522,7 +1539,7 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
   ssize_t nread;
   int ftpcode; /* for ftp status */
 
-  /* the ftp struct is already inited in ftp_connect() */
+  /* the ftp struct is already inited in Curl_ftp_connect() */
   struct FTP *ftp = conn->proto.ftp;
   long *bytecountp = ftp->bytecountp;
 
@@ -1582,8 +1599,8 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
             readthisamountnow = BUFSIZE;
 
           actuallyread =
-            data->set.fread(data->state.buffer, 1, readthisamountnow,
-                            data->set.in);
+            conn->fread(data->state.buffer, 1, readthisamountnow,
+                        conn->fread_in);
 
           passed += actuallyread;
           if(actuallyread != readthisamountnow) {
@@ -1614,7 +1631,7 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
       }
     }
 
-    /* Send everything on data->set.in to the socket */
+    /* Send everything on data->state.in to the socket */
     if(data->set.ftp_append) {
       /* we append onto the file instead of rewriting it */
       FTPSENDF(conn, "APPE %s", ftp->file);
@@ -1623,9 +1640,9 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
       FTPSENDF(conn, "STOR %s", ftp->file);
     }
 
-    nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-    if(nread < 0)
-      return CURLE_OPERATION_TIMEOUTED;
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if(result)
+      return result;
 
     if(ftpcode>=400) {
       failf(data, "Failed FTP upload:%s", buf+3);
@@ -1799,9 +1816,9 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
 
         FTPSENDF(conn, "REST %d", conn->resume_from);
 
-        nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-        if(nread < 0)
-          return CURLE_OPERATION_TIMEOUTED;
+        result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+        if(result)
+          return result;
 
         if(ftpcode != 350) {
           failf(data, "Couldn't use REST: %s", buf+4);
@@ -1812,9 +1829,9 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
       FTPSENDF(conn, "RETR %s", ftp->file);
     }
 
-    nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
-    if(nread < 0)
-      return CURLE_OPERATION_TIMEOUTED;
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if(result)
+      return result;
 
     if((ftpcode == 150) || (ftpcode == 125)) {
 
@@ -1919,7 +1936,7 @@ CURLcode ftp_perform(struct connectdata *conn,
   struct SessionHandle *data=conn->data;
   char *buf = data->state.buffer; /* this is our buffer */
 
-  /* the ftp struct is already inited in ftp_connect() */
+  /* the ftp struct is already inited in Curl_ftp_connect() */
   struct FTP *ftp = conn->proto.ftp;
 
   /* Send any QUOTE strings? */
@@ -1980,7 +1997,7 @@ CURLcode ftp_perform(struct connectdata *conn,
        well, we "emulate" a HTTP-style header in our output. */
 
 #ifdef HAVE_STRFTIME
-    if(data->set.get_filetime && data->info.filetime) {
+    if(data->set.get_filetime && (data->info.filetime>=0) ) {
       struct tm *tm;
 #ifdef HAVE_LOCALTIME_R
       struct tm buffer;