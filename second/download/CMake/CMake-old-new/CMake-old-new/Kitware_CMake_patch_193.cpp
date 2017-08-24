@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -77,10 +77,9 @@
 #include "warnless.h"
 #include "http_proxy.h"
 #include "non-ascii.h"
+/* The last 3 #include files should be in this order */
 #include "curl_printf.h"
-
 #include "curl_memory.h"
-/* The last #include file should be: */
 #include "memdebug.h"
 
 #ifndef NI_MAXHOST
@@ -155,8 +154,9 @@ static CURLcode ftp_dophase_done(struct connectdata *conn,
                                  bool connected);
 
 /* easy-to-use macro: */
-#define PPSENDF(x,y,z)  if((result = Curl_pp_sendf(x,y,z)))     \
-                              return result
+#define PPSENDF(x,y,z)  result = Curl_pp_sendf(x,y,z); \
+                        if(result)                     \
+                          return result
 
 
 /*
@@ -265,6 +265,15 @@ static const struct Curl_handler Curl_handler_ftps_proxy = {
 #endif
 #endif
 
+static void close_secondarysocket(struct connectdata *conn)
+{
+  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET]) {
+    Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
+    conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
+  }
+  conn->bits.tcpconnect[SECONDARYSOCKET] = FALSE;
+  conn->tunnel_state[SECONDARYSOCKET] = TUNNEL_INIT;
+}
 
 /*
  * NOTE: back in the old days, we added code in the FTP code that made NOBODY
@@ -318,7 +327,7 @@ static bool isBadFtpString(const char *string)
  */
 static CURLcode AcceptServerConnect(struct connectdata *conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   curl_socket_t sock = conn->sock[SECONDARYSOCKET];
   curl_socket_t s = CURL_SOCKET_BAD;
 #ifdef ENABLE_IPV6
@@ -340,6 +349,9 @@ static CURLcode AcceptServerConnect(struct connectdata *conn)
     return CURLE_FTP_PORT_FAILED;
   }
   infof(data, "Connection accepted from server\n");
+  /* when this happens within the DO state it is important that we mark us as
+     not needing DO_MORE anymore */
+  conn->bits.do_more = FALSE;
 
   conn->sock[SECONDARYSOCKET] = s;
   (void)curlx_nonblock(s, TRUE); /* enable non-blocking */
@@ -354,8 +366,7 @@ static CURLcode AcceptServerConnect(struct connectdata *conn)
                                CURLSOCKTYPE_ACCEPT);
 
     if(error) {
-      Curl_closesocket(conn, s); /* close the socket and bail out */
-      conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
+      close_secondarysocket(conn);
       return CURLE_ABORTED_BY_CALLBACK;
     }
   }
@@ -373,7 +384,7 @@ static CURLcode AcceptServerConnect(struct connectdata *conn)
  * Curl_pgrsTime(..., TIMER_STARTACCEPT);
  *
  */
