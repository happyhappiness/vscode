@@ -1,28 +1,29 @@
-/*****************************************************************************
+/***************************************************************************
  *                                  _   _ ____  _     
  *  Project                     ___| | | |  _ \| |    
  *                             / __| | | | |_) | |    
  *                            | (__| |_| |  _ <| |___ 
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 2001, Daniel Stenberg, <daniel@haxx.se>, et al.
- *
- * In order to be useful for every potential user, curl and libcurl are
- * dual-licensed under the MPL and the MIT/X-derivate licenses.
+ * Copyright (C) 1998 - 2002, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
+ * This software is licensed as described in the file COPYING, which
+ * you should have received as part of this distribution. The terms
+ * are also available at http://curl.haxx.se/docs/copyright.html.
+ * 
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
- * furnished to do so, under the terms of the MPL or the MIT/X-derivate
- * licenses. You may pick one of these licenses.
+ * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
  * $Id$
- *****************************************************************************/
+ ***************************************************************************/
 
 #include "setup.h"
 
+#ifndef CURL_DISABLE_FTP
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
@@ -210,16 +211,6 @@ int Curl_GetFTPResponse(char *buf,
   if (ftpcode)
     *ftpcode = 0; /* 0 for errors */
 
-  if(data->set.timeout) {
-    /* if timeout is requested, find out how much remaining time we have */
-    timeout = data->set.timeout - /* timeout time */
-      Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
-    if(timeout <=0 ) {
-      failf(data, "Transfer aborted due to timeout");
-      return -SELECT_TIMEOUT; /* already too little time */
-    }
-  }
-
   FD_ZERO (&readfd);            /* clear it */
   FD_SET (sockfd, &readfd);     /* read socket */
 
@@ -235,11 +226,22 @@ int Curl_GetFTPResponse(char *buf,
   keepon=TRUE;
 
   while((nread<BUFSIZE) && (keepon && !error)) {
-    readfd = rkeepfd;              /* set every lap */
-    interval.tv_sec = timeout;
-    interval.tv_usec = 0;
+    /* check and reset timeout value every lap */
+    if(data->set.timeout) {
+      /* if timeout is requested, find out how much remaining time we have */
+      timeout = data->set.timeout - /* timeout time */
+        Curl_tvdiff(Curl_tvnow(), conn->now)/1000; /* spent time */
+      if(timeout <=0 ) {
+        failf(data, "Transfer aborted due to timeout");
+        return -SELECT_TIMEOUT; /* already too little time */
+      }
+    }
+
+    if(!ftp->cache) {
+      readfd = rkeepfd;            /* set every lap */
+      interval.tv_sec = timeout;
+      interval.tv_usec = 0;
 
-    if(!ftp->cache)
       switch (select (sockfd+1, &readfd, NULL, NULL, &interval)) {
       case -1: /* select() error, stop reading */
         error = SELECT_ERROR;
@@ -253,6 +255,7 @@ int Curl_GetFTPResponse(char *buf,
         error = SELECT_OK;
         break;
       }
+    }
     if(SELECT_OK == error) {
       /*
        * This code previously didn't use the kerberos sec_read() code
@@ -301,11 +304,8 @@ int Curl_GetFTPResponse(char *buf,
             CURLcode result;
 
             /* output debug output if that is requested */
-            if(data->set.verbose) {
-              fputs("< ", data->set.err);
-              fwrite(line_start, perline, 1, data->set.err);
-              /* no need to output LF here, it is part of the data */
-            }
+            if(data->set.verbose)
+              Curl_debug(data, CURLINFO_HEADER_IN, line_start, perline);
 
             /*
              * We pass all response-lines to the callback function registered
@@ -387,33 +387,10 @@ int Curl_GetFTPResponse(char *buf,
   return nread; /* total amount of bytes read */
 }
 
-#ifndef ENABLE_IPV6
 /*
- * This function is only used by code that works on IPv4. When we add proper
- * support for that functionality with IPv6, this function can go in again.
+ * Curl_ftp_connect() should do everything that is to be considered a part of
+ * the connection phase.
  */
-/* -- who are we? -- */
-static char *getmyhost(char *buf, int buf_size)
-{
-#if defined(HAVE_GETHOSTNAME)
-  gethostname(buf, buf_size);
-#elif defined(HAVE_UNAME)
-  struct utsname ugnm;
-  strncpy(buf, uname(&ugnm) < 0 ? "localhost" : ugnm.nodename, buf_size - 1);
-  buf[buf_size - 1] = '\0';
-#else
-  /* We have no means of finding the local host name! */
-  strncpy(buf, "localhost", buf_size);
-  buf[buf_size - 1] = '\0';
-#endif
-  return buf;
-}
-
-#endif /* ipv4-only function */
-
-
-/* ftp_connect() should do everything that is to be considered a part
-   of the connection phase. */
 CURLcode Curl_ftp_connect(struct connectdata *conn)
 {
   /* this is FTP and no proxy */
@@ -622,8 +599,10 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
   CURLcode result=CURLE_OK;
 
   if(data->set.upload) {
-    if((-1 != data->set.infilesize) && (data->set.infilesize != *ftp->bytecountp)) {
-      failf(data, "Wrote only partial file (%d out of %d bytes)",
+    if((-1 != data->set.infilesize) &&
+       (data->set.infilesize != *ftp->bytecountp) &&
+       !data->set.crlf) {
+      failf(data, "Uploaded unaligned file size (%d out of %d bytes)",
             *ftp->bytecountp, data->set.infilesize);
       return CURLE_PARTIAL_FILE;
     }
@@ -634,9 +613,9 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
       failf(data, "Received only partial file: %d bytes", *ftp->bytecountp);
       return CURLE_PARTIAL_FILE;
     }
-    else if(!conn->bits.resume_done &&
-            !data->set.no_body &&
-            (0 == *ftp->bytecountp)) {
+    else if(!ftp->dont_check &&
+            !*ftp->bytecountp &&
+            (conn->size>0)) {
       /* We consider this an error, but there's no true FTP error received
          why we need to continue to "read out" the server response too.
          We don't want to leave a "waiting" server reply if we'll get told
@@ -653,21 +632,25 @@ CURLcode Curl_ftp_done(struct connectdata *conn)
   sclose(conn->secondarysocket);
   conn->secondarysocket = -1;
 
-  if(!data->set.no_body && !conn->bits.resume_done) {  
-    /* now let's see what the server says about the transfer we
-       just performed: */
+  if(!ftp->no_transfer) {
+    /* now let's see what the server says about the transfer we just
+       performed: */
     nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
     if(nread < 0)
       return CURLE_OPERATION_TIMEOUTED;
 
-    /* 226 Transfer complete, 250 Requested file action okay, completed. */
-    if((ftpcode != 226) && (ftpcode != 250)) {
-      failf(data, "server did not report OK, got %d", ftpcode);
-      return CURLE_FTP_WRITE_ERROR;
+    if(!ftp->dont_check) {
+      /* 226 Transfer complete, 250 Requested file action okay, completed. */
+      if((ftpcode != 226) && (ftpcode != 250)) {
+        failf(data, "server did not report OK, got %d", ftpcode);
+        return CURLE_FTP_WRITE_ERROR;
+      }
     }
   }
 
-  conn->bits.resume_done = FALSE; /* clean this for next connection */
+  /* clear these for next connection */
+  ftp->no_transfer = FALSE;
+  ftp->dont_check = FALSE; 
 
   /* Send any post-transfer QUOTE strings? */
   if(!result && data->set.postquote)
@@ -728,8 +711,7 @@ CURLcode ftp_cwd(struct connectdata *conn, char *path)
   CURLcode result;
   
   FTPSENDF(conn, "CWD %s", path);
-  nread = Curl_GetFTPResponse(
-                              conn->data->state.buffer, conn, &ftpcode);
+  nread = Curl_GetFTPResponse(conn->data->state.buffer, conn, &ftpcode);
   if (nread < 0)
     return CURLE_OPERATION_TIMEOUTED;
 
@@ -898,31 +880,35 @@ ftp_pasv_verbose(struct connectdata *conn,
   /* Bjorn Reese (November 28 2001):
      The Tru64 man page on gethostbyaddr_r() says that
      the hostent struct must be filled with zeroes before the call to
-     gethostbyaddr_r(). */
+     gethostbyaddr_r(). 
+
+     ... as must be struct hostent_data Craig Markwardt 19 Sep 2002. */
 
-  memset(hostent_buf, 0, sizeof(struct hostent));
+  memset(hostent_buf, 0, sizeof(struct hostent)+sizeof(struct hostent_data));
 
   if(gethostbyaddr_r((char *) &address,
                      sizeof(address), AF_INET,
                      (struct hostent *)hostent_buf,
-                     hostent_buf + sizeof(*answer)))
+                     (struct hostent_data *)(hostent_buf + sizeof(*answer))))
     answer=NULL;
+  else
+    answer=(struct hostent *)hostent_buf;
                            
 #  endif
 #  ifdef HAVE_GETHOSTBYADDR_R_7
   /* Solaris and IRIX */
   answer = gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,
                            (struct hostent *)bigbuf,
                            hostent_buf + sizeof(*answer),
-                           sizeof(hostent_buf) - sizeof(*answer),
+                           sizeof(bigbuf) - sizeof(*answer),
                            &h_errnop);
 #  endif
 #  ifdef HAVE_GETHOSTBYADDR_R_8
   /* Linux style */
   if(gethostbyaddr_r((char *) &address, sizeof(address), AF_INET,
                      (struct hostent *)hostent_buf,
                      hostent_buf + sizeof(*answer),
-                     sizeof(hostent_buf) - sizeof(*answer),
+                     sizeof(bigbuf) - sizeof(*answer),
                      &answer,
                      &h_errnop))
     answer=NULL; /* error */
@@ -1013,7 +999,6 @@ CURLcode ftp_use_port(struct connectdata *conn)
 #endif
   unsigned char *ap;
   unsigned char *pp;
-  int alen, plen;
   char portmsgbuf[4096], tmp[4096];
 
   const char *mode[] = { "EPRT", "LPRT", "PORT", NULL };
@@ -1064,18 +1049,19 @@ CURLcode ftp_use_port(struct connectdata *conn)
   }
   freeaddrinfo(res);
   if (portsock < 0) {
-    failf(data, strerror(errno));
+    failf(data, "%s", strerror(errno));
     return CURLE_FTP_PORT_FAILED;
   }
 
   sslen = sizeof(ss);
   if (getsockname(portsock, sa, &sslen) < 0) {
-    failf(data, strerror(errno));
+    failf(data, "%s", strerror(errno));
     return CURLE_FTP_PORT_FAILED;
   }
 
   for (modep = (char **)mode; modep && *modep; modep++) {
     int lprtaf, eprtaf;
+    int alen=0, plen=0;
     
     switch (sa->sa_family) {
     case AF_INET:
@@ -1197,30 +1183,42 @@ CURLcode ftp_use_port(struct connectdata *conn)
    *
    */
   struct sockaddr_in sa;
-  struct hostent *h=NULL;
-  char *hostdataptr=NULL;
+  struct Curl_dns_entry *h=NULL;
   unsigned short porttouse;
   char myhost[256] = "";
+  bool sa_filled_in = FALSE;
 
   if(data->set.ftpport) {
     if(Curl_if2ip(data->set.ftpport, myhost, sizeof(myhost))) {
-      h = Curl_resolv(data, myhost, 0, &hostdataptr);
+      h = Curl_resolv(data, myhost, 0);
     }
     else {
       int len = strlen(data->set.ftpport);
       if(len>1)
-        h = Curl_resolv(data, data->set.ftpport, 0, &hostdataptr);
+        h = Curl_resolv(data, data->set.ftpport, 0);
       if(h)
         strcpy(myhost, data->set.ftpport); /* buffer overflow risk */
     }
   }
   if(! *myhost) {
-    char *tmp_host = getmyhost(myhost, sizeof(myhost));
-    h=Curl_resolv(data, tmp_host, 0, &hostdataptr);
+    /* pick a suitable default here */
+
+    socklen_t sslen;
+    
+    sslen = sizeof(sa);
+    if (getsockname(conn->firstsocket, (struct sockaddr *)&sa, &sslen) < 0) {
+      failf(data, "getsockname() failed");
+      return CURLE_FTP_PORT_FAILED;
+    }
+
+    sa_filled_in = TRUE; /* the sa struct is filled in */
   }
-  infof(data, "We connect from %s\n", myhost);
-  
-  if ( h ) {
+
+  if(h)
+    /* when we return from here, we can forget about this */
+    Curl_resolv_unlock(h);
+
+  if ( h || sa_filled_in) {
     if( (portsock = socket(AF_INET, SOCK_STREAM, 0)) >= 0 ) {
       int size;
       
@@ -1229,12 +1227,15 @@ CURLcode ftp_use_port(struct connectdata *conn)
          we fail before the true secondary stuff is made */
       conn->secondarysocket = portsock;
 
-      memset((char *)&sa, 0, sizeof(sa));
-      memcpy((char *)&sa.sin_addr,
-             h->h_addr,
-             h->h_length);
-      sa.sin_family = AF_INET;
-      sa.sin_addr.s_addr = INADDR_ANY;
+      if(!sa_filled_in) {
+        memset((char *)&sa, 0, sizeof(sa));
+        memcpy((char *)&sa.sin_addr,
+               h->addr->h_addr,
+               h->addr->h_length);
+        sa.sin_family = AF_INET;
+        sa.sin_addr.s_addr = INADDR_ANY;
+      }
+
       sa.sin_port = 0;
       size = sizeof(sa);
       
@@ -1252,19 +1253,16 @@ CURLcode ftp_use_port(struct connectdata *conn)
         
         if ( listen(portsock, 1) < 0 ) {
           failf(data, "listen(2) failed on socket");
-          free(hostdataptr);
           return CURLE_FTP_PORT_FAILED;
         }
       }
       else {
         failf(data, "bind(2) failed on socket");
-        free(hostdataptr);
         return CURLE_FTP_PORT_FAILED;
       }
     }
     else {
       failf(data, "socket(2) failed (%s)");
-      free(hostdataptr);
       return CURLE_FTP_PORT_FAILED;
     }
   }
@@ -1278,7 +1276,10 @@ CURLcode ftp_use_port(struct connectdata *conn)
 #endif
     struct in_addr in;
     unsigned short ip[5];
-    (void) memcpy(&in.s_addr, *h->h_addr_list, sizeof (in.s_addr));
+    (void) memcpy(&in.s_addr,
+                  h?*h->addr->h_addr_list:(char *)&sa.sin_addr.s_addr,
+                  sizeof (in.s_addr));
+
 #ifdef HAVE_INET_NTOA_R
     /* ignore the return code from inet_ntoa_r() as it is int or
        char * depending on system */
@@ -1289,6 +1290,9 @@ CURLcode ftp_use_port(struct connectdata *conn)
     sscanf( inet_ntoa(in), "%hu.%hu.%hu.%hu",
             &ip[0], &ip[1], &ip[2], &ip[3]);
 #endif
+    infof(data, "Telling server to connect to %d.%d.%d.%d:%d\n",
+          ip[0], ip[1], ip[2], ip[3], porttouse);
+  
     result=Curl_ftpsendf(conn, "PORT %d,%d,%d,%d,%d,%d",
                          ip[0], ip[1], ip[2], ip[3],
                          porttouse >> 8,
@@ -1320,14 +1324,15 @@ CURLcode ftp_use_port(struct connectdata *conn)
  */
 
 static
-CURLcode ftp_use_pasv(struct connectdata *conn)
+CURLcode ftp_use_pasv(struct connectdata *conn,
+                      bool *connected)
 {
   struct SessionHandle *data = conn->data;
   ssize_t nread;
   char *buf = data->state.buffer; /* this is our buffer */
   int ftpcode; /* receive FTP response codes in this */
   CURLcode result;
-  Curl_addrinfo *addr=NULL;
+  struct Curl_dns_entry *addr=NULL;
   Curl_ipconnect *conninfo;
 
   /*
@@ -1358,8 +1363,7 @@ CURLcode ftp_use_pasv(struct connectdata *conn)
 #endif
   int modeoff;
   unsigned short connectport; /* the local port connect() should use! */
-  unsigned short newport; /* remote port, not necessary the local one */
-  char *hostdataptr=NULL;
+  unsigned short newport=0; /* remote port, not necessary the local one */
   
   /* newhost must be able to hold a full IP-style address in ASCII, which
      in the IPv6 case means 5*8-1 = 39 letters */
@@ -1368,7 +1372,7 @@ CURLcode ftp_use_pasv(struct connectdata *conn)
   
   for (modeoff = (data->set.ftp_use_epsv?0:1);
        mode[modeoff]; modeoff++) {
-    result = Curl_ftpsendf(conn, mode[modeoff]);
+    result = Curl_ftpsendf(conn, "%s", mode[modeoff]);
     if(result)
       return result;
     nread = Curl_GetFTPResponse(buf, conn, &ftpcode);
@@ -1449,18 +1453,21 @@ CURLcode ftp_use_pasv(struct connectdata *conn)
   if(data->change.proxy) {
     /*
      * This is a tunnel through a http proxy and we need to connect to the
-     * proxy again here. We already have the name info for it since the
-     * previous lookup.
+     * proxy again here.
+     *
+     * We don't want to rely on a former host lookup that might've expired
+     * now, instead we remake the lookup here and now!
      */
-    addr = conn->hostaddr;
+    addr = Curl_resolv(data, conn->proxyhost, conn->port);
     connectport =
-      (unsigned short)conn->port; /* we connect to the proxy's port */
+      (unsigned short)conn->port; /* we connect to the proxy's port */    
+
   }
   else {
     /* normal, direct, ftp connection */
-    addr = Curl_resolv(data, newhostp, newport, &hostdataptr);
+    addr = Curl_resolv(data, newhostp, newport);
     if(!addr) {
-      failf(data, "Can't resolve new host %s", newhost);
+      failf(data, "Can't resolve new host %s:%d", newhostp, newport);
       return CURLE_FTP_CANT_GET_HOST;
     }
     connectport = newport; /* we connect to the remote port */
@@ -1470,146 +1477,54 @@ CURLcode ftp_use_pasv(struct connectdata *conn)
                             addr,
                             connectport,
                             &conn->secondarysocket,
-                            &conninfo);
+                            &conninfo,
+                            connected);
+
+  Curl_resolv_unlock(addr); /* we're done using this address */
+
+  /*
+   * When this is used from the multi interface, this might've returned with
+   * the 'connected' set to FALSE and thus we are now awaiting a non-blocking
+   * connect to connect and we should not be "hanging" here waiting.
+   */
   
   if((CURLE_OK == result) &&       
      data->set.verbose)
     /* this just dumps information about this second connection */
-    ftp_pasv_verbose(conn, conninfo, newhost, connectport);
+    ftp_pasv_verbose(conn, conninfo, newhostp, connectport);
   
   if(CURLE_OK != result)
     return result;
 
   if (data->set.tunnel_thru_httpproxy) {
     /* We want "seamless" FTP operations through HTTP proxy tunnel */
     result = Curl_ConnectHTTPProxyTunnel(conn, conn->secondarysocket,
-                                         newhost, newport);
+                                         newhostp, newport);
     if(CURLE_OK != result)
       return result;
   }
 
   return CURLE_OK;
 }
 
-/***********************************************************************
- *
- * ftp_perform()
+/*
+ * Curl_ftp_nextconnect()
  *
- * This is the actual DO function for FTP. Get a file/directory according to
- * the options previously setup.
+ * This function shall be called when the second FTP connection has been
+ * established and is confirmed connected.
  */
 
-static
-CURLcode ftp_perform(struct connectdata *conn)
+CURLcode Curl_ftp_nextconnect(struct connectdata *conn)
 {
-  /* this is FTP and no proxy */
-  ssize_t nread;
-  CURLcode result;
   struct SessionHandle *data=conn->data;
   char *buf = data->state.buffer; /* this is our buffer */
+  CURLcode result;
+  ssize_t nread;
+  int ftpcode; /* for ftp status */
 
   /* the ftp struct is already inited in ftp_connect() */
   struct FTP *ftp = conn->proto.ftp;
-
   long *bytecountp = ftp->bytecountp;
-  int ftpcode; /* for ftp status */
-
-  /* Send any QUOTE strings? */
-  if(data->set.quote) {
-    if ((result = ftp_sendquote(conn, data->set.quote)) != CURLE_OK)
-      return result;
-  }
-    
-  /* This is a re-used connection. Since we change directory to where the
-     transfer is taking place, we must now get back to the original dir
-     where we ended up after login: */
-  if (conn->bits.reuse) {
-    if ((result = ftp_cwd(conn, ftp->entrypath)) != CURLE_OK)
-      return result;
-  }
-
-  /* change directory first! */
-  if(ftp->dir && ftp->dir[0]) {
-    if ((result = ftp_cwd(conn, ftp->dir)) != CURLE_OK)
-        return result;
-  }
-
-  /* Requested time of file? */
-  if(data->set.get_filetime && ftp->file) {
-    result = ftp_getfiletime(conn, ftp->file);
-    if(result)
-      return result;
-  }
-
-  /* If we have selected NOBODY and HEADER, it means that we only want file
-     information. Which in FTP can't be much more than the file size and
-     date. */
-  if(data->set.no_body && data->set.include_header) {
-    /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
-       may not support it! It is however the only way we have to get a file's
-       size! */
-    ssize_t filesize;
-
-    /* Some servers return different sizes for different modes, and thus we
-       must set the proper type before we check the size */
-    result = ftp_transfertype(conn, data->set.ftp_ascii);
-    if(result)
-      return result;
-
-    /* failing to get size is not a serious error */
-    result = ftp_getsize(conn, ftp->file, &filesize);
-
-    if(CURLE_OK == result) {
-      sprintf(buf, "Content-Length: %d\r\n", filesize);
-      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
-      if(result)
-        return result;
-    }
-
-    /* If we asked for a time of the file and we actually got one as
-       well, we "emulate" a HTTP-style header in our output. */
-
-#ifdef HAVE_STRFTIME
-    if(data->set.get_filetime && data->info.filetime) {
-      struct tm *tm;
-#ifdef HAVE_LOCALTIME_R
-      struct tm buffer;
-      tm = (struct tm *)localtime_r(&data->info.filetime, &buffer);
-#else
-      tm = localtime((unsigned long *)&data->info.filetime);
-#endif
-      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n",
-               tm);
-      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
-      if(result)
-        return result;
-    }
-#endif
-
-    return CURLE_OK;
-  }
-
-  if(data->set.no_body)
-    /* don't transfer the data */
-    ;
-  /* Get us a second connection up and connected */
-  else if(data->set.ftp_use_port) {
-    /* We have chosen to use the PORT command */
-    result = ftp_use_port(conn);
-    if(CURLE_OK == result)
-      /* we have the data connection ready */
-      infof(data, "Connected the data stream with PORT!\n");
-  }
-  else {
-    /* We have chosen (this is default) to use the PASV command */
-    result = ftp_use_pasv(conn);
-    if(CURLE_OK == result)
-      infof(data, "Connected the data stream with PASV!\n");
-  }
-  
-  if(result)
-    return result;
 
   if(data->set.upload) {
 
@@ -1688,10 +1603,9 @@ CURLcode ftp_perform(struct connectdata *conn)
             /* no data to transfer */
             result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
             
-            /* Set resume done so that we won't get any error in
-             * Curl_ftp_done() because we didn't transfer the amount of bytes
-             * that the local file file obviously is */
-            conn->bits.resume_done = TRUE; 
+            /* Set no_transfer so that we won't get any error in
+             * Curl_ftp_done() because we didn't transfer anything! */
+            ftp->no_transfer = TRUE; 
 
             return CURLE_OK;
           }
@@ -1780,6 +1694,7 @@ CURLcode ftp_perform(struct connectdata *conn)
       }
       infof(data, "range-download from %d to %d, totally %d bytes\n",
             from, to, totalsize);
+      ftp->dont_check = TRUE; /* dont check for successful transfer */
     }
 
     if((data->set.ftp_list_only) || !ftp->file) {
@@ -1872,11 +1787,9 @@ CURLcode ftp_perform(struct connectdata *conn)
           result=Curl_Transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
           infof(data, "File already completely downloaded\n");
 
-          /* Set resume done so that we won't get any error in Curl_ftp_done()
-           * because we didn't transfer the amount of bytes that the remote
-           * file obviously is */
-          conn->bits.resume_done = TRUE; 
-
+          /* Set no_transfer so that we won't get any error in Curl_ftp_done()
+           * because we didn't transfer the any file */
+          ftp->no_transfer = TRUE;
           return CURLE_OK;
         }
         
@@ -1990,6 +1903,128 @@ CURLcode ftp_perform(struct connectdata *conn)
 
 /***********************************************************************
  *
+ * ftp_perform()
+ *
+ * This is the actual DO function for FTP. Get a file/directory according to
+ * the options previously setup.
+ */
+
+static
+CURLcode ftp_perform(struct connectdata *conn,
+                     bool *connected)  /* for the TCP connect status after
+                                          PASV / PORT */
+{
+  /* this is FTP and no proxy */
+  CURLcode result=CURLE_OK;
+  struct SessionHandle *data=conn->data;
+  char *buf = data->state.buffer; /* this is our buffer */
+
+  /* the ftp struct is already inited in ftp_connect() */
+  struct FTP *ftp = conn->proto.ftp;
+
+  /* Send any QUOTE strings? */
+  if(data->set.quote) {
+    if ((result = ftp_sendquote(conn, data->set.quote)) != CURLE_OK)
+      return result;
+  }
+    
+  /* This is a re-used connection. Since we change directory to where the
+     transfer is taking place, we must now get back to the original dir
+     where we ended up after login: */
+  if (conn->bits.reuse && ftp->entrypath) {
+    if ((result = ftp_cwd(conn, ftp->entrypath)) != CURLE_OK)
+      return result;
+  }
+
+  /* change directory first! */
+  if(ftp->dir && ftp->dir[0]) {
+    if ((result = ftp_cwd(conn, ftp->dir)) != CURLE_OK)
+        return result;
+  }
+
+  /* Requested time of file? */
+  if(data->set.get_filetime && ftp->file) {
+    result = ftp_getfiletime(conn, ftp->file);
+    if(result)
+      return result;
+  }
+
+  /* If we have selected NOBODY and HEADER, it means that we only want file
+     information. Which in FTP can't be much more than the file size and
+     date. */
+  if(data->set.no_body && data->set.include_header && ftp->file) {
+    /* The SIZE command is _not_ RFC 959 specified, and therefor many servers
+       may not support it! It is however the only way we have to get a file's
+       size! */
+    ssize_t filesize;
+
+    ftp->no_transfer = TRUE; /* this means no actual transfer is made */
+    
+    /* Some servers return different sizes for different modes, and thus we
+       must set the proper type before we check the size */
+    result = ftp_transfertype(conn, data->set.ftp_ascii);
+    if(result)
+      return result;
+
+    /* failing to get size is not a serious error */
+    result = ftp_getsize(conn, ftp->file, &filesize);
+
+    if(CURLE_OK == result) {
+      sprintf(buf, "Content-Length: %d\r\n", filesize);
+      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
+      if(result)
+        return result;
+    }
+
+    /* If we asked for a time of the file and we actually got one as
+       well, we "emulate" a HTTP-style header in our output. */
+
+#ifdef HAVE_STRFTIME
+    if(data->set.get_filetime && data->info.filetime) {
+      struct tm *tm;
+#ifdef HAVE_LOCALTIME_R
+      struct tm buffer;
+      tm = (struct tm *)localtime_r(&data->info.filetime, &buffer);
+#else
+      tm = localtime((unsigned long *)&data->info.filetime);
+#endif
+      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
+      strftime(buf, BUFSIZE-1, "Last-Modified: %a, %d %b %Y %H:%M:%S %Z\r\n",
+               tm);
+      result = Curl_client_write(data, CLIENTWRITE_BOTH, buf, 0);
+      if(result)
+        return result;
+    }
+#endif
+
+    return CURLE_OK;
+  }
+
+  if(data->set.no_body)
+    /* doesn't really transfer any data */
+    ftp->no_transfer = TRUE;
+  /* Get us a second connection up and connected */
+  else if(data->set.ftp_use_port) {
+    /* We have chosen to use the PORT command */
+    result = ftp_use_port(conn);
+    if(CURLE_OK == result) {
+      /* we have the data connection ready */
+      infof(data, "Ordered connect of the data stream with PORT!\n");
+      *connected = TRUE; /* mark us "still connected" */
+    }
+  }
+  else {
+    /* We have chosen (this is default) to use the PASV command */
+    result = ftp_use_pasv(conn, connected);
+    if(connected)
+      infof(data, "Connected the data stream with PASV!\n");
+  }
+  
+  return result;
+}
+
+/***********************************************************************
+ *
  * Curl_ftp()
  *
  * This function is registered as 'curl_do' function. It decodes the path
@@ -2000,6 +2035,7 @@ CURLcode ftp_perform(struct connectdata *conn)
 CURLcode Curl_ftp(struct connectdata *conn)
 {
   CURLcode retcode;
+  bool connected;
 
   struct SessionHandle *data = conn->data;
   struct FTP *ftp;
@@ -2046,15 +2082,15 @@ CURLcode Curl_ftp(struct connectdata *conn)
   else
     ftp->dir = NULL;
 
-  retcode = ftp_perform(conn);
-
-  /* clean up here, success or error doesn't matter */
-  if(ftp->file)
-    free(ftp->file);
-  if(ftp->dir)
-    free(ftp->dir);
+  retcode = ftp_perform(conn, &connected);
 
-  ftp->file = ftp->dir = NULL; /* zero */
+  if(CURLE_OK == retcode) {
+    if(connected)
+      retcode = Curl_ftp_nextconnect(conn);
+    else
+      /* since we didn't connect now, we want do_more to get called */
+      conn->bits.do_more = TRUE;
+  }
 
   return retcode;
 }
@@ -2081,10 +2117,7 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
   va_start(ap, fmt);
   vsnprintf(s, 250, fmt, ap);
   va_end(ap);
-
-  if(conn->data->set.verbose)
-    fprintf(conn->data->set.err, "> %s\n", s);
-
+  
   strcat(s, "\r\n"); /* append a trailing CRLF */
 
   bytes_written=0;
@@ -2097,6 +2130,9 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
     if(CURLE_OK != res)
       break;
 
+    if(conn->data->set.verbose)
+      Curl_debug(conn->data, CURLINFO_HEADER_OUT, sptr, bytes_written);
+
     if(bytes_written != write_len) {
       write_len -= bytes_written;
       sptr += bytes_written;
@@ -2125,6 +2161,12 @@ CURLcode Curl_ftp_disconnect(struct connectdata *conn)
       free(ftp->entrypath);
     if(ftp->cache)
       free(ftp->cache);
+    if(ftp->file)
+      free(ftp->file);
+    if(ftp->dir)
+      free(ftp->dir);
+
+    ftp->file = ftp->dir = NULL; /* zero */
   }
   return CURLE_OK;
 }
@@ -2136,3 +2178,5 @@ CURLcode Curl_ftp_disconnect(struct connectdata *conn)
  * vim600: fdm=marker
  * vim: et sw=2 ts=2 sts=2 tw=78
  */
+
+#endif /* CURL_DISABLE_FTP */