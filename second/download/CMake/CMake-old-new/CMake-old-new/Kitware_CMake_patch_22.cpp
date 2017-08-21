@@ -580,10 +580,8 @@ static CURLcode AllowServerConnect(struct connectdata *conn, bool *connected)
   else {
     /* Add timeout to multi handle and break out of the loop */
     if(!result && *connected == FALSE) {
-      if(data->set.accepttimeout > 0)
-        Curl_expire(data, data->set.accepttimeout);
-      else
-        Curl_expire(data, DEFAULT_ACCEPT_TIMEOUT);
+      Curl_expire(data, data->set.accepttimeout > 0 ?
+                  data->set.accepttimeout: DEFAULT_ACCEPT_TIMEOUT, 0);
     }
   }
 
@@ -1681,8 +1679,9 @@ static CURLcode ftp_state_ul_setup(struct connectdata *conn,
       /* seekerr == CURL_SEEKFUNC_CANTSEEK (can't seek to offset) */
       do {
         size_t readthisamountnow =
-          (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
-          BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
+          (data->state.resume_from - passed > data->set.buffer_size) ?
+          (size_t)data->set.buffer_size :
+          curlx_sotouz(data->state.resume_from - passed);
 
         size_t actuallyread =
           data->state.fread_func(data->state.buffer, 1, readthisamountnow,
@@ -2101,17 +2100,17 @@ static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
       /* we got a time. Format should be: "YYYYMMDDHHMMSS[.sss]" where the
          last .sss part is optional and means fractions of a second */
       int year, month, day, hour, minute, second;
-      char *buf = data->state.buffer;
-      if(6 == sscanf(buf+4, "%04d%02d%02d%02d%02d%02d",
+      if(6 == sscanf(&data->state.buffer[4], "%04d%02d%02d%02d%02d%02d",
                      &year, &month, &day, &hour, &minute, &second)) {
         /* we have a time, reformat it */
+        char timebuf[24];
         time_t secs=time(NULL);
-        /* using the good old yacc/bison yuck */
-        snprintf(buf, CURL_BUFSIZE(conn->data->set.buffer_size),
+
+        snprintf(timebuf, sizeof(timebuf),
                  "%04d%02d%02d %02d:%02d:%02d GMT",
                  year, month, day, hour, minute, second);
         /* now, convert this into a time() value: */
-        data->info.filetime = (long)curl_getdate(buf, &secs);
+        data->info.filetime = (long)curl_getdate(timebuf, &secs);
       }
 
 #ifdef CURL_FTP_HTTPSTYLE_HEAD
@@ -2122,6 +2121,7 @@ static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
          ftpc->file &&
          data->set.get_filetime &&
          (data->info.filetime>=0) ) {
+        char headerbuf[128];
         time_t filetime = (time_t)data->info.filetime;
         struct tm buffer;
         const struct tm *tm = &buffer;
@@ -2131,7 +2131,7 @@ static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
           return result;
 
         /* format: "Tue, 15 Nov 1994 12:45:26" */
-        snprintf(buf, BUFSIZE-1,
+        snprintf(headerbuf, sizeof(headerbuf),
                  "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
                  Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
                  tm->tm_mday,
@@ -2140,7 +2140,7 @@ static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
                  tm->tm_hour,
                  tm->tm_min,
                  tm->tm_sec);
-        result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
+        result = Curl_client_write(conn, CLIENTWRITE_BOTH, headerbuf, 0);
         if(result)
           return result;
       } /* end of a ridiculous amount of conditionals */
@@ -2318,9 +2318,10 @@ static CURLcode ftp_state_size_resp(struct connectdata *conn,
   if(instate == FTP_SIZE) {
 #ifdef CURL_FTP_HTTPSTYLE_HEAD
     if(-1 != filesize) {
-      snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
+      char clbuf[128];
+      snprintf(clbuf, sizeof(clbuf),
                "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", filesize);
-      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
+      result = Curl_client_write(conn, CLIENTWRITE_BOTH, clbuf, 0);
       if(result)
         return result;
     }
@@ -2420,7 +2421,6 @@ static CURLcode ftp_state_get_resp(struct connectdata *conn,
   CURLcode result = CURLE_OK;
   struct Curl_easy *data = conn->data;
   struct FTP *ftp = data->req.protop;
-  char *buf = data->state.buffer;
 
   if((ftpcode == 150) || (ftpcode == 125)) {
 
@@ -2464,6 +2464,7 @@ static CURLcode ftp_state_get_resp(struct connectdata *conn,
        *
        * Example D above makes this parsing a little tricky */
       char *bytes;
+      char *buf = data->state.buffer;
       bytes=strstr(buf, " bytes");
       if(bytes--) {
         long in=(long)(bytes-buf);
@@ -2822,7 +2823,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
     case FTP_PWD:
       if(ftpcode == 257) {
         char *ptr=&data->state.buffer[4];  /* start on the first letter */
-        const size_t buf_size = CURL_BUFSIZE(data->set.buffer_size);
+        const size_t buf_size = data->set.buffer_size;
         char *dir;
         char *store;
 
@@ -3587,7 +3588,7 @@ static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
     if(conn->tunnel_state[SECONDARYSOCKET] == TUNNEL_CONNECT) {
       /* As we're in TUNNEL_CONNECT state now, we know the proxy name and port
          aren't used so we blank their arguments. TODO: make this nicer */
-      result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, NULL, 0, FALSE);
+      result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, NULL, 0);
 
       return result;
     }