@@ -1,16 +1,16 @@
 /***************************************************************************
- *                                  _   _ ____  _     
- *  Project                     ___| | | |  _ \| |    
- *                             / __| | | | |_) | |    
- *                            | (__| |_| |  _ <| |___ 
+ *                                  _   _ ____  _
+ *  Project                     ___| | | |  _ \| |
+ *                             / __| | | | |_) | |
+ *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
  * are also available at http://curl.haxx.se/docs/copyright.html.
- * 
+ *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
@@ -39,7 +39,7 @@
 #endif
 
 #if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
-#include <winsock.h>
+
 #else /* some kind of unix */
 #ifdef HAVE_SYS_SOCKET_H
 #include <sys/socket.h>
@@ -65,6 +65,11 @@
 #include <errno.h>
 #endif
 
+#if (defined(NETWARE) && defined(__NOVELL_LIBC__))
+#undef in_addr_t
+#define in_addr_t unsigned long
+#endif
+
 #include <curl/curl.h>
 #include "urldata.h"
 #include "sendf.h"
@@ -77,14 +82,18 @@
 #include "http.h" /* for HTTP proxy tunnel stuff */
 #include "ftp.h"
 
-#ifdef KRB4
+#ifdef HAVE_KRB4
 #include "security.h"
 #include "krb4.h"
 #endif
 
+#include "strtoofft.h"
 #include "strequal.h"
 #include "ssluse.h"
 #include "connect.h"
+#include "strerror.h"
+#include "memory.h"
+#include "inet_ntop.h"
 
 #if defined(HAVE_INET_NTOA_R) && !defined(HAVE_INET_NTOA_R_DECL)
 #include "inet_ntoa_r.h"
@@ -94,17 +103,50 @@
 #include <curl/mprintf.h>
 
 /* The last #include file should be: */
-#ifdef MALLOCDEBUG
+#ifdef CURLDEBUG
 #include "memdebug.h"
 #endif
 
+#ifdef HAVE_NI_WITHSCOPEID
+#define NIFLAGS NI_NUMERICHOST | NI_NUMERICSERV | NI_WITHSCOPEID
+#else
+#define NIFLAGS NI_NUMERICHOST | NI_NUMERICSERV
+#endif
+
 /* Local API functions */
-static CURLcode ftp_sendquote(struct connectdata *conn, struct curl_slist *quote);
+static CURLcode ftp_sendquote(struct connectdata *conn,
+                              struct curl_slist *quote);
 static CURLcode ftp_cwd(struct connectdata *conn, char *path);
+static CURLcode ftp_mkd(struct connectdata *conn, char *path);
+static CURLcode ftp_cwd_and_mkd(struct connectdata *conn, char *path);
+static CURLcode ftp_quit(struct connectdata *conn);
+static CURLcode ftp_3rdparty_pretransfer(struct connectdata *conn);
+static CURLcode ftp_3rdparty_transfer(struct connectdata *conn);
+static CURLcode ftp_regular_transfer(struct connectdata *conn);
+static CURLcode ftp_3rdparty(struct connectdata *conn);
 
 /* easy-to-use macro: */
 #define FTPSENDF(x,y,z) if((result = Curl_ftpsendf(x,y,z))) return result
 
+static void freedirs(struct FTP *ftp)
+{
+  int i;
+  if(ftp->dirs) {
+    for (i=0; i < ftp->dirdepth; i++){
+      if(ftp->dirs[i]) {
+        free(ftp->dirs[i]);
+        ftp->dirs[i]=NULL;
+      }
+    }
+    free(ftp->dirs);
+    ftp->dirs = NULL;
+  }
+  if(ftp->file) {
+    free(ftp->file);
+    ftp->file = NULL;
+  }
+}
+
 /***********************************************************************
  *
  * AllowServerConnect()
@@ -114,19 +156,31 @@ static CURLcode ftp_cwd(struct connectdata *conn, char *path);
  * connected.
  *
  */