-static long ftp_timeleft_accept(struct SessionHandle *data)
+static long ftp_timeleft_accept(struct Curl_easy *data)
 {
   long timeout_ms = DEFAULT_ACCEPT_TIMEOUT;
   long other;
@@ -413,7 +424,7 @@ static long ftp_timeleft_accept(struct SessionHandle *data)
  */
 static CURLcode ReceivedServerConnect(struct connectdata *conn, bool *received)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   curl_socket_t ctrl_sock = conn->sock[FIRSTSOCKET];
   curl_socket_t data_sock = conn->sock[SECONDARYSOCKET];
   struct ftp_conn *ftpc = &conn->proto.ftpc;
@@ -484,7 +495,7 @@ static CURLcode ReceivedServerConnect(struct connectdata *conn, bool *received)
  */
 static CURLcode InitiateTransfer(struct connectdata *conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct FTP *ftp = data->req.protop;
   CURLcode result = CURLE_OK;
 
@@ -535,7 +546,7 @@ static CURLcode InitiateTransfer(struct connectdata *conn)
  */
 static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   long timeout_ms;
   CURLcode result = CURLE_OK;
 
@@ -606,7 +617,7 @@ static CURLcode ftp_readresp(curl_socket_t sockfd,
                              size_t *size) /* size of the response */
 {
   struct connectdata *conn = pp->conn;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 #ifdef HAVE_GSSAPI
   char * const buf = data->state.buffer;
 #endif
@@ -678,7 +689,7 @@ CURLcode Curl_GetFTPResponse(ssize_t *nreadp, /* return number of bytes read */
   curl_socket_t sockfd = conn->sock[FIRSTSOCKET];
   long timeout;              /* timeout in milliseconds */
   long interval_ms;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   CURLcode result = CURLE_OK;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   struct pingpong *pp = &ftpc->pp;
@@ -698,7 +709,7 @@ CURLcode Curl_GetFTPResponse(ssize_t *nreadp, /* return number of bytes read */
     /* check and reset timeout value every lap */
     timeout = Curl_pp_state_timeout(pp);
 
-    if(timeout <=0 ) {
+    if(timeout <=0) {
       failf(data, "FTP response timeout");
       return CURLE_OPERATION_TIMEDOUT; /* already too little time */
     }
@@ -969,7 +980,7 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
 {
   CURLcode result = CURLE_OK;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   curl_socket_t portsock= CURL_SOCKET_BAD;
   char myhost[256] = "";
 
@@ -1024,7 +1035,7 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
     if(*string_ftpport == '[') {
       /* [ipv6]:port(-range) */
       ip_start = string_ftpport + 1;
-      if((ip_end = strchr(string_ftpport, ']')) != NULL )
+      if((ip_end = strchr(string_ftpport, ']')) != NULL)
         strncpy(addr, ip_start, ip_end - ip_start);
     }
     else
@@ -1045,7 +1056,7 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
       else
 #endif
         /* (ipv4|domain|interface):port(-range) */
-        strncpy(addr, string_ftpport, ip_end - ip_start );
+        strncpy(addr, string_ftpport, ip_end - ip_start);
     }
     else
       /* ipv4|interface */
@@ -1065,11 +1076,11 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
 
     /* correct errors like:
      *  :1234-1230
-     *  :-4711 , in this case port_min is (unsigned)-1,
+     *  :-4711,  in this case port_min is (unsigned)-1,
      *           therefore port_min > port_max for all cases
      *           but port_max = (unsigned)-1
      */
-    if(port_min > port_max )
+    if(port_min > port_max)
       port_min = port_max = 0;
 
 
@@ -1322,11 +1333,11 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
   /* store which command was sent */
   ftpc->count1 = fcmd;
 
+  close_secondarysocket(conn);
+
   /* we set the secondary socket variable to this for now, it is only so that
      the cleanup function will close it in case we fail before the true
      secondary stuff is made */
-  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
-    Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
   conn->sock[SECONDARYSOCKET] = portsock;
 
   /* this tcpconnect assignment below is a hackish work-around to make the
@@ -1392,7 +1403,7 @@ static CURLcode ftp_state_prepare_transfer(struct connectdata *conn)
 {
   CURLcode result = CURLE_OK;
   struct FTP *ftp = conn->data->req.protop;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   if(ftp->transfer != FTPTRANSFER_BODY) {
     /* doesn't transfer any data */
@@ -1475,7 +1486,7 @@ static CURLcode ftp_state_size(struct connectdata *conn)
 static CURLcode ftp_state_list(struct connectdata *conn)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   /* If this output is to be machine-parsed, the NLST command might be better
      to use, since the LIST command output is not specified or standard in any
@@ -1513,12 +1524,12 @@ static CURLcode ftp_state_list(struct connectdata *conn)
     }
   }
 
-  cmd = aprintf( "%s%s%s",
-                 data->set.str[STRING_CUSTOMREQUEST]?
-                 data->set.str[STRING_CUSTOMREQUEST]:
-                 (data->set.ftp_list_only?"NLST":"LIST"),
-                 lstArg? " ": "",
-                 lstArg? lstArg: "" );
+  cmd = aprintf("%s%s%s",
+                data->set.str[STRING_CUSTOMREQUEST]?
+                data->set.str[STRING_CUSTOMREQUEST]:
+                (data->set.ftp_list_only?"NLST":"LIST"),
+                lstArg? " ": "",
+                lstArg? lstArg: "");
 
   if(!cmd) {
     free(lstArg);
@@ -1564,7 +1575,7 @@ static CURLcode ftp_state_type(struct connectdata *conn)
 {
   CURLcode result = CURLE_OK;
   struct FTP *ftp = conn->data->req.protop;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
 
   /* If we have selected NOBODY and HEADER, it means that we only want file
@@ -1596,7 +1607,7 @@ static CURLcode ftp_state_type(struct connectdata *conn)
 static CURLcode ftp_state_mdtm(struct connectdata *conn)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
 
   /* Requested time of file or time-depended transfer? */
@@ -1621,7 +1632,7 @@ static CURLcode ftp_state_ul_setup(struct connectdata *conn,
 {
   CURLcode result = CURLE_OK;
   struct FTP *ftp = conn->data->req.protop;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   int seekerr = CURL_SEEKFUNC_OK;
 
@@ -1640,7 +1651,7 @@ static CURLcode ftp_state_ul_setup(struct connectdata *conn,
     /* 4. lower the infilesize counter */
     /* => transfer as usual */
 
-    if(data->state.resume_from < 0 ) {
+    if(data->state.resume_from < 0) {
       /* Got no given size to start from, figure it out */
       PPSENDF(&ftpc->pp, "SIZE %s", ftpc->file);
       state(conn, FTP_STOR_SIZE);
@@ -1670,8 +1681,8 @@ static CURLcode ftp_state_ul_setup(struct connectdata *conn,
             BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
 
           size_t actuallyread =
-            data->set.fread_func(data->state.buffer, 1, readthisamountnow,
-                                 data->set.in);
+            data->state.fread_func(data->state.buffer, 1, readthisamountnow,
+                                   data->state.in);
 
           passed += actuallyread;
           if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
@@ -1717,7 +1728,7 @@ static CURLcode ftp_state_quote(struct connectdata *conn,
                                 ftpstate instate)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct FTP *ftp = data->req.protop;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   bool quote=FALSE;
@@ -1787,8 +1798,20 @@ static CURLcode ftp_state_quote(struct connectdata *conn,
           result = ftp_state_retr(conn, ftpc->known_filesize);
         }
         else {
-          PPSENDF(&ftpc->pp, "SIZE %s", ftpc->file);
-          state(conn, FTP_RETR_SIZE);
+          if(data->set.ignorecl) {
+            /* This code is to support download of growing files.  It prevents
+               the state machine from requesting the file size from the
+               server.  With an unknown file size the download continues until
+               the server terminates it, otherwise the client stops if the
+               received byte count exceeds the reported file size.  Set option
+               CURLOPT_IGNORE_CONTENT_LENGTH to 1 to enable this behavior.*/
+            PPSENDF(&ftpc->pp, "RETR %s", ftpc->file);
+            state(conn, FTP_RETR);
+          }
+          else {
+            PPSENDF(&ftpc->pp, "SIZE %s", ftpc->file);
+            state(conn, FTP_RETR_SIZE);
+          }
         }
       }
       break;
@@ -1836,7 +1859,7 @@ static CURLcode proxy_magic(struct connectdata *conn,
                             bool *magicdone)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
 #if defined(CURL_DISABLE_PROXY)
   (void) newhost;
@@ -1927,7 +1950,7 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
 {
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   CURLcode result;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   struct Curl_dns_entry *addr=NULL;
   int rc;
   unsigned short connectport; /* the local port connect() should use! */
@@ -2102,7 +2125,7 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
 static CURLcode ftp_state_port_resp(struct connectdata *conn,
                                     int ftpcode)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   ftpport fcmd = (ftpport)ftpc->count1;
   CURLcode result = CURLE_OK;
@@ -2139,7 +2162,7 @@ static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
                                     int ftpcode)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   struct FTP *ftp = data->req.protop;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
 
@@ -2244,7 +2267,7 @@ static CURLcode ftp_state_type_resp(struct connectdata *conn,
                                     ftpstate instate)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
 
   if(ftpcode/100 != 2) {
     /* "sasserftpd" and "(u)r(x)bot ftpd" both responds with 226 after a
@@ -2273,7 +2296,7 @@ static CURLcode ftp_state_retr(struct connectdata *conn,
                                          curl_off_t filesize)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   struct FTP *ftp = data->req.protop;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
 
@@ -2356,7 +2379,7 @@ static CURLcode ftp_state_size_resp(struct connectdata *conn,
                                     ftpstate instate)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   curl_off_t filesize;
   char *buf = data->state.buffer;
 
@@ -2428,7 +2451,7 @@ static CURLcode ftp_state_stor_resp(struct connectdata *conn,
                                     int ftpcode, ftpstate instate)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   if(ftpcode>=400) {
     failf(data, "Failed FTP upload: %0d", ftpcode);
@@ -2467,7 +2490,7 @@ static CURLcode ftp_state_get_resp(struct connectdata *conn,
                                     ftpstate instate)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct FTP *ftp = data->req.protop;
   char *buf = data->state.buffer;
 
@@ -2624,7 +2647,7 @@ static CURLcode ftp_state_user_resp(struct connectdata *conn,
                                     ftpstate instate)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct FTP *ftp = data->req.protop;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   (void)instate; /* no use for this yet */
@@ -2679,7 +2702,7 @@ static CURLcode ftp_state_acct_resp(struct connectdata *conn,
                                     int ftpcode)
 {
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   if(ftpcode != 230) {
     failf(data, "ACCT rejected by server: %03d", ftpcode);
     result = CURLE_FTP_WEIRD_PASS_REPLY; /* FIX */
@@ -2695,7 +2718,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
 {
   CURLcode result;
   curl_socket_t sock = conn->sock[FIRSTSOCKET];
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   int ftpcode;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   struct pingpong *pp = &ftpc->pp;
@@ -3218,9 +3241,9 @@ static CURLcode ftp_connect(struct connectdata *conn,
  * Input argument is already checked for validity.
  */
 static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
-                              bool premature)
+                         bool premature)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct FTP *ftp = data->req.protop;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   struct pingpong *pp = &ftpc->pp;
@@ -3232,11 +3255,6 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
   const char *path_to_use = data->state.path;
 
   if(!ftp)
-    /* When the easy handle is removed from the multi while libcurl is still
-     * trying to resolve the host name, it seems that the ftp struct is not
-     * yet initialized, but the removal action calls Curl_done() which calls
-     * this function. So we simply return success if no ftp pointer is set.
-     */
     return CURLE_OK;
 
   switch(status) {
@@ -3345,11 +3363,7 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
       /* Note that we keep "use" set to TRUE since that (next) connection is
          still requested to use SSL */
     }
-    if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET]) {
-      Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
-      conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
-      conn->bits.tcpconnect[SECONDARYSOCKET] = FALSE;
-    }
+    close_secondarysocket(conn);
   }
 
   if(!result && (ftp->transfer == FTPTRANSFER_BODY) && ftpc->ctl_valid &&
@@ -3573,7 +3587,7 @@ static CURLcode ftp_range(struct connectdata *conn)
   curl_off_t from, to;
   char *ptr;
   char *ptr2;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
 
   if(data->state.use_range && data->state.range) {
@@ -3631,7 +3645,7 @@ static CURLcode ftp_range(struct connectdata *conn)
 
 static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
 {
-  struct SessionHandle *data=conn->data;
+  struct Curl_easy *data=conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   CURLcode result = CURLE_OK;
   bool connected = FALSE;
@@ -3720,7 +3734,13 @@ static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
         return result;
 
       result = ftp_multi_statemach(conn, &complete);
-      *completep = (int)complete;
+      if(ftpc->wait_data_conn)
+        /* if we reach the end of the FTP state machine here, *complete will be
+           TRUE but so is ftpc->wait_data_conn, which says we need to wait for
+           the data connection and therefore we're not actually complete */
+        *completep = 0;
+      else
+        *completep = (int)complete;
     }
     else {
       /* download */
@@ -4189,7 +4209,7 @@ static CURLcode ftp_disconnect(struct connectdata *conn, bool dead_connection)
   (void)ftp_quit(conn); /* ignore errors on the QUIT */
 
   if(ftpc->entrypath) {
-    struct SessionHandle *data = conn->data;
+    struct Curl_easy *data = conn->data;
     if(data->state.most_recent_ftp_entrypath == ftpc->entrypath) {
       data->state.most_recent_ftp_entrypath = NULL;
     }
@@ -4222,7 +4242,7 @@ static CURLcode ftp_disconnect(struct connectdata *conn, bool dead_connection)
 static
 CURLcode ftp_parse_url_path(struct connectdata *conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   /* the ftp struct is already inited in ftp_connect() */
   struct FTP *ftp = data->req.protop;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
@@ -4248,16 +4268,17 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
       the first condition in the if() right here, is there just in case
       someone decides to set path to NULL one day
    */
-    if(data->state.path &&
-       data->state.path[0] &&
-       (data->state.path[strlen(data->state.path) - 1] != '/') )
-      filename = data->state.path;  /* this is a full file path */
-      /*
+    if(path_to_use[0] &&
+       (path_to_use[strlen(path_to_use) - 1] != '/') )
+      filename = path_to_use;  /* this is a full file path */
+    /*
+      else {
         ftpc->file is not used anywhere other than for operations on a file.
         In other words, never for directory operations.
         So we can safely leave filename as NULL here and use it as a
         argument in dir/file decisions.
-      */
+      }
+    */
     break;
 
   case FTPFILE_SINGLECWD:
@@ -4422,11 +4443,7 @@ static CURLcode ftp_dophase_done(struct connectdata *conn,
     CURLcode result = ftp_do_more(conn, &completed);
 
     if(result) {
-      if(conn->sock[SECONDARYSOCKET] != CURL_SOCKET_BAD) {
-        /* close the second socket if it was created already */
-        Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
-        conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
-      }
+      close_secondarysocket(conn);
       return result;
     }
   }
@@ -4477,7 +4494,7 @@ CURLcode ftp_regular_transfer(struct connectdata *conn,
 {
   CURLcode result=CURLE_OK;
   bool connected=FALSE;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   data->req.size = -1; /* make sure this is unknown at this point */
 
@@ -4511,7 +4528,7 @@ CURLcode ftp_regular_transfer(struct connectdata *conn,
 
 static CURLcode ftp_setup_connection(struct connectdata *conn)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   char *type;
   char command;
   struct FTP *ftp;