-static CURLcode AllowServerConnect(struct SessionHandle *data,
-                                   struct connectdata *conn,
-                                   int sock)
+static CURLcode AllowServerConnect(struct connectdata *conn)
 {
   fd_set rdset;
   struct timeval dt;
-  
+  struct SessionHandle *data = conn->data;
+  curl_socket_t sock = conn->sock[SECONDARYSOCKET];
+  struct timeval now = Curl_tvnow();
+  long timespent = Curl_tvdiff(Curl_tvnow(), now)/1000;
+  long timeout = data->set.connecttimeout?data->set.connecttimeout:
+    (data->set.timeout?data->set.timeout: 0);
+
   FD_ZERO(&rdset);
 
   FD_SET(sock, &rdset);
 
-  /* we give the server 10 seconds to connect to us */
-  dt.tv_sec = 10;
+  if(timeout) {
+    timeout -= timespent;
+    if(timeout<=0) {
+      failf(data, "Timed out before server could connect to us");
+      return CURLE_OPERATION_TIMEDOUT;
+    }
+  }
+
+  /* we give the server 60 seconds to connect to us, or a custom timeout */
+  dt.tv_sec = (int)(timeout?timeout:60);
   dt.tv_usec = 0;
 
   switch (select(sock+1, &rdset, NULL, NULL, &dt)) {
@@ -141,30 +195,28 @@ static CURLcode AllowServerConnect(struct SessionHandle *data,
   default:
     /* we have received data here */
     {
-      int s;
-#ifdef __hpux     
-      int size = sizeof(struct sockaddr_in);
-#else 
-      socklen_t size = sizeof(struct sockaddr_in);
-#endif
+      curl_socket_t s;
+      size_t size = sizeof(struct sockaddr_in);
       struct sockaddr_in add;
 
-      getsockname(sock, (struct sockaddr *) &add, &size);
-      s=(int)accept(sock, (struct sockaddr *) &add, &size);
+      getsockname(sock, (struct sockaddr *) &add, (socklen_t *)&size);
+      s=accept(sock, (struct sockaddr *) &add, (socklen_t *)&size);
 
       sclose(sock); /* close the first socket */
 
-      if (-1 == s) {
+      if (CURL_SOCKET_BAD == s) {
         /* DIE! */
         failf(data, "Error accept()ing server connect");
         return CURLE_FTP_PORT_FAILED;
       }
       infof(data, "Connection accepted from server\n");
 
-      conn->secondarysocket = s;
+      conn->sock[SECONDARYSOCKET] = s;
+      Curl_nonblock(s, TRUE); /* enable non-blocking */
     }
     break;
   }
+
   return CURLE_OK;
 }
 
@@ -177,7 +229,7 @@ static CURLcode AllowServerConnect(struct SessionHandle *data,
  * response and extract the relevant return code for the invoking function.
  */
 
-CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
+CURLcode Curl_GetFTPResponse(ssize_t *nreadp, /* return number of bytes read */
                              struct connectdata *conn,
                              int *ftpcode) /* return the ftp-code */
 {
@@ -188,12 +240,12 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
    * Alas, read as much as possible, split up into lines, use the ending
    * line in a response or continue reading.  */
 
-  int sockfd = conn->firstsocket;
+  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
   int perline; /* count bytes per line */
   bool keepon=TRUE;
   ssize_t gotbytes;
   char *ptr;
-  int timeout;              /* timeout in seconds */
+  long timeout;              /* timeout in seconds */
   struct timeval interval;
   fd_set rkeepfd;
   fd_set readfd;
@@ -224,7 +276,15 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
 
   while((*nreadp<BUFSIZE) && (keepon && !result)) {
     /* check and reset timeout value every lap */
-    if(data->set.timeout)
+    if(data->set.ftp_response_timeout )
+      /* if CURLOPT_FTP_RESPONSE_TIMEOUT is set, use that to determine
+         remaining time.  Also, use "now" as opposed to "conn->now"
+         because ftp_response_timeout is only supposed to govern
+         the response for any given ftp response, not for the time
+         from connect to the given ftp response. */
+      timeout = data->set.ftp_response_timeout - /* timeout time */
+        Curl_tvdiff(Curl_tvnow(), now)/1000; /* spent time */
+    else if(data->set.timeout)
       /* if timeout is requested, find out how much remaining time we have */
       timeout = data->set.timeout - /* timeout time */
         Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
@@ -235,24 +295,25 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
         Curl_tvdiff(Curl_tvnow(), now)/1000; /* spent time */
 
     if(timeout <=0 ) {
-      failf(data, "Transfer aborted due to timeout");
+      failf(data, "FTP response timeout");
       return CURLE_OPERATION_TIMEDOUT; /* already too little time */
     }
 
     if(!ftp->cache) {
       readfd = rkeepfd;            /* set every lap */
-      interval.tv_sec = timeout;
+      interval.tv_sec = 1; /* use 1 second timeout intervals */
       interval.tv_usec = 0;
 
       switch (select (sockfd+1, &readfd, NULL, NULL, &interval)) {
       case -1: /* select() error, stop reading */
         result = CURLE_RECV_ERROR;
-        failf(data, "Transfer aborted due to select() error: %d", errno);
+        failf(data, "FTP response aborted due to select() error: %d", errno);
         break;
       case 0: /* timeout */
-        result = CURLE_OPERATION_TIMEDOUT;
-        failf(data, "Transfer aborted due to timeout");
-        break;
+        if(Curl_pgrsUpdate(conn))
+          return CURLE_ABORTED_BY_CALLBACK;
+        continue; /* just continue in our loop for the timeout duration */
+
       default:
         break;
       }
@@ -265,8 +326,15 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
        */
       if(ftp->cache) {
         /* we had data in the "cache", copy that instead of doing an actual
-           read */
-        memcpy(ptr, ftp->cache, ftp->cache_size);
+         * read
+         *
+         * Dave Meyer, December 2003:
+         * ftp->cache_size is cast to int here.  This should be safe,
+         * because it would have been populated with something of size
+         * int to begin with, even though its datatype may be larger
+         * than an int.
+         */
+        memcpy(ptr, ftp->cache, (int)ftp->cache_size);
         gotbytes = (int)ftp->cache_size;
         free(ftp->cache);    /* free the cache */
         ftp->cache = NULL;   /* clear the pointer */
@@ -287,25 +355,26 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
       else if(gotbytes <= 0) {
         keepon = FALSE;
         result = CURLE_RECV_ERROR;
-        failf(data, "Connection aborted");
+        failf(data, "FTP response reading failed");
       }
       else {
         /* we got a whole chunk of data, which can be anything from one
          * byte to a set of lines and possible just a piece of the last
          * line */
         int i;
 
+        conn->headerbytecount += gotbytes;
+
         *nreadp += gotbytes;
         for(i = 0; i < gotbytes; ptr++, i++) {
           perline++;
           if(*ptr=='\n') {
             /* a newline is CRLF in ftp-talk, so the CR is ignored as
                the line isn't really terminated until the LF comes */
-            CURLcode result;
 
             /* output debug output if that is requested */
             if(data->set.verbose)
-              Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline);
+              Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline, conn->host.dispname);
 
             /*
              * We pass all response-lines to the callback function registered
@@ -316,7 +385,7 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
                                        line_start, perline);
             if(result)
               return result;
-                                       
+
 #define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
                         isdigit((int)line[2]) && (' ' == line[3]))
 
@@ -346,9 +415,9 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
              already!  Cleverly figured out by Eric Lavigne in December
              2001. */
           ftp->cache_size = gotbytes - i;
-          ftp->cache = (char *)malloc(ftp->cache_size);
+          ftp->cache = (char *)malloc((int)ftp->cache_size);
           if(ftp->cache)
-            memcpy(ftp->cache, line_start, ftp->cache_size);
+            memcpy(ftp->cache, line_start, (int)ftp->cache_size);
           else
             return CURLE_OUT_OF_MEMORY; /**BANG**/
         }
@@ -359,7 +428,7 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
   if(!result)
     code = atoi(buf);
 
-#ifdef KRB4
+#ifdef HAVE_KRB4
   /* handle the security-oriented responses 6xx ***/
   /* FIXME: some errorchecking perhaps... ***/
   switch(code) {
@@ -381,22 +450,29 @@ CURLcode Curl_GetFTPResponse(int *nreadp, /* return number of bytes read */
   if(ftpcode)
     *ftpcode=code; /* return the initial number like this */
 
+  /* store the latest code for later retrieval */
+  conn->data->info.httpcode=code;
+
   return result;
 }
 
+static const char *ftpauth[]= {
+  "SSL", "TLS", NULL
+};
+
 /*
  * Curl_ftp_connect() should do everything that is to be considered a part of
  * the connection phase.
  */
 CURLcode Curl_ftp_connect(struct connectdata *conn)
 {
   /* this is FTP and no proxy */
-  int nread;
+  ssize_t nread;
   struct SessionHandle *data=conn->data;
   char *buf = data->state.buffer; /* this is our buffer */
   struct FTP *ftp;
   CURLcode result;
-  int ftpcode;
+  int ftpcode, try;
 
   ftp = (struct FTP *)malloc(sizeof(struct FTP));
   if(!ftp)
@@ -411,28 +487,29 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
   /* get some initial data into the ftp struct */
   ftp->bytecountp = &conn->bytecount;
 
-  /* no need to duplicate them, the data struct won't change */
-  ftp->user = data->state.user;
-  ftp->passwd = data->state.passwd;
+  /* no need to duplicate them, this connectdata struct won't change */
+  ftp->user = conn->user;
+  ftp->passwd = conn->passwd;
   ftp->response_time = 3600; /* set default response time-out */
 
-  if (data->set.tunnel_thru_httpproxy) {
+#ifndef CURL_DISABLE_HTTP
+  if (conn->bits.tunnel_proxy) {
     /* We want "seamless" FTP operations through HTTP proxy tunnel */
-    result = Curl_ConnectHTTPProxyTunnel(conn, conn->firstsocket,
-                                         conn->hostname, conn->remote_port);
+    result = Curl_ConnectHTTPProxyTunnel(conn, FIRSTSOCKET,
+                                         conn->host.name, conn->remote_port);
     if(CURLE_OK != result)
       return result;
   }
+#endif   /* CURL_DISABLE_HTTP */
 
   if(conn->protocol & PROT_FTPS) {
     /* FTPS is simply ftp with SSL for the control channel */
     /* now, perform the SSL initialization for this socket */
-    result = Curl_SSLConnect(conn);
+    result = Curl_SSLConnect(conn, FIRSTSOCKET);
     if(result)
       return result;
   }
 
-
   /* The first thing we do is wait for the "220*" line: */
   result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
   if(result)
@@ -443,7 +520,7 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     return CURLE_FTP_WEIRD_SERVER_REPLY;
   }
 
-#ifdef KRB4
+#ifdef HAVE_KRB4
   /* if not anonymous login, try a secure login */
   if(data->set.krb4) {
 
@@ -460,9 +537,39 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
       infof(data, "Authentication successful\n");
   }
 #endif
-  
+
+  if(data->set.ftp_ssl && !conn->ssl[FIRSTSOCKET].use) {
+    /* we don't have a SSL/TLS connection, try a FTPS connection now */
+
+    for (try = 0; ftpauth[try]; try++) {
+
+      FTPSENDF(conn, "AUTH %s", ftpauth[try]);
+
+      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+
+      if(result)
+        return result;
+
+      /* RFC2228 (page 5) says:
+       *
+       * If the server is willing to accept the named security mechanism, and
+       * does not require any security data, it must respond with reply code
+       * 234/334.
+       */
+
+      if((ftpcode == 234) || (ftpcode == 334)) {
+        result = Curl_SSLConnect(conn, FIRSTSOCKET);
+        if(result)
+          return result;
+        conn->protocol |= PROT_FTPS;
+        conn->ssl[SECONDARYSOCKET].use = FALSE; /* clear-text data */
+        break;
+      }
+    }
+  }
+
   /* send USER */
-  FTPSENDF(conn, "USER %s", ftp->user);
+  FTPSENDF(conn, "USER %s", ftp->user?ftp->user:"");
 
   /* wait for feedback */
   result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
@@ -478,7 +585,7 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
   else if(ftpcode == 331) {
     /* 331 Password required for ...
        (the server requires to send the user's password too) */
-    FTPSENDF(conn, "PASS %s", ftp->passwd);
+    FTPSENDF(conn, "PASS %s", ftp->passwd?ftp->passwd:"");
     result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
     if(result)
       return result;
@@ -492,7 +599,7 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     else if(ftpcode == 230) {
       /* 230 User ... logged in.
          (user successfully logged in) */
-        
+
       infof(data, "We have successfully logged in\n");
     }
     else {
@@ -504,28 +611,71 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     /* 230 User ... logged in.
        (the user logged in without password) */
     infof(data, "We have successfully logged in\n");
-#ifdef KRB4
-        /* we are logged in (with Kerberos)
-         * now set the requested protection level
-         */
-    if(conn->sec_complete)
-      Curl_sec_set_protection_level(conn);
+    if (conn->ssl[FIRSTSOCKET].use) {
+#ifdef HAVE_KRB4
+      /* We are logged in with Kerberos, now set the requested protection
+       * level
+       */
+      if(conn->sec_complete)
+        Curl_sec_set_protection_level(conn);
 
-    /* we may need to issue a KAUTH here to have access to the files
-     * do it if user supplied a password
-     */
-    if(data->state.passwd && *data->state.passwd) {
-      result = Curl_krb_kauth(conn);
-      if(result)
-        return result;
-    }
+      /* We may need to issue a KAUTH here to have access to the files
+       * do it if user supplied a password
+       */
+      if(conn->passwd && *conn->passwd) {
+        result = Curl_krb_kauth(conn);
+        if(result)
+          return result;
+      }
 #endif
+    }
   }
   else {
     failf(data, "Odd return code after USER");
     return CURLE_FTP_WEIRD_USER_REPLY;
   }
 
+  if(conn->ssl[FIRSTSOCKET].use) {
+    /* PBSZ = PROTECTION BUFFER SIZE.
+
+       The 'draft-murray-auth-ftp-ssl' (draft 12, page 7) says:
+
+       Specifically, the PROT command MUST be preceded by a PBSZ command
+       and a PBSZ command MUST be preceded by a successful security data
+       exchange (the TLS negotiation in this case)
+
+       ... (and on page 8):
+
+       Thus the PBSZ command must still be issued, but must have a parameter
+       of '0' to indicate that no buffering is taking place and the data
+       connection should not be encapsulated.
+    */
+    FTPSENDF(conn, "PBSZ %d", 0);
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if(result)
+      return result;
+
+    /* For TLS, the data connection can have one of two security levels.
+
+       1)Clear (requested by 'PROT C')
+
+       2)Private (requested by 'PROT P')
+    */
+    if(!conn->ssl[SECONDARYSOCKET].use) {
+      FTPSENDF(conn, "PROT %c", 'P');
+      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+      if(result)
+        return result;
+
+      if(ftpcode == 200)
+        /* We have enabled SSL for the data connection! */
+        conn->ssl[SECONDARYSOCKET].use = TRUE;
+
+      /* FTP servers typically responds with 500 if they decide to reject
+         our 'P' request */
+    }
+  }
+
   /* send PWD to discover our entry point */
   FTPSENDF(conn, "PWD", NULL);
 
@@ -538,14 +688,17 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
     char *dir = (char *)malloc(nread+1);
     char *store=dir;
     char *ptr=&buf[4]; /* start on the first letter */
-    
+
+    if(!dir)
+      return CURLE_OUT_OF_MEMORY;
+
     /* Reply format is like
        257<space>"<directory-name>"<space><commentary> and the RFC959 says
 
        The directory name can contain any character; embedded double-quotes
        should be escaped by double-quotes (the "quote-doubling" convention).
     */
-    if(dir && ('\"' == *ptr)) {
+    if('\"' == *ptr) {
       /* it started good */
       ptr++;
       while(ptr && *ptr) {
@@ -592,27 +745,40 @@ CURLcode Curl_ftp_connect(struct connectdata *conn)
  *
  * Input argument is already checked for validity.
  */
-CURLcode Curl_ftp_done(struct connectdata *conn)
+CURLcode Curl_ftp_done(struct connectdata *conn, CURLcode status)
 {
   struct SessionHandle *data = conn->data;
   struct FTP *ftp = conn->proto.ftp;
-  int nread;
+  ssize_t nread;
   int ftpcode;
   CURLcode result=CURLE_OK;
 
+  bool was_ctl_valid = ftp->ctl_valid;
+
+  /* free the dir tree and file parts */
+  freedirs(ftp);
+
+  ftp->ctl_valid = FALSE;
+
   if(data->set.upload) {
     if((-1 != data->set.infilesize) &&
        (data->set.infilesize != *ftp->bytecountp) &&
        !data->set.crlf) {
-      failf(data, "Uploaded unaligned file size (%d out of %d bytes)",
+      failf(data, "Uploaded unaligned file size (%" FORMAT_OFF_T
+            " out of %" FORMAT_OFF_T " bytes)",
             *ftp->bytecountp, data->set.infilesize);
+      conn->bits.close = TRUE; /* close this connection since we don't
+                                  know what state this error leaves us in */
       return CURLE_PARTIAL_FILE;
     }
   }
   else {
     if((-1 != conn->size) && (conn->size != *ftp->bytecountp) &&
        (conn->maxdownload != *ftp->bytecountp)) {
-      failf(data, "Received only partial file: %d bytes", *ftp->bytecountp);
+      failf(data, "Received only partial file: %" FORMAT_OFF_T " bytes",
+            *ftp->bytecountp);
+      conn->bits.close = TRUE; /* close this connection since we don't
+                                  know what state this error leaves us in */
       return CURLE_PARTIAL_FILE;
     }
     else if(!ftp->dont_check &&
@@ -627,25 +793,43 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
     }
   }
 
-#ifdef KRB4
-  Curl_sec_fflush_fd(conn, conn->secondarysocket);
+  switch(status) {
+  case CURLE_BAD_DOWNLOAD_RESUME:
+  case CURLE_FTP_WEIRD_PASV_REPLY:
+  case CURLE_FTP_PORT_FAILED:
+  case CURLE_FTP_COULDNT_SET_BINARY:
+  case CURLE_FTP_COULDNT_RETR_FILE:
+  case CURLE_FTP_ACCESS_DENIED:
+    /* the connection stays alive fine even though this happened */
+    /* fall-through */
+  case CURLE_OK: /* doesn't affect the control connection's status */
+    ftp->ctl_valid = was_ctl_valid;
+    break;
+  default:       /* by default, an error means the control connection is
+                    wedged and should not be used anymore */
+    ftp->ctl_valid = FALSE;
+    break;
+  }
+
+#ifdef HAVE_KRB4
+  Curl_sec_fflush_fd(conn, conn->sock[SECONDARYSOCKET]);
 #endif
   /* shut down the socket to inform the server we're done */
-  sclose(conn->secondarysocket);
-  conn->secondarysocket = -1;
+  sclose(conn->sock[SECONDARYSOCKET]);
+  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
 
-  if(!ftp->no_transfer) {
+  if(!ftp->no_transfer && !status) {
     /* Let's see what the server says about the transfer we just performed,
-       but lower the timeout as sometimes this connection has died while 
-       the data has been transfered. This happens when doing through NATs
-       etc that abandon old silent connections.
-    */
+     * but lower the timeout as sometimes this connection has died while the
+     * data has been transfered. This happens when doing through NATs etc that
+     * abandon old silent connections.
+     */
     ftp->response_time = 60; /* give it only a minute for now */
 
     result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
 
     ftp->response_time = 3600; /* set this back to one hour waits */
-  
+
     if(!nread && (CURLE_OPERATION_TIMEDOUT == result)) {
       failf(data, "control connection looks dead");
       return result;
@@ -665,10 +849,15 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
 
   /* clear these for next connection */
   ftp->no_transfer = FALSE;
-  ftp->dont_check = FALSE; 
+  ftp->dont_check = FALSE;
+
+  if (!result && conn->sec_conn) {   /* 3rd party transfer */
+    /* "done" with the secondary connection */
+    result = Curl_ftp_done(conn->sec_conn, status);
+  }
 
   /* Send any post-transfer QUOTE strings? */
-  if(!result && data->set.postquote)
+  if(!status && !result && data->set.postquote)
     result = ftp_sendquote(conn, data->set.postquote);
 
   return result;
@@ -682,11 +871,11 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
  * The quote list is passed as an argument.
  */
 
-static 
+static
 CURLcode ftp_sendquote(struct connectdata *conn, struct curl_slist *quote)
 {
   struct curl_slist *item;
-  int nread;
+  ssize_t nread;
   int ftpcode;
   CURLcode result;
 
@@ -713,33 +902,6 @@ CURLcode ftp_sendquote(struct connectdata *conn, struct curl_slist *quote)
 
 /***********************************************************************
  *
- * ftp_cwd()
- *
- * Send 'CWD' to the remote server to Change Working Directory.
- * It is the ftp version of the unix 'cd' command.
- */
-static 
-CURLcode ftp_cwd(struct connectdata *conn, char *path)
-{
-  int nread;
-  int     ftpcode;
-  CURLcode result;
-  
-  FTPSENDF(conn, "CWD %s", path);
-  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
-  if (result)
-    return result;
-
-  if (ftpcode != 250) {
-    failf(conn->data, "Couldn't cd to %s", path);
-    return CURLE_FTP_ACCESS_DENIED;
-  }
-
-  return CURLE_OK;
-}
-
-/***********************************************************************
- *
  * ftp_getfiletime()
  *
  * Get the timestamp of the given file.
@@ -749,7 +911,7 @@ CURLcode ftp_getfiletime(struct connectdata *conn, char *file)
 {
   CURLcode result=CURLE_OK;
   int ftpcode; /* for ftp status */
-  int nread;
+  ssize_t nread;
   char *buf = conn->data->state.buffer;
 
   /* we have requested to get the modified-time of the file, this is yet
@@ -770,8 +932,9 @@ CURLcode ftp_getfiletime(struct connectdata *conn, char *file)
                      &year, &month, &day, &hour, &minute, &second)) {
         /* we have a time, reformat it */
         time_t secs=time(NULL);
-        sprintf(buf, "%04d%02d%02d %02d:%02d:%02d",
-                year, month, day, hour, minute, second);
+        snprintf(buf, sizeof(conn->data->state.buffer),
+                 "%04d%02d%02d %02d:%02d:%02d GMT",
+                 year, month, day, hour, minute, second);
         /* now, convert this into a time() value: */
         conn->data->info.filetime = curl_getdate(buf, &secs);
       }
@@ -800,15 +963,15 @@ static CURLcode ftp_transfertype(struct connectdata *conn,
 {
   struct SessionHandle *data = conn->data;
   int ftpcode;
-  int nread;
+  ssize_t nread;
   CURLcode result;
 
   FTPSENDF(conn, "TYPE %s", ascii?"A":"I");
 
   result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
   if(result)
     return result;
-  
+
   if(ftpcode != 200) {
     failf(data, "Couldn't set %s mode",
           ascii?"ASCII":"binary");
@@ -827,11 +990,11 @@ static CURLcode ftp_transfertype(struct connectdata *conn,
 
 static
 CURLcode ftp_getsize(struct connectdata *conn, char *file,
-                      ssize_t *size)
+                     curl_off_t *size)
 {
   struct SessionHandle *data = conn->data;
   int ftpcode;
-  int nread;
+  ssize_t nread;
   char *buf=data->state.buffer;
   CURLcode result;
 
@@ -842,7 +1005,7 @@ CURLcode ftp_getsize(struct connectdata *conn, char *file,
 
   if(ftpcode == 213) {
     /* get the size from the ascii string: */
-    *size = atoi(buf+4);
+    *size = curlx_strtoofft(buf+4, NULL, 0);
   }
   else
     return CURLE_FTP_COULDNT_GET_SIZE;
@@ -861,125 +1024,13 @@ CURLcode ftp_getsize(struct connectdata *conn, char *file,
  */
 static void
 ftp_pasv_verbose(struct connectdata *conn,
-                 Curl_ipconnect *addr,
+                 Curl_addrinfo *ai,
                  char *newhost, /* ascii version */
                  int port)
 {
-#ifndef ENABLE_IPV6
-  /*****************************************************************
-   *
-   * IPv4-only code section
-   */
-
-  struct in_addr in;
-  struct hostent * answer;
-
-#ifdef HAVE_INET_NTOA_R
-  char ntoa_buf[64];
-#endif
-  /* The array size trick below is to make this a large chunk of memory
-     suitably 8-byte aligned on 64-bit platforms. This was thoughtfully
-     suggested by Philip Gladstone. */
-  long bigbuf[9000 / sizeof(long)];
-
-#if defined(HAVE_INET_ADDR)
-  in_addr_t address;
-# if defined(HAVE_GETHOSTBYADDR_R)
-  int h_errnop;
-# endif
-  char *hostent_buf = (char *)bigbuf; /* get a char * to the buffer */
-  (void)hostent_buf;
-  address = inet_addr(newhost);
-# ifdef HAVE_GETHOSTBYADDR_R
-
-#  ifdef HAVE_GETHOSTBYADDR_R_5
-  /* AIX, Digital Unix (OSF1, Tru64) style:
-     extern int gethostbyaddr_r(char *addr, size_t len, int type,
-     struct hostent *htent, struct hostent_data *ht_data); */
-
-  /* Fred Noz helped me try this out, now it at least compiles! */
-
-  /* Bjorn Reese (November 28 2001):
-     The Tru64 man page on gethostbyaddr_r() says that
-     the hostent struct must be filled with zeroes before the call to
-     gethostbyaddr_r(). 
-
-     ... as must be struct hostent_data Craig Markwardt 19 Sep 2002. */
-
-  memset(hostent_buf, 0, sizeof(struct hostent)+sizeof(struct hostent_data));
-
-  if(gethostbyaddr_r((char *) &address,
-                     sizeof(address), AF_INET,
-                     (struct hostent *)hostent_buf,
-                     (struct hostent_data *)(hostent_buf + sizeof(*answer))))
-    answer=NULL;
-  else
-    answer=(struct hostent *)hostent_buf;
-                           
-#  endif
-#  ifdef HAVE_GETHOSTBYADDR_R_7
-  /* Solaris and IRIX */
-  answer = gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,
-                           (struct hostent *)bigbuf,
-                           hostent_buf + sizeof(*answer),
-                           sizeof(bigbuf) - sizeof(*answer),
-                           &h_errnop);
-#  endif
-#  ifdef HAVE_GETHOSTBYADDR_R_8
-  /* Linux style */
-  if(gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,
-                     (struct hostent *)hostent_buf,
-                     hostent_buf + sizeof(*answer),
-                     sizeof(bigbuf) - sizeof(*answer),
-                     &answer,
-                     &h_errnop))
-    answer=NULL; /* error */
-#  endif
-        
-# else
-  answer = gethostbyaddr((char *) &address, sizeof(address), AF_INET);
-# endif
-#else
-  answer = NULL;
-#endif
-  (void) memcpy(&in.s_addr, addr, sizeof (Curl_ipconnect));
-  infof(conn->data, "Connecting to %s (%s) port %u\n",
-        answer?answer->h_name:newhost,
-#if defined(HAVE_INET_NTOA_R)
-        inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf)),
-#else
-        inet_ntoa(in),
-#endif
-        port);
-
-#else
-  /*****************************************************************
-   *
-   * IPv6-only code section
-   */
-  char hbuf[NI_MAXHOST]; /* ~1KB */
-  char nbuf[NI_MAXHOST]; /* ~1KB */
-  char sbuf[NI_MAXSERV]; /* around 32 */
-#ifdef NI_WITHSCOPEID
-  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV | NI_WITHSCOPEID;
-#else
-  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV;
-#endif
-  port = 0; /* unused, prevent warning */
-  if (getnameinfo(addr->ai_addr, addr->ai_addrlen,
-                  nbuf, sizeof(nbuf), sbuf, sizeof(sbuf), niflags)) {
-    snprintf(nbuf, sizeof(nbuf), "?");
-    snprintf(sbuf, sizeof(sbuf), "?");
-  }
-        
-  if (getnameinfo(addr->ai_addr, addr->ai_addrlen,
-                  hbuf, sizeof(hbuf), NULL, 0, 0)) {
-    infof(conn->data, "Connecting to %s (%s) port %s\n", nbuf, newhost, sbuf);
-  }
-  else {
-    infof(conn->data, "Connecting to %s (%s) port %s\n", hbuf, nbuf, sbuf);
-  }
-#endif
+  char buf[256];
+  Curl_printable_address(ai, buf, sizeof(buf));
+  infof(conn->data, "Connecting to %s (%s) port %d\n", newhost, buf, port);
 }
 
 /***********************************************************************
@@ -995,8 +1046,8 @@ static
 CURLcode ftp_use_port(struct connectdata *conn)
 {
   struct SessionHandle *data=conn->data;
-  int portsock=-1;
-  int nread;
+  curl_socket_t portsock= CURL_SOCKET_BAD;
+  ssize_t nread;
   int ftpcode; /* receive FTP response codes in this */
   CURLcode result;
 
@@ -1013,77 +1064,95 @@ CURLcode ftp_use_port(struct connectdata *conn)
   char hbuf[NI_MAXHOST];
 
   struct sockaddr *sa=(struct sockaddr *)&ss;
-#ifdef NI_WITHSCOPEID
-  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV | NI_WITHSCOPEID;
-#else
-  const int niflags = NI_NUMERICHOST | NI_NUMERICSERV;
-#endif
   unsigned char *ap;
   unsigned char *pp;
-  char portmsgbuf[4096], tmp[4096];
+  char portmsgbuf[1024], tmp[1024];
 
   const char *mode[] = { "EPRT", "LPRT", "PORT", NULL };
   char **modep;
+  int rc;
+  int error;
 
   /*
    * we should use Curl_if2ip?  given pickiness of recent ftpd,
    * I believe we should use the same address as the control connection.
    */
   sslen = sizeof(ss);
-  if (getsockname(conn->firstsocket, (struct sockaddr *)&ss, &sslen) < 0)
+  rc = getsockname(conn->sock[FIRSTSOCKET], (struct sockaddr *)&ss, &sslen);
+  if(rc < 0) {
+    failf(data, "getsockname() returned %d\n", rc);
     return CURLE_FTP_PORT_FAILED;
-  
-  if (getnameinfo((struct sockaddr *)&ss, sslen, hbuf, sizeof(hbuf), NULL, 0,
-                  niflags))
+  }
+
+  rc = getnameinfo((struct sockaddr *)&ss, sslen, hbuf, sizeof(hbuf), NULL, 0,
+                   NIFLAGS);
+  if(rc) {
+    failf(data, "getnameinfo() returned %d\n", rc);
     return CURLE_FTP_PORT_FAILED;
+  }
 
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = sa->sa_family;
   /*hints.ai_family = ss.ss_family;
-    this way can be used if sockaddr_storage is properly defined, as glibc 
+    this way can be used if sockaddr_storage is properly defined, as glibc
     2.1.X doesn't do*/
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags = AI_PASSIVE;
 
-  if (getaddrinfo(hbuf, (char *)"0", &hints, &res))
+  rc = getaddrinfo(hbuf, NULL, &hints, &res);
+  if(rc) {
+    failf(data, "getaddrinfo() returned %d\n", rc);
     return CURLE_FTP_PORT_FAILED;
-  
-  portsock = -1;
+  }
+
+  portsock = CURL_SOCKET_BAD;
+  error = 0;
   for (ai = res; ai; ai = ai->ai_next) {
+    /*
+     * Workaround for AIX5 getaddrinfo() problem (it doesn't set ai_socktype):
+     */
+    if (ai->ai_socktype == 0)
+      ai->ai_socktype = hints.ai_socktype;
+
     portsock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
-    if (portsock < 0)
+    if (portsock == CURL_SOCKET_BAD) {
+      error = Curl_ourerrno();
       continue;
+    }
 
     if (bind(portsock, ai->ai_addr, ai->ai_addrlen) < 0) {
+      error = Curl_ourerrno();
       sclose(portsock);
-      portsock = -1;
+      portsock = CURL_SOCKET_BAD;
       continue;
     }
-      
+
     if (listen(portsock, 1) < 0) {
+      error = Curl_ourerrno();
       sclose(portsock);
-      portsock = -1;
+      portsock = CURL_SOCKET_BAD;
       continue;
     }
-    
+
     break;
   }
   freeaddrinfo(res);
-  if (portsock < 0) {
-    failf(data, "%s", strerror(errno));
+  if (portsock == CURL_SOCKET_BAD) {
+    failf(data, "%s", Curl_strerror(conn,error));
     return CURLE_FTP_PORT_FAILED;
   }
 
   sslen = sizeof(ss);
   if (getsockname(portsock, sa, &sslen) < 0) {
-    failf(data, "%s", strerror(errno));
+    failf(data, "%s", Curl_strerror(conn,Curl_ourerrno()));
     return CURLE_FTP_PORT_FAILED;
   }
 
-  for (modep = (char **)mode; modep && *modep; modep++) {
+  for (modep = (char **)(data->set.ftp_use_eprt?&mode[0]:&mode[2]);
+       modep && *modep; modep++) {
     int lprtaf, eprtaf;
     int alen=0, plen=0;
-    
+
     switch (sa->sa_family) {
     case AF_INET:
       ap = (unsigned char *)&((struct sockaddr_in *)&ss)->sin_addr;
@@ -1111,24 +1180,26 @@ CURLcode ftp_use_port(struct connectdata *conn)
       if (eprtaf < 0)
         continue;
       if (getnameinfo((struct sockaddr *)&ss, sslen,
-                      portmsgbuf, sizeof(portmsgbuf), tmp, sizeof(tmp), niflags))
+                      portmsgbuf, sizeof(portmsgbuf), tmp, sizeof(tmp),
+                      NIFLAGS))
         continue;
 
       /* do not transmit IPv6 scope identifier to the wire */
       if (sa->sa_family == AF_INET6) {
         char *q = strchr(portmsgbuf, '%');
-          if (q)
-            *q = '\0';
+        if (q)
+          *q = '\0';
       }
 
       result = Curl_ftpsendf(conn, "%s |%d|%s|%s|", *modep, eprtaf,
                              portmsgbuf, tmp);
       if(result)
         return result;
-    } else if (strcmp(*modep, "LPRT") == 0 ||
-               strcmp(*modep, "PORT") == 0) {
+    }
+    else if (strcmp(*modep, "LPRT") == 0 ||
+             strcmp(*modep, "PORT") == 0) {
       int i;
-      
+
       if (strcmp(*modep, "LPRT") == 0 && lprtaf < 0)
         continue;
       if (strcmp(*modep, "PORT") == 0 && sa->sa_family != AF_INET)
@@ -1148,138 +1219,144 @@ CURLcode ftp_use_port(struct connectdata *conn)
           snprintf(tmp, sizeof(tmp), ",%u", ap[i]);
         else
           snprintf(tmp, sizeof(tmp), "%u", ap[i]);
-        
+
         if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=
             sizeof(portmsgbuf)) {
           continue;
         }
       }
-      
+
       if (strcmp(*modep, "LPRT") == 0) {
         snprintf(tmp, sizeof(tmp), ",%d", plen);
-        
+
         if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >= sizeof(portmsgbuf))
           continue;
       }
 
       for (i = 0; i < plen; i++) {
         snprintf(tmp, sizeof(tmp), ",%u", pp[i]);
-        
+
         if (strlcat(portmsgbuf, tmp, sizeof(portmsgbuf)) >=
             sizeof(portmsgbuf)) {
           continue;
         }
       }
-      
+
       result = Curl_ftpsendf(conn, "%s %s", *modep, portmsgbuf);
       if(result)
         return result;
     }
-    
+
     result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
     if(result)
       return result;
-    
+
     if (ftpcode != 200) {
-      failf(data, "Server does not grok %s", *modep);
       continue;
     }
     else
       break;
   }
-  
+
   if (!*modep) {
     sclose(portsock);
+    failf(data, "PORT command attempts failed");
     return CURLE_FTP_PORT_FAILED;
   }
   /* we set the secondary socket variable to this for now, it
      is only so that the cleanup function will close it in case
      we fail before the true secondary stuff is made */
-  conn->secondarysocket = portsock;
-  
+  conn->sock[SECONDARYSOCKET] = portsock;
+
 #else
   /******************************************************************
    *
    * Here's a piece of IPv4-specific code coming up
    *
    */
   struct sockaddr_in sa;
-  struct Curl_dns_entry *h=NULL;
   unsigned short porttouse;
   char myhost[256] = "";
   bool sa_filled_in = FALSE;
+  Curl_addrinfo *addr = NULL;
+  unsigned short ip[4];
 
   if(data->set.ftpport) {
-    if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {
-      h = Curl_resolv(data, myhost, 0);
-    }
+    in_addr_t in;
+
+    /* First check if the given name is an IP address */
+    in=inet_addr(data->set.ftpport);
+
+    if(in != CURL_INADDR_NONE)
+      /* this is an IPv4 address */
+      addr = Curl_ip2addr(in, data->set.ftpport, 0);
     else {
-      size_t len = strlen(data->set.ftpport);
-      if(len>1)
-        h = Curl_resolv(data, data->set.ftpport, 0);
-      if(h)
-        strcpy(myhost, data->set.ftpport); /* buffer overflow risk */
-    }
-  }
-  if(! *myhost) {
+      if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {
+        /* The interface to IP conversion provided a dotted address */
+        in=inet_addr(myhost);
+        addr = Curl_ip2addr(in, myhost, 0);
+      }
+      else if(strlen(data->set.ftpport)> 1) {
+        /* might be a host name! */
+        struct Curl_dns_entry *h=NULL;
+        int rc = Curl_resolv(conn, myhost, 0, &h);
+        if(rc == CURLRESOLV_PENDING)
+          rc = Curl_wait_for_resolv(conn, &h);
+        if(h) {
+          addr = h->addr;
+          /* when we return from this function, we can forget about this entry
+             to we can unlock it now already */
+          Curl_resolv_unlock(data, h);
+        } /* (h) */
+      } /* strlen */
+    } /* CURL_INADDR_NONE */
+  } /* data->set.ftpport */
+
+  if(!addr) {
     /* pick a suitable default here */
 
-#ifdef __hpux     
-    int sslen;
-#else 
     socklen_t sslen;
-#endif
-    
+
     sslen = sizeof(sa);
-    if (getsockname(conn->firstsocket, (struct sockaddr *)&sa, &sslen) < 0) {
+    if (getsockname(conn->sock[FIRSTSOCKET],
+                    (struct sockaddr *)&sa, &sslen) < 0) {
       failf(data, "getsockname() failed");
       return CURLE_FTP_PORT_FAILED;
     }
 
     sa_filled_in = TRUE; /* the sa struct is filled in */
   }
 
-  if(h)
-    /* when we return from here, we can forget about this */
-    Curl_resolv_unlock(h);
+  if (addr || sa_filled_in) {
+    portsock = socket(AF_INET, SOCK_STREAM, 0);
+    if(CURL_SOCKET_BAD != portsock) {
+      socklen_t size;
 
-  if ( h || sa_filled_in) {
-    if( (portsock = (int)socket(AF_INET, SOCK_STREAM, 0)) >= 0 ) {
-      int size;
-      
       /* we set the secondary socket variable to this for now, it
          is only so that the cleanup function will close it in case
          we fail before the true secondary stuff is made */
-      conn->secondarysocket = portsock;
+      conn->sock[SECONDARYSOCKET] = portsock;
 
       if(!sa_filled_in) {
-        memset((char *)&sa, 0, sizeof(sa));
-        memcpy((char *)&sa.sin_addr,
-               h->addr->h_addr,
-               h->addr->h_length);
-        sa.sin_family = AF_INET;
+        memcpy(&sa, addr->ai_addr, sizeof(sa));
         sa.sin_addr.s_addr = INADDR_ANY;
       }
 
       sa.sin_port = 0;
       size = sizeof(sa);
-      
+
       if(bind(portsock, (struct sockaddr *)&sa, size) >= 0) {
         /* we succeeded to bind */
         struct sockaddr_in add;
-#ifdef __hpux     
-        int socksize = sizeof(add);
-#else 
         socklen_t socksize = sizeof(add);
-#endif
 
         if(getsockname(portsock, (struct sockaddr *) &add,
                        &socksize)<0) {
           failf(data, "getsockname() failed");
           return CURLE_FTP_PORT_FAILED;
         }
         porttouse = ntohs(add.sin_port);
-        
+
         if ( listen(portsock, 1) < 0 ) {
           failf(data, "listen(2) failed on socket");
           return CURLE_FTP_PORT_FAILED;
@@ -1296,39 +1373,34 @@ CURLcode ftp_use_port(struct connectdata *conn)
     }
   }
   else {
-    failf(data, "could't find my own IP address (%s)", myhost);
+    failf(data, "could't find IP address to use");
     return CURLE_FTP_PORT_FAILED;
   }
-  {
-#ifdef HAVE_INET_NTOA_R
-    char ntoa_buf[64];
-#endif
-    struct in_addr in;
-    unsigned short ip[5];
-    (void) memcpy(&in.s_addr,
-                  h?*h->addr->h_addr_list:(char *)&sa.sin_addr.s_addr,
-                  sizeof (in.s_addr));
-
-#ifdef HAVE_INET_NTOA_R
-    /* ignore the return code from inet_ntoa_r() as it is int or
-       char * depending on system */
-    inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf));
-    sscanf( ntoa_buf, "%hu.%hu.%hu.%hu",
-            &ip[0], &ip[1], &ip[2], &ip[3]);
-#else
-    sscanf( inet_ntoa(in), "%hu.%hu.%hu.%hu",
-            &ip[0], &ip[1], &ip[2], &ip[3]);
-#endif
+
+  if(sa_filled_in)
+    Curl_inet_ntop(AF_INET, &((struct sockaddr_in *)&sa)->sin_addr,
+                   myhost, sizeof(myhost));
+  else
+    Curl_printable_address(addr, myhost, sizeof(myhost));
+
+  if(4 == sscanf(myhost, "%hu.%hu.%hu.%hu",
+                 &ip[0], &ip[1], &ip[2], &ip[3])) {
+
     infof(data, "Telling server to connect to %d.%d.%d.%d:%d\n",
           ip[0], ip[1], ip[2], ip[3], porttouse);
-  
+
     result=Curl_ftpsendf(conn, "PORT %d,%d,%d,%d,%d,%d",
                          ip[0], ip[1], ip[2], ip[3],
                          porttouse >> 8,
                          porttouse & 255);
     if(result)
       return result;
+
   }
+  else
+    return CURLE_FTP_PORT_FAILED;
+
+  Curl_freeaddrinfo(addr);
 
   result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
   if(result)
@@ -1357,12 +1429,13 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
                       bool *connected)
 {
   struct SessionHandle *data = conn->data;
-  int nread;
+  ssize_t nread;
   char *buf = data->state.buffer; /* this is our buffer */
   int ftpcode; /* receive FTP response codes in this */
   CURLcode result;
   struct Curl_dns_entry *addr=NULL;
-  Curl_ipconnect *conninfo;
+  Curl_addrinfo *conninfo;
+  int rc;
 
   /*
     Here's the excecutive summary on what to do:
@@ -1378,27 +1451,17 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
 
   */
 
-#if 1
   const char *mode[] = { "EPSV", "PASV", NULL };
   int results[] = { 229, 227, 0 };
-#else
-#if 0
-  char *mode[] = { "EPSV", "LPSV", "PASV", NULL };
-  int results[] = { 229, 228, 227, 0 };
-#else
-  const char *mode[] = { "PASV", NULL };
-  int results[] = { 227, 0 };
-#endif
-#endif
   int modeoff;
   unsigned short connectport; /* the local port connect() should use! */
   unsigned short newport=0; /* remote port, not necessary the local one */
-  
+
   /* newhost must be able to hold a full IP-style address in ASCII, which
      in the IPv6 case means 5*8-1 = 39 letters */
   char newhost[48];
   char *newhostp=NULL;
-  
+
   for (modeoff = (data->set.ftp_use_epsv?0:1);
        mode[modeoff]; modeoff++) {
     result = Curl_ftpsendf(conn, "%s", mode[modeoff]);
@@ -1430,7 +1493,7 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
      * "227 Data transfer will passively listen to 127,0,0,1,4,51"
      * "227 Entering passive mode. 127,0,0,1,4,51"
      */
-      
+
     while(*str) {
       if (6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
                       &ip[0], &ip[1], &ip[2], &ip[3],
@@ -1444,11 +1507,11 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
       return CURLE_FTP_WEIRD_227_FORMAT;
     }
 
-    sprintf(newhost, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
+    snprintf(newhost, sizeof(newhost),
+             "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
     newhostp = newhost;
-    newport = (unsigned short)((port[0]<<8) + port[1]);
+    newport = (port[0]<<8) + port[1];
   }
-#if 1
   else if (229 == results[modeoff]) {
     char *ptr = strchr(buf, '(');
     if(ptr) {
@@ -1461,12 +1524,24 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
                       &separator[2],
                       &num,
                       &separator[3])) {
-        /* the four separators should be identical */
-        newport = (unsigned short)num;
+        char sep1 = separator[0];
+        int i;
+
+        /* The four separators should be identical, or else this is an oddly
+           formatted reply and we bail out immediately. */
+        for(i=1; i<4; i++) {
+          if(separator[i] != sep1) {
+            ptr=NULL; /* set to NULL to signal error */
+            break;
+          }
+        }
+        if(ptr) {
+          newport = num;
 
-        /* we should use the same host we already are connected to */
-        newhostp = conn->name;
-      }                      
+          /* we should use the same host we already are connected to */
+          newhostp = conn->host.name;
+        }
+      }
       else
         ptr=NULL;
     }
@@ -1475,63 +1550,68 @@ CURLcode ftp_use_pasv(struct connectdata *conn,
       return CURLE_FTP_WEIRD_PASV_REPLY;
     }
   }
-#endif
   else
     return CURLE_FTP_CANT_RECONNECT;
 
-  if(data->change.proxy) {
+  if(data->change.proxy && *data->change.proxy) {
     /*
      * This is a tunnel through a http proxy and we need to connect to the
      * proxy again here.
      *
      * We don't want to rely on a former host lookup that might've expired
      * now, instead we remake the lookup here and now!
      */
-    addr = Curl_resolv(data, conn->proxyhost, conn->port);
+    rc = Curl_resolv(conn, conn->proxy.name, (int)conn->port, &addr);
+    if(rc == CURLRESOLV_PENDING)
+      rc = Curl_wait_for_resolv(conn, &addr);
+
     connectport =
-      (unsigned short)conn->port; /* we connect to the proxy's port */    
+      (unsigned short)conn->port; /* we connect to the proxy's port */
 
   }
   else {
     /* normal, direct, ftp connection */
-    addr = Curl_resolv(data, newhostp, newport);
+    rc = Curl_resolv(conn, newhostp, newport, &addr);
+    if(rc == CURLRESOLV_PENDING)
+      rc = Curl_wait_for_resolv(conn, &addr);
+
     if(!addr) {
       failf(data, "Can't resolve new host %s:%d", newhostp, newport);
       return CURLE_FTP_CANT_GET_HOST;
     }
     connectport = newport; /* we connect to the remote port */
   }
-    
+
   result = Curl_connecthost(conn,
                             addr,
-                            connectport,
-                            &conn->secondarysocket,
+                            &conn->sock[SECONDARYSOCKET],
                             &conninfo,
                             connected);
 
-  Curl_resolv_unlock(addr); /* we're done using this address */
+  Curl_resolv_unlock(data, addr); /* we're done using this address */
+
+  if(result)
+    return result;
 
   /*
    * When this is used from the multi interface, this might've returned with
    * the 'connected' set to FALSE and thus we are now awaiting a non-blocking
    * connect to connect and we should not be "hanging" here waiting.
    */
-  
-  if((CURLE_OK == result) &&       
-     data->set.verbose)
+
+  if(data->set.verbose)
     /* this just dumps information about this second connection */
     ftp_pasv_verbose(conn, conninfo, newhostp, connectport);
-  
-  if(CURLE_OK != result)
-    return result;
 
-  if (data->set.tunnel_thru_httpproxy) {
+#ifndef CURL_DISABLE_HTTP
+  if(conn->bits.tunnel_proxy) {
     /* We want "seamless" FTP operations through HTTP proxy tunnel */
-    result = Curl_ConnectHTTPProxyTunnel(conn, conn->secondarysocket,
+    result = Curl_ConnectHTTPProxyTunnel(conn, SECONDARYSOCKET,
                                          newhostp, newport);
     if(CURLE_OK != result)
       return result;
   }
+#endif   /* CURL_DISABLE_HTTP */
 
   return CURLE_OK;
 }
@@ -1548,12 +1628,12 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
   struct SessionHandle *data=conn->data;
   char *buf = data->state.buffer; /* this is our buffer */
   CURLcode result;
-  int nread;
+  ssize_t nread;
   int ftpcode; /* for ftp status */
 
   /* the ftp struct is already inited in Curl_ftp_connect() */
   struct FTP *ftp = conn->proto.ftp;
-  long *bytecountp = ftp->bytecountp;
+  curl_off_t *bytecountp = ftp->bytecountp;
 
   if(data->set.upload) {
 
@@ -1585,7 +1665,7 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
       if(conn->resume_from < 0 ) {
         /* we could've got a specified offset from the command line,
            but now we know we didn't */
-        ssize_t gottensize;
+        curl_off_t gottensize;
 
         if(CURLE_OK != ftp_getsize(conn, ftp->file, &gottensize)) {
           failf(data, "Couldn't get remote file size");
@@ -1596,27 +1676,28 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
 
       if(conn->resume_from) {
         /* do we still game? */
-        int passed=0;
+        curl_off_t passed=0;
         /* enable append instead */
         data->set.ftp_append = 1;
 
         /* Now, let's read off the proper amount of bytes from the
            input. If we knew it was a proper file we could've just
            fseek()ed but we only have a stream here */
         do {
-          size_t readthisamountnow = (conn->resume_from - passed);
-          size_t actuallyread;
+          curl_off_t readthisamountnow = (conn->resume_from - passed);
+          curl_off_t actuallyread;
 
           if(readthisamountnow > BUFSIZE)
             readthisamountnow = BUFSIZE;
 
-          actuallyread = 
-            conn->fread(data->state.buffer, 1, readthisamountnow,
+          actuallyread = (curl_off_t)
+            conn->fread(data->state.buffer, 1, (size_t)readthisamountnow,
                         conn->fread_in);
 
-          passed += (int)actuallyread;
+          passed += actuallyread;
           if(actuallyread != readthisamountnow) {
-            failf(data, "Could only read %d bytes from the input", passed);
+            failf(data, "Could only read %" FORMAT_OFF_T
+                  " bytes from the input", passed);
             return CURLE_FTP_COULDNT_USE_REST;
           }
         }
@@ -1631,10 +1712,10 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
 
             /* no data to transfer */
             result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
-            
+
             /* Set no_transfer so that we won't get any error in
              * Curl_ftp_done() because we didn't transfer anything! */
-            ftp->no_transfer = TRUE; 
+            ftp->no_transfer = TRUE;
 
             return CURLE_OK;
           }
@@ -1664,11 +1745,20 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
 
     if(data->set.ftp_use_port) {
       /* PORT means we are now awaiting the server to connect to us. */
-      result = AllowServerConnect(data, conn, conn->secondarysocket);
+      result = AllowServerConnect(conn);
       if( result )
         return result;
     }
 
+    if(conn->ssl[SECONDARYSOCKET].use) {
+      /* since we only have a plaintext TCP connection here, we must now
+         do the TLS stuff */
+      infof(data, "Doing the SSL/TLS handshake on the data stream\n");
+      result = Curl_SSLConnect(conn, SECONDARYSOCKET);
+      if(result)
+        return result;
+    }
+
     *bytecountp=0;
 
     /* When we know we're uploading a specified file, we can get the file
@@ -1677,52 +1767,53 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
     Curl_pgrsSetUploadSize(data, data->set.infilesize);
 
     result = Curl_Transfer(conn, -1, -1, FALSE, NULL, /* no download */
-                      conn->secondarysocket, bytecountp);
+                           SECONDARYSOCKET, bytecountp);
     if(result)
       return result;
-      
+
   }
-  else if(!data->set.no_body) {
+  else if(!conn->bits.no_body) {
     /* Retrieve file or directory */
     bool dirlist=FALSE;
-    long downloadsize=-1;
+    curl_off_t downloadsize=-1;
 
     if(conn->bits.use_range && conn->range) {
-      long from, to;
-      int totalsize=-1;
+      curl_off_t from, to;
+      curl_off_t totalsize=-1;
       char *ptr;
       char *ptr2;
 
-      from=strtol(conn->range, &ptr, 0);
+      from=curlx_strtoofft(conn->range, &ptr, 0);
       while(ptr && *ptr && (isspace((int)*ptr) || (*ptr=='-')))
         ptr++;
-      to=strtol(ptr, &ptr2, 0);
+      to=curlx_strtoofft(ptr, &ptr2, 0);
       if(ptr == ptr2) {
         /* we didn't get any digit */
         to=-1;
       }
       if((-1 == to) && (from>=0)) {
         /* X - */
         conn->resume_from = from;
-        infof(data, "FTP RANGE %d to end of file\n", from);
+        infof(data, "FTP RANGE %" FORMAT_OFF_T " to end of file\n", from);
       }
       else if(from < 0) {
         /* -Y */
         totalsize = -from;
         conn->maxdownload = -from;
         conn->resume_from = from;
-        infof(data, "FTP RANGE the last %d bytes\n", totalsize);
+        infof(data, "FTP RANGE the last %" FORMAT_OFF_T " bytes\n", totalsize);
       }
       else {
         /* X-Y */
         totalsize = to-from;
         conn->maxdownload = totalsize+1; /* include the last mentioned byte */
         conn->resume_from = from;
-        infof(data, "FTP RANGE from %d getting %d bytes\n", from,
-              conn->maxdownload);
+        infof(data, "FTP RANGE from %" FORMAT_OFF_T
+              " getting %" FORMAT_OFF_T " bytes\n", from, conn->maxdownload);
       }
-      infof(data, "range-download from %d to %d, totally %d bytes\n",
-            from, to, totalsize);
+      infof(data, "range-download from %" FORMAT_OFF_T
+            " to %" FORMAT_OFF_T ", totally %" FORMAT_OFF_T " bytes\n",
+            from, to, conn->maxdownload);
       ftp->dont_check = TRUE; /* dont check for successful transfer */
     }
 
@@ -1746,14 +1837,14 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
             (data->set.ftp_list_only?"NLST":"LIST"));
     }
     else {
-      ssize_t foundsize;
+      curl_off_t foundsize;
 
       /* Set type to binary (unless specified ASCII) */
       result = ftp_transfertype(conn, data->set.ftp_ascii);
       if(result)
         return result;
 
-      /* Send any PREQUOTE strings after transfer type is set? (Wesley Laxton)*/
+      /* Send any PREQUOTE strings after transfer type is set? */
       if(data->set.prequote) {
         if ((result = ftp_sendquote(conn, data->set.prequote)) != CURLE_OK)
           return result;
@@ -1763,8 +1854,13 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
          downloads and when talking to servers that don't give away the size
          in the RETR response line. */
       result = ftp_getsize(conn, ftp->file, &foundsize);
-      if(CURLE_OK == result)
+      if(CURLE_OK == result) {
+        if (data->set.max_filesize && foundsize > data->set.max_filesize) {
+          failf(data, "Maximum file size exceeded");
+          return CURLE_FILESIZE_EXCEEDED;
+        }
         downloadsize = foundsize;
+      }
 
       if(conn->resume_from) {
 
@@ -1791,7 +1887,8 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
           if(conn->resume_from< 0) {
             /* We're supposed to download the last abs(from) bytes */
             if(foundsize < -conn->resume_from) {
-              failf(data, "Offset (%d) was beyond file size (%d)",
+              failf(data, "Offset (%" FORMAT_OFF_T
+                    ") was beyond file size (%" FORMAT_OFF_T ")",
                     conn->resume_from, foundsize);
               return CURLE_FTP_BAD_DOWNLOAD_RESUME;
             }
@@ -1802,7 +1899,8 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
           }
           else {
             if(foundsize < conn->resume_from) {
-              failf(data, "Offset (%d) was beyond file size (%d)",
+              failf(data, "Offset (%" FORMAT_OFF_T
+                    ") was beyond file size (%" FORMAT_OFF_T ")",
                     conn->resume_from, foundsize);
               return CURLE_FTP_BAD_DOWNLOAD_RESUME;
             }
@@ -1821,12 +1919,13 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
           ftp->no_transfer = TRUE;
           return CURLE_OK;
         }
-        
+
         /* Set resume file transfer offset */
-        infof(data, "Instructs server to resume from offset %d\n",
+        infof(data, "Instructs server to resume from offset %" FORMAT_OFF_T
+              "\n",
               conn->resume_from);
 
-        FTPSENDF(conn, "REST %d", conn->resume_from);
+        FTPSENDF(conn, "REST %" FORMAT_OFF_T, conn->resume_from);
 
         result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
         if(result)
@@ -1851,24 +1950,34 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
         A;
         150 Opening BINARY mode data connection for /etc/passwd (2241
         bytes).  (ok, the file is being transfered)
-        
+
         B:
-        150 Opening ASCII mode data connection for /bin/ls 
+        150 Opening ASCII mode data connection for /bin/ls
 
         C:
         150 ASCII data connection for /bin/ls (137.167.104.91,37445) (0 bytes).
 
         D:
         150 Opening ASCII mode data connection for /linux/fisk/kpanelrc (0.0.0.0,0) (545 bytes).
-          
+
         E:
         125 Data connection already open; Transfer starting. */
 
-      int size=-1; /* default unknown size */
+      curl_off_t size=-1; /* default unknown size */
+
+
+      /*
+       * It appears that there are FTP-servers that return size 0 for files
+       * when SIZE is used on the file while being in BINARY mode. To work
+       * around that (stupid) behavior, we attempt to parse the RETR response
+       * even if the SIZE returned size zero.
+       *
+       * Debugging help from Salvatore Sorrentino on February 26, 2003.
+       */
 
       if(!dirlist &&
          !data->set.ftp_ascii &&
-         (-1 == downloadsize)) {
+         (downloadsize < 1)) {
         /*
          * It seems directory listings either don't show the size or very
          * often uses size 0 anyway. ASCII transfers may very well turn out
@@ -1879,9 +1988,9 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
         char *bytes;
         bytes=strstr(buf, " bytes");
         if(bytes--) {
-          int index=(int)(bytes-buf);
+          long in=bytes-buf;
           /* this is a hint there is size information in there! ;-) */
-          while(--index) {
+          while(--in) {
             /* scan for the parenthesis and break there */
             if('(' == *bytes)
               break;
@@ -1896,34 +2005,52 @@ CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
           /* only if we have nothing but digits: */
           if(bytes++) {
             /* get the number! */
-            size = atoi(bytes);
+            size = curlx_strtoofft(bytes, NULL, 0);
           }
-            
+
         }
       }
       else if(downloadsize > -1)
         size = downloadsize;
 
       if(data->set.ftp_use_port) {
-        result = AllowServerConnect(data, conn, conn->secondarysocket);
+        result = AllowServerConnect(conn);
         if( result )
           return result;
       }
 
-      infof(data, "Getting file with size: %d\n", size);
+      if(conn->ssl[SECONDARYSOCKET].use) {
+        /* since we only have a plaintext TCP connection here, we must now
+           do the TLS stuff */
+        infof(data, "Doing the SSL/TLS handshake on the data stream\n");
+        result = Curl_SSLConnect(conn, SECONDARYSOCKET);
+        if(result)
+          return result;
+      }
+
+      if(size > conn->maxdownload && conn->maxdownload > 0)
+        size = conn->size = conn->maxdownload;
+
+      infof(data, "Getting file with size: %" FORMAT_OFF_T "\n", size);
 
       /* FTP download: */
-      result=Curl_Transfer(conn, conn->secondarysocket, size, FALSE,
+      result=Curl_Transfer(conn, SECONDARYSOCKET, size, FALSE,
                            bytecountp,
                            -1, NULL); /* no upload here */
       if(result)
         return result;
     }
     else {
-      failf(data, "%s", buf+4);
-      return CURLE_FTP_COULDNT_RETR_FILE;
+      if(dirlist && (ftpcode == 450)) {
+        /* simply no matching files */
+        ftp->no_transfer = TRUE; /* don't think we should download anything */
+      }
+      else {
+        failf(data, "%s", buf+4);
+        return CURLE_FTP_COULDNT_RETR_FILE;
+      }
     }
-        
+
   }
   /* end of transfer */
 
@@ -1956,39 +2083,76 @@ CURLcode ftp_perform(struct connectdata *conn,
     if ((result = ftp_sendquote(conn, data->set.quote)) != CURLE_OK)
       return result;
   }
-    
+
   /* This is a re-used connection. Since we change directory to where the
      transfer is taking place, we must now get back to the original dir
      where we ended up after login: */
   if (conn->bits.reuse && ftp->entrypath) {
-    if ((result = ftp_cwd(conn, ftp->entrypath)) != CURLE_OK)
+    if ((result = ftp_cwd_and_mkd(conn, ftp->entrypath)) != CURLE_OK)
       return result;
   }
 
-  /* change directory first! */
-  if(ftp->dir && ftp->dir[0]) {
-    if ((result = ftp_cwd(conn, ftp->dir)) != CURLE_OK)
+  {
+    int i; /* counter for loop */
+    for (i=0; i < ftp->dirdepth; i++) {
+      /* RFC 1738 says empty components should be respected too, but
+         that is plain stupid since CWD can't be used with an empty argument */
+      if ((result = ftp_cwd_and_mkd(conn, ftp->dirs[i])) != CURLE_OK)
         return result;
+    }
   }
 
-  /* Requested time of file? */
-  if(data->set.get_filetime && ftp->file) {
+  /* Requested time of file or time-depended transfer? */
+  if((data->set.get_filetime || data->set.timecondition) &&
+     ftp->file) {
     result = ftp_getfiletime(conn, ftp->file);
-    if(result)
-      return result;
+    switch( result )
+      {
+      case CURLE_FTP_COULDNT_RETR_FILE:
+      case CURLE_OK:
+        if(data->set.timecondition) {
+          if((data->info.filetime > 0) && (data->set.timevalue > 0)) {
+            switch(data->set.timecondition) {
+            case CURL_TIMECOND_IFMODSINCE:
+            default:
+              if(data->info.filetime < data->set.timevalue) {
+                infof(data, "The requested document is not new enough\n");
+                ftp->no_transfer = TRUE; /* mark this to not transfer data */
+                return CURLE_OK;
+              }
+              break;
+            case CURL_TIMECOND_IFUNMODSINCE:
+              if(data->info.filetime > data->set.timevalue) {
+                infof(data, "The requested document is not old enough\n");
+                ftp->no_transfer = TRUE; /* mark this to not transfer data */
+                return CURLE_OK;
+              }
+              break;
+            } /* switch */
+          }
+          else {
+            infof(data, "Skipping time comparison\n");
+          }
+        }
+        break;
+      default:
+        return result;
+      } /* switch */
   }
 
   /* If we have selected NOBODY and HEADER, it means that we only want file
      information. Which in FTP can't be much more than the file size and
      date. */
-  if(data->set.no_body && data->set.include_header && ftp->file) {
+  if(conn->bits.no_body && data->set.include_header && ftp->file) {
     /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
        may not support it! It is however the only way we have to get a file's
        size! */
-    ssize_t filesize;
+    curl_off_t filesize;
+    ssize_t nread;
+    int ftpcode;
 
     ftp->no_transfer = TRUE; /* this means no actual transfer is made */
-    
+
     /* Some servers return different sizes for different modes, and thus we
        must set the proper type before we check the size */
     result = ftp_transfertype(conn, data->set.ftp_ascii);
@@ -1999,26 +2163,40 @@ CURLcode ftp_perform(struct connectdata *conn,
     result = ftp_getsize(conn, ftp->file, &filesize);
 
     if(CURLE_OK == result) {
-      sprintf(buf, "Content-Length: %d\r\n", filesize);
+      snprintf(buf, sizeof(data->state.buffer),
+               "Content-Length: %" FORMAT_OFF_T "\r\n", filesize);
       result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
       if(result)
         return result;
     }
 
-    /* If we asked for a time of the file and we actually got one as
-       well, we "emulate" a HTTP-style header in our output. */
+    /* Determine if server can respond to REST command and therefore
+       whether it can do a range */
+    FTPSENDF(conn, "REST 0", NULL);
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+
+    if ((CURLE_OK == result) && (ftpcode == 350)) {
+      result = Curl_client_write(data, CLIENTWRITE_BOTH,
+                                 (char *)"Accept-ranges: bytes\r\n", 0);
+      if(result)
+        return result;
+    }
+
+    /* If we asked for a time of the file and we actually got one as
+       well, we "emulate" a HTTP-style header in our output. */
 
 #ifdef HAVE_STRFTIME
     if(data->set.get_filetime && (data->info.filetime>=0) ) {
       struct tm *tm;
-#ifdef HAVE_LOCALTIME_R
+      time_t clock = (time_t)data->info.filetime;
+#ifdef HAVE_GMTIME_R
       struct tm buffer;
-      tm = (struct tm *)localtime_r((time_t*)&data->info.filetime, &buffer);
+      tm = (struct tm *)gmtime_r(&clock, &buffer);
 #else
-      tm = localtime((time_t *)&data->info.filetime);
+      tm = gmtime(&clock);
 #endif
-      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n",
+      /* format: "Tue, 15 Nov 1994 12:45:26" */
+      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S GMT\r\n",
                tm);
       result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
       if(result)
@@ -2029,7 +2207,7 @@ CURLcode ftp_perform(struct connectdata *conn,
     return CURLE_OK;
   }
 
-  if(data->set.no_body)
+  if(conn->bits.no_body)
     /* doesn't really transfer any data */
     ftp->no_transfer = TRUE;
   /* Get us a second connection up and connected */
@@ -2045,10 +2223,10 @@ CURLcode ftp_perform(struct connectdata *conn,
   else {
     /* We have chosen (this is default) to use the PASV command */
     result = ftp_use_pasv(conn, connected);
-    if(connected)
+    if(CURLE_OK == result && *connected)
       infof(data, "Connected the data stream with PASV!\n");
   }
-  
+
   return result;
 }
 
@@ -2063,64 +2241,12 @@ CURLcode ftp_perform(struct connectdata *conn,
  */
 CURLcode Curl_ftp(struct connectdata *conn)
 {
-  CURLcode retcode;
-  bool connected;
-
-  struct SessionHandle *data = conn->data;
-  struct FTP *ftp;
-  int dirlength=0; /* 0 forces strlen() */
-
-  /* the ftp struct is already inited in ftp_connect() */
-  ftp = conn->proto.ftp;
-
-  /* We split the path into dir and file parts *before* we URLdecode
-     it */
-  ftp->file = strrchr(conn->ppath, '/');
-  if(ftp->file) {
-    if(ftp->file != conn->ppath)
-      /* don't count the traling slash */
-      dirlength=(int)(ftp->file-conn->ppath); 
+  CURLcode retcode = CURLE_OK;
 
-    ftp->file++; /* point to the first letter in the file name part or
-                    remain NULL */
-  }
-  else {
-    ftp->file = conn->ppath; /* there's only a file part */
-  }
-
-  if(*ftp->file) {
-    ftp->file = curl_unescape(ftp->file, 0);
-    if(NULL == ftp->file) {
-      failf(data, "no memory");
-      return CURLE_OUT_OF_MEMORY;
-    }
-  }
+  if (conn->sec_conn) /* 3rd party transfer */
+    retcode = ftp_3rdparty(conn);
   else
-    ftp->file=NULL; /* instead of point to a zero byte, we make it a NULL
-                       pointer */
-
-  ftp->urlpath = conn->ppath;
-  if(dirlength) {
-    ftp->dir = curl_unescape(ftp->urlpath, dirlength);
-    if(NULL == ftp->dir) {
-      if(ftp->file)
-        free(ftp->file);
-      failf(data, "no memory");
-      return CURLE_OUT_OF_MEMORY; /* failure */
-    }
-  }
-  else
-    ftp->dir = NULL;
-
-  retcode = ftp_perform(conn, &connected);
-
-  if(CURLE_OK == retcode) {
-    if(connected)
-      retcode = Curl_ftp_nextconnect(conn);
-    else
-      /* since we didn't connect now, we want do_more to get called */
-      conn->bits.do_more = TRUE;
-  }
+    retcode = ftp_regular_transfer(conn);
 
   return retcode;
 }
@@ -2139,43 +2265,68 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
 {
   ssize_t bytes_written;
   char s[256];
-  ssize_t write_len;
+  size_t write_len;
   char *sptr=s;
   CURLcode res = CURLE_OK;
 
   va_list ap;
   va_start(ap, fmt);
   vsnprintf(s, 250, fmt, ap);
   va_end(ap);
-  
+
   strcat(s, "\r\n"); /* append a trailing CRLF */
 
   bytes_written=0;
-  write_len = (int)strlen(s);
+  write_len = strlen(s);
 
-  do {
-    res = Curl_write(conn, conn->firstsocket, sptr, write_len,
+  while(1) {
+    res = Curl_write(conn, conn->sock[FIRSTSOCKET], sptr, write_len,
                      &bytes_written);
 
     if(CURLE_OK != res)
       break;
 
     if(conn->data->set.verbose)
-      Curl_debug(conn->data, CURLINFO_HEADER_OUT, sptr, bytes_written);
+      Curl_debug(conn->data, CURLINFO_HEADER_OUT, sptr, bytes_written, conn->host.dispname);
 
-    if(bytes_written != write_len) {
+    if(bytes_written != (ssize_t)write_len) {
       write_len -= bytes_written;
       sptr += bytes_written;
     }
     else
       break;
-  } while(1);
+  }
 
   return res;
 }
 
 /***********************************************************************
  *
+ * ftp_quit()
+ *
+ * This should be called before calling sclose() on an ftp control connection
+ * (not data connections). We should then wait for the response from the
+ * server before returning. The calling code should then try to close the
+ * connection.
+ *
+ */
+static CURLcode ftp_quit(struct connectdata *conn)
+{
+  ssize_t nread;
+  int ftpcode;
+  CURLcode ret = CURLE_OK;
+
+  if(conn->proto.ftp->ctl_valid) {
+    ret = Curl_ftpsendf(conn, "%s", "QUIT");
+    if(CURLE_OK == ret)
+      ret = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  }
+
+  return ret;
+}
+
+/***********************************************************************
+ *
  * Curl_ftp_disconnect()
  *
  * Disconnect from an FTP server. Cleanup protocol-specific per-connection
@@ -2185,28 +2336,424 @@ CURLcode Curl_ftp_disconnect(struct connectdata *conn)
 {
   struct FTP *ftp= conn->proto.ftp;
 
+  /* We cannot send quit unconditionally. If this connection is stale or
+     bad in any way, sending quit and waiting around here will make the
+     disconnect wait in vain and cause more problems than we need to.
+
+     ftp_quit() will check the state of ftp->ctl_valid. If it's ok it
+     will try to send the QUIT command, otherwise it will just return.
+  */
+
   /* The FTP session may or may not have been allocated/setup at this point! */
   if(ftp) {
+    (void)ftp_quit(conn); /* ignore errors on the QUIT */
+
     if(ftp->entrypath)
       free(ftp->entrypath);
-    if(ftp->cache)
+    if(ftp->cache) {
       free(ftp->cache);
-    if(ftp->file)
-      free(ftp->file);
-    if(ftp->dir)
-      free(ftp->dir);
+      ftp->cache = NULL;
+    }
+    freedirs(ftp);
+  }
+  return CURLE_OK;
+}
+
+/***********************************************************************
+ *
+ * ftp_mkd()
+ *
+ * Makes a directory on the FTP server.
+ *
+ * Calls failf()
+ */
+static CURLcode ftp_mkd(struct connectdata *conn, char *path)
+{
+  CURLcode result=CURLE_OK;
+  int ftpcode; /* for ftp status */
+  ssize_t nread;
+
+  /* Create a directory on the remote server */
+  FTPSENDF(conn, "MKD %s", path);
 
-    ftp->file = ftp->dir = NULL; /* zero */
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if(result)
+    return result;
+
+  switch(ftpcode) {
+  case 257:
+    /* success! */
+    infof( conn->data , "Created remote directory %s\n" , path );
+    break;
+  case 550:
+    failf(conn->data, "Permission denied to make directory %s", path);
+    result = CURLE_FTP_ACCESS_DENIED;
+    break;
+  default:
+    failf(conn->data, "unrecognized MKD response: %d", ftpcode );
+    result = CURLE_FTP_ACCESS_DENIED;
+    break;
   }
+  return  result;
+}
+
+/***********************************************************************
+ *
+ * ftp_cwd()
+ *
+ * Send 'CWD' to the remote server to Change Working Directory.  It is the ftp
+ * version of the unix 'cd' command. This function is only called from the
+ * ftp_cwd_and_mkd() function these days.
+ *
+ * This function does NOT call failf().
+ */
+static
+CURLcode ftp_cwd(struct connectdata *conn, char *path)
+{
+  ssize_t nread;
+  int     ftpcode;
+  CURLcode result;
+
+  FTPSENDF(conn, "CWD %s", path);
+  result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+  if (!result) {
+    /* According to RFC959, CWD is supposed to return 250 on success, but
+       there seem to be non-compliant FTP servers out there that return 200,
+       so we accept any '2xy' code here. */
+    if (ftpcode/100 != 2)
+      result = CURLE_FTP_ACCESS_DENIED;
+  }
+
+  return result;
+}
+
+/***********************************************************************
+ *
+ * ftp_cwd_and_mkd()
+ *
+ * Change to the given directory.  If the directory is not present, and we
+ * have been told to allow it, then create the directory and cd to it.
+ *
+ */
+static CURLcode ftp_cwd_and_mkd(struct connectdata *conn, char *path)
+{
+  CURLcode result;
+
+  result = ftp_cwd(conn, path);
+  if (result) {
+    if(conn->data->set.ftp_create_missing_dirs) {
+      result = ftp_mkd(conn, path);
+      if (result)
+        /* ftp_mkd() calls failf() itself */
+        return result;
+      result = ftp_cwd(conn, path);
+    }
+    if(result)
+      failf(conn->data, "Couldn't cd to %s", path);
+  }
+  return result;
+}
+
+
+
+/***********************************************************************
+ *
+ * ftp_3rdparty_pretransfer()
+ *
+ * Preparation for 3rd party transfer.
+ *
+ */
+static CURLcode ftp_3rdparty_pretransfer(struct connectdata *conn)
+{
+  CURLcode result = CURLE_OK;
+  struct SessionHandle *data = conn->data;
+  struct connectdata *sec_conn = conn->sec_conn;
+
+  /* sets transfer type */
+  result = ftp_transfertype(conn, data->set.ftp_ascii);
+  if (result)
+    return result;
+
+  result = ftp_transfertype(sec_conn, data->set.ftp_ascii);
+  if (result)
+    return result;
+
+  /* Send any PREQUOTE strings after transfer type is set? */
+  if (data->set.source_prequote) {
+    /* sends command(s) to source server before file transfer */
+    result = ftp_sendquote(sec_conn, data->set.source_prequote);
+  }
+  if (!result && data->set.prequote)
+    result = ftp_sendquote(conn, data->set.prequote);
+
+  return result;
+}
+
+
+
+/***********************************************************************
+ *
+ * ftp_3rdparty_transfer()
+ *
+ * Performs 3rd party transfer.
+ *
+ */
+static CURLcode ftp_3rdparty_transfer(struct connectdata *conn)
+{
+  CURLcode result = CURLE_OK;
+  ssize_t nread;
+  int ftpcode, ip[4], port[2];
+  struct SessionHandle *data = conn->data;
+  struct connectdata *sec_conn = conn->sec_conn;
+  char *buf = data->state.buffer;   /* this is our buffer */
+  char *str = buf;
+  char pasv_port[50];
+  const char *stor_cmd;
+  struct connectdata *pasv_conn;
+  struct connectdata *port_conn;
+
+  if (data->set.pasvHost == CURL_TARGET_PASV) {
+    pasv_conn = conn;
+    port_conn = sec_conn;
+  }
+  else {
+    pasv_conn = sec_conn;
+    port_conn = conn;
+  }
+
+  /* sets the passive mode */
+  FTPSENDF(pasv_conn, "%s", "PASV");
+  result = Curl_GetFTPResponse(&nread, pasv_conn, &ftpcode);
+  if (result) return result;
+  if (ftpcode != 227) {
+    failf(data, "Odd return code after PASV:%s", buf + 3);
+    return CURLE_FTP_WEIRD_PASV_REPLY;
+  }
+
+  while (*str) {
+    if (6 == sscanf(str, "%d,%d,%d,%d,%d,%d",
+                    &ip[0], &ip[1], &ip[2], &ip[3], &port[0], &port[1]))
+      break;
+    str++;
+  }
+
+  if (!*str) {
+    failf(pasv_conn->data, "Couldn't interpret this 227-reply: %s", buf);
+    return CURLE_FTP_WEIRD_227_FORMAT;
+  }
+
+  snprintf(pasv_port, sizeof(pasv_port), "%d,%d,%d,%d,%d,%d", ip[0], ip[1],
+           ip[2], ip[3], port[0], port[1]);
+
+  /* sets data connection between remote hosts */
+  FTPSENDF(port_conn, "PORT %s", pasv_port);
+  result = Curl_GetFTPResponse(&nread, port_conn, &ftpcode);
+  if (result)
+    return result;
+
+  if (ftpcode != 200) {
+    failf(data, "PORT command attempts failed:%s", buf + 3);
+    return CURLE_FTP_PORT_FAILED;
+  }
+
+  /* we might append onto the file instead of overwriting it */
+  stor_cmd = data->set.ftp_append?"APPE":"STOR";
+
+  /* transfers file between remote hosts */
+  FTPSENDF(sec_conn, "RETR %s", data->set.source_path);
+
+  if(data->set.pasvHost == CURL_TARGET_PASV) {
+
+    result = Curl_GetFTPResponse(&nread, sec_conn, &ftpcode);
+    if (result)
+      return result;
+
+    if (ftpcode != 150) {
+      failf(data, "Failed RETR: %s", buf + 4);
+      return CURLE_FTP_COULDNT_RETR_FILE;
+    }
+
+    result = Curl_ftpsendf(conn, "%s %s", stor_cmd, conn->path);
+    if(CURLE_OK == result)
+      result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if (result)
+      return result;
+
+    if (ftpcode != 150) {
+      failf(data, "Failed FTP upload: %s", buf + 4);
+      return CURLE_FTP_COULDNT_STOR_FILE;
+    }
+
+  }
+  else {
+
+    result = Curl_ftpsendf(conn, "%s %s", stor_cmd, conn->path);
+    if(CURLE_OK == result)
+      result = Curl_GetFTPResponse(&nread, sec_conn, &ftpcode);
+    if (result)
+      return result;
+
+    if (ftpcode != 150) {
+      failf(data, "Failed FTP upload: %s", buf + 4);
+      return CURLE_FTP_COULDNT_STOR_FILE;
+    }
+
+    result = Curl_GetFTPResponse(&nread, conn, &ftpcode);
+    if (result)
+      return result;
+
+    if (ftpcode != 150) {
+      failf(data, "Failed FTP upload: %s", buf + 4);
+      return CURLE_FTP_COULDNT_STOR_FILE;
+    }
+  }
+
   return CURLE_OK;
 }
 
-/*
- * local variables:
- * eval: (load-file "../curl-mode.el")
- * end:
- * vim600: fdm=marker
- * vim: et sw=2 ts=2 sts=2 tw=78
+
+
+/***********************************************************************
+ *
+ * ftp_regular_transfer()
+ *
+ * The input argument is already checked for validity.
+ * Performs a regular transfer between local and remote hosts.
+ *
+ * ftp->ctl_valid starts out as FALSE, and gets set to TRUE if we reach the
+ * Curl_ftp_done() function without finding any major problem.
+ */
+static
+CURLcode ftp_regular_transfer(struct connectdata *conn)
+{
+  CURLcode retcode=CURLE_OK;
+  bool connected=0;
+  struct SessionHandle *data = conn->data;
+  struct FTP *ftp;
+
+  char *slash_pos;  /* position of the first '/' char in curpos */
+  char *cur_pos=conn->path; /* current position in ppath. point at the begin
+                               of next path component */
+
+  /* the ftp struct is already inited in ftp_connect() */
+  ftp = conn->proto.ftp;
+  ftp->ctl_valid = FALSE;
+  conn->size = -1; /* make sure this is unknown at this point */
+
+  Curl_pgrsSetUploadCounter(data, 0);
+  Curl_pgrsSetDownloadCounter(data, 0);
+  Curl_pgrsSetUploadSize(data, 0);
+  Curl_pgrsSetDownloadSize(data, 0);
+
+  ftp->dirdepth = 0;
+  ftp->diralloc = 5; /* default dir depth to allocate */
+  ftp->dirs = (char **)malloc(ftp->diralloc * sizeof(ftp->dirs[0]));
+  if(!ftp->dirs)
+    return CURLE_OUT_OF_MEMORY;
+  ftp->dirs[0] = NULL; /* to start with */
+
+  /* parse the URL path into separate path components */
+  while((slash_pos=strchr(cur_pos, '/'))) {
+    /* 1 or 0 to indicate absolute directory */
+    bool absolute_dir = (cur_pos - conn->path > 0) && (ftp->dirdepth == 0);
+
+    /* seek out the next path component */
+    if (slash_pos-cur_pos) {
+      /* we skip empty path components, like "x//y" since the FTP command CWD
+         requires a parameter and a non-existant parameter a) doesn't work on
+         many servers and b) has no effect on the others. */
+      int len = (int)(slash_pos - cur_pos + absolute_dir);
+      ftp->dirs[ftp->dirdepth] = curl_unescape(cur_pos - absolute_dir, len);
+
+      if (!ftp->dirs[ftp->dirdepth]) { /* run out of memory ... */
+        failf(data, "no memory");
+        freedirs(ftp);
+        return CURLE_OUT_OF_MEMORY;
+      }
+    }
+    else {
+      cur_pos = slash_pos + 1; /* jump to the rest of the string */
+      continue;
+    }
+
+    if(!retcode) {
+      cur_pos = slash_pos + 1; /* jump to the rest of the string */
+      if(++ftp->dirdepth >= ftp->diralloc) {
+        /* enlarge array */
+        char *bigger;
+        ftp->diralloc *= 2; /* double the size each time */
+        bigger = realloc(ftp->dirs, ftp->diralloc * sizeof(ftp->dirs[0]));
+        if(!bigger) {
+          freedirs(ftp);
+          return CURLE_OUT_OF_MEMORY;
+        }
+        ftp->dirs = (char **)bigger;
+      }
+    }
+  }
+
+  ftp->file = cur_pos;  /* the rest is the file name */
+
+  if(*ftp->file) {
+    ftp->file = curl_unescape(ftp->file, 0);
+    if(NULL == ftp->file) {
+      freedirs(ftp);
+      failf(data, "no memory");
+      return CURLE_OUT_OF_MEMORY;
+    }
+  }
+  else
+    ftp->file=NULL; /* instead of point to a zero byte, we make it a NULL
+                       pointer */
+
+  retcode = ftp_perform(conn, &connected);
+
+  if(CURLE_OK == retcode) {
+    if(connected)
+      retcode = Curl_ftp_nextconnect(conn);
+
+    if(retcode && (conn->sock[SECONDARYSOCKET] != CURL_SOCKET_BAD)) {
+      /* Failure detected, close the second socket if it was created already */
+      sclose(conn->sock[SECONDARYSOCKET]);
+      conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
+    }
+
+    if(ftp->no_transfer)
+      /* no data to transfer */
+      retcode=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
+    else if(!connected)
+      /* since we didn't connect now, we want do_more to get called */
+      conn->bits.do_more = TRUE;
+  }
+  else
+    freedirs(ftp);
+
+  ftp->ctl_valid = TRUE; /* seems good */
+
+  return retcode;
+}
+
+
+
+/***********************************************************************
+ *
+ * ftp_3rdparty()
+ *
+ * The input argument is already checked for validity.
+ * Performs a 3rd party transfer between two remote hosts.
  */
+static CURLcode ftp_3rdparty(struct connectdata *conn)
+{
+  CURLcode retcode = CURLE_OK;
+
+  conn->proto.ftp->ctl_valid = conn->sec_conn->proto.ftp->ctl_valid = TRUE;
+  conn->size = conn->sec_conn->size = -1;
+
+  retcode = ftp_3rdparty_pretransfer(conn);
+  if (!retcode)
+    retcode = ftp_3rdparty_transfer(conn);
+
+  return retcode;
+}
 
 #endif /* CURL_DISABLE_FTP */