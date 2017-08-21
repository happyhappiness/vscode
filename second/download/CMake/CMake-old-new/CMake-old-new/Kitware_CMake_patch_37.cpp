@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -916,8 +916,7 @@ static int ftp_domore_getsock(struct connectdata *conn, curl_socket_t *socks,
 
     return bits;
   }
-  else
-    return Curl_pp_getsock(&conn->proto.ftpc.pp, socks, numsocks);
+  return Curl_pp_getsock(&conn->proto.ftpc.pp, socks, numsocks);
 }
 
 /* This is called after the FTP_QUOTE state is passed.
@@ -1209,7 +1208,7 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
         possibly_non_local = FALSE; /* don't try this again */
         continue;
       }
-      else if(error != EADDRINUSE && error != EACCES) {
+      if(error != EADDRINUSE && error != EACCES) {
         failf(data, "bind(port=%hu) failed: %s", port,
               Curl_strerror(conn, error) );
         Curl_closesocket(conn, portsock);
@@ -1307,7 +1306,7 @@ static CURLcode ftp_state_use_port(struct connectdata *conn,
       }
       break;
     }
-    else if(PORT == fcmd) {
+    if(PORT == fcmd) {
       char *source = myhost;
       char *dest = tmp;
 
@@ -1674,31 +1673,29 @@ static CURLcode ftp_state_ul_setup(struct connectdata *conn,
     }
 
     if(seekerr != CURL_SEEKFUNC_OK) {
+      curl_off_t passed=0;
       if(seekerr != CURL_SEEKFUNC_CANTSEEK) {
         failf(data, "Could not seek stream");
         return CURLE_FTP_COULDNT_USE_REST;
       }
       /* seekerr == CURL_SEEKFUNC_CANTSEEK (can't seek to offset) */
-      else {
-        curl_off_t passed=0;
-        do {
-          size_t readthisamountnow =
-            (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
-            BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
-
-          size_t actuallyread =
-            data->state.fread_func(data->state.buffer, 1, readthisamountnow,
-                                   data->state.in);
-
-          passed += actuallyread;
-          if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
-            /* this checks for greater-than only to make sure that the
-               CURL_READFUNC_ABORT return code still aborts */
-            failf(data, "Failed to read data");
-            return CURLE_FTP_COULDNT_USE_REST;
-          }
-        } while(passed < data->state.resume_from);
-      }
+      do {
+        size_t readthisamountnow =
+          (data->state.resume_from - passed > CURL_OFF_T_C(BUFSIZE)) ?
+          BUFSIZE : curlx_sotouz(data->state.resume_from - passed);
+
+        size_t actuallyread =
+          data->state.fread_func(data->state.buffer, 1, readthisamountnow,
+                                 data->state.in);
+
+        passed += actuallyread;
+        if((actuallyread == 0) || (actuallyread > readthisamountnow)) {
+          /* this checks for greater-than only to make sure that the
+             CURL_READFUNC_ABORT return code still aborts */
+          failf(data, "Failed to read data");
+          return CURLE_FTP_COULDNT_USE_REST;
+        }
+      } while(passed < data->state.resume_from);
     }
     /* now, decrease the size of the read */
     if(data->state.infilesize>0) {
@@ -1757,7 +1754,7 @@ static CURLcode ftp_state_quote(struct connectdata *conn,
   /*
    * This state uses:
    * 'count1' to iterate over the commands to send
-   * 'count2' to store wether to allow commands to fail
+   * 'count2' to store whether to allow commands to fail
    */
 
   if(init)
@@ -2000,7 +1997,7 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
 
     if(!addr) {
       failf(data, "Can't resolve proxy host %s:%hu", host_name, connectport);
-      return CURLE_FTP_CANT_GET_HOST;
+      return CURLE_COULDNT_RESOLVE_PROXY;
     }
   }
   else {
@@ -2040,11 +2037,14 @@ static CURLcode ftp_state_pasv_resp(struct connectdata *conn,
     /* this just dumps information about this second connection */
     ftp_pasv_verbose(conn, addr->addr, ftpc->newhost, connectport);
 
+  Curl_resolv_unlock(data, addr); /* we're done using this address */
+
   Curl_safefree(conn->secondaryhostname);
-  conn->secondaryhostname = strdup(ftpc->newhost);
   conn->secondary_port = ftpc->newport;
+  conn->secondaryhostname = strdup(ftpc->newhost);
+  if(!conn->secondaryhostname)
+    return CURLE_OUT_OF_MEMORY;
 
-  Curl_resolv_unlock(data, addr); /* we're done using this address */
   conn->bits.do_more = TRUE;
   state(conn, FTP_STOP); /* this phase is completed */
 
@@ -2107,7 +2107,7 @@ static CURLcode ftp_state_mdtm_resp(struct connectdata *conn,
         /* we have a time, reformat it */
         time_t secs=time(NULL);
         /* using the good old yacc/bison yuck */
-        snprintf(buf, sizeof(conn->data->state.buffer),
+        snprintf(buf, CURL_BUFSIZE(conn->data->set.buffer_size),
                  "%04d%02d%02d %02d:%02d:%02d GMT",
                  year, month, day, hour, minute, second);
         /* now, convert this into a time() value: */
@@ -2318,7 +2318,7 @@ static CURLcode ftp_state_size_resp(struct connectdata *conn,
   if(instate == FTP_SIZE) {
 #ifdef CURL_FTP_HTTPSTYLE_HEAD
     if(-1 != filesize) {
-      snprintf(buf, sizeof(data->state.buffer),
+      snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
                "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", filesize);
       result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
       if(result)
@@ -2409,8 +2409,7 @@ static CURLcode ftp_state_stor_resp(struct connectdata *conn,
 
     return CURLE_OK;
   }
-  else
-    return InitiateTransfer(conn);
+  return InitiateTransfer(conn);
 }
 
 /* for LIST and RETR responses */
@@ -2823,6 +2822,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
     case FTP_PWD:
       if(ftpcode == 257) {
         char *ptr=&data->state.buffer[4];  /* start on the first letter */
+        const size_t buf_size = CURL_BUFSIZE(data->set.buffer_size);
         char *dir;
         char *store;
 
@@ -2840,7 +2840,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
         */
 
         /* scan for the first double-quote for non-standard responses */
-        while(ptr < &data->state.buffer[sizeof(data->state.buffer)]
+        while(ptr < &data->state.buffer[buf_size]
               && *ptr != '\n' && *ptr != '\0' && *ptr != '"')
           ptr++;
 
@@ -2870,7 +2870,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
              does not start with a '/'), we probably need some server-dependent
              adjustments. For example, this is the case when connecting to
              an OS400 FTP server: this server supports two name syntaxes,
-             the default one being incompatible with standard pathes. In
+             the default one being incompatible with standard paths. In
              addition, this server switches automatically to the regular path
              syntax when one is encountered in a command: this results in
              having an entrypath in the wrong syntax when later used in CWD.
@@ -2944,12 +2944,10 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
           state(conn, FTP_NAMEFMT);
           break;
         }
-        else {
-          /* Nothing special for the target server. */
-          /* remember target server OS */
-          Curl_safefree(ftpc->server_os);
-          ftpc->server_os = os;
-        }
+        /* Nothing special for the target server. */
+        /* remember target server OS */
+        Curl_safefree(ftpc->server_os);
+        ftpc->server_os = os;
       }
       else {
         /* Cannot identify server OS. Continue anyway and cross fingers. */
@@ -3210,6 +3208,7 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
 
     /* until we cope better with prematurely ended requests, let them
      * fallback as if in complete failure */
+    /* FALLTHROUGH */
   default:       /* by default, an error means the control connection is
                     wedged and should not be used anymore */
     ftpc->ctl_valid = FALSE;
@@ -3553,7 +3552,7 @@ static CURLcode ftp_range(struct connectdata *conn)
                  " to %" CURL_FORMAT_CURL_OFF_T ", totally %"
                  CURL_FORMAT_CURL_OFF_T " bytes\n",
                  from, to, data->req.maxdownload));
-    ftpc->dont_check = TRUE; /* dont check for successful transfer */
+    ftpc->dont_check = TRUE; /* don't check for successful transfer */
   }
   else
     data->req.maxdownload = -1;
@@ -3796,12 +3795,10 @@ static CURLcode init_wc_data(struct connectdata *conn)
       result = ftp_parse_url_path(conn);
       return result;
     }
-    else {
-      wildcard->pattern = strdup(last_slash);
-      if(!wildcard->pattern)
-        return CURLE_OUT_OF_MEMORY;
-      last_slash[0] = '\0'; /* cut file from path */
-    }
+    wildcard->pattern = strdup(last_slash);
+    if(!wildcard->pattern)
+      return CURLE_OUT_OF_MEMORY;
+    last_slash[0] = '\0'; /* cut file from path */
   }
   else { /* there is only 'wildcard pattern' or nothing */
     if(path[0]) {
@@ -3886,8 +3883,7 @@ static CURLcode wc_statemach(struct connectdata *conn)
     if(wildcard->state == CURLWC_CLEAN)
       /* only listing! */
       break;
-    else
-      wildcard->state = result ? CURLWC_ERROR : CURLWC_MATCHING;
+    wildcard->state = result ? CURLWC_ERROR : CURLWC_MATCHING;
     break;
 
   case CURLWC_MATCHING: {
@@ -3905,7 +3901,7 @@ static CURLcode wc_statemach(struct connectdata *conn)
       wildcard->state = CURLWC_CLEAN;
       return wc_statemach(conn);
     }
-    else if(wildcard->filelist->size == 0) {
+    if(wildcard->filelist.size == 0) {
       /* no corresponding file */
       wildcard->state = CURLWC_CLEAN;
       return CURLE_REMOTE_FILE_NOT_FOUND;
@@ -3916,7 +3912,7 @@ static CURLcode wc_statemach(struct connectdata *conn)
   case CURLWC_DOWNLOADING: {
     /* filelist has at least one file, lets get first one */
     struct ftp_conn *ftpc = &conn->proto.ftpc;
-    struct curl_fileinfo *finfo = wildcard->filelist->head->ptr;
+    struct curl_fileinfo *finfo = wildcard->filelist.head->ptr;
 
     char *tmp_path = aprintf("%s%s", wildcard->path, finfo->filename);
     if(!tmp_path)
@@ -3931,7 +3927,7 @@ static CURLcode wc_statemach(struct connectdata *conn)
     infof(conn->data, "Wildcard - START of \"%s\"\n", finfo->filename);
     if(conn->data->set.chunk_bgn) {
       long userresponse = conn->data->set.chunk_bgn(
-          finfo, wildcard->customptr, (int)wildcard->filelist->size);
+        finfo, wildcard->customptr, (int)wildcard->filelist.size);
       switch(userresponse) {
       case CURL_CHUNK_BGN_FUNC_SKIP:
         infof(conn->data, "Wildcard - \"%s\" skipped by user\n",
@@ -3956,9 +3952,9 @@ static CURLcode wc_statemach(struct connectdata *conn)
       return result;
 
     /* we don't need the Curl_fileinfo of first file anymore */
-    Curl_llist_remove(wildcard->filelist, wildcard->filelist->head, NULL);
+    Curl_llist_remove(&wildcard->filelist, wildcard->filelist.head, NULL);
 
-    if(wildcard->filelist->size == 0) { /* remains only one file to down. */
+    if(wildcard->filelist.size == 0) { /* remains only one file to down. */
       wildcard->state = CURLWC_CLEAN;
       /* after that will be ftp_do called once again and no transfer
          will be done because of CURLWC_CLEAN state */
@@ -3969,8 +3965,8 @@ static CURLcode wc_statemach(struct connectdata *conn)
   case CURLWC_SKIP: {
     if(conn->data->set.chunk_end)
       conn->data->set.chunk_end(conn->data->wildcard.customptr);
-    Curl_llist_remove(wildcard->filelist, wildcard->filelist->head, NULL);
-    wildcard->state = (wildcard->filelist->size == 0) ?
+    Curl_llist_remove(&wildcard->filelist, wildcard->filelist.head, NULL);
+    wildcard->state = (wildcard->filelist.size == 0) ?
                       CURLWC_CLEAN : CURLWC_DOWNLOADING;
     return wc_statemach(conn);
   }
@@ -3986,6 +3982,7 @@ static CURLcode wc_statemach(struct connectdata *conn)
 
   case CURLWC_DONE:
   case CURLWC_ERROR:
+  case CURLWC_CLEAR:
     break;
   }
 
@@ -4283,7 +4280,6 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
                            &ftpc->dirs[ftpc->dirdepth], NULL,
                            TRUE);
           if(result) {
-            free(ftpc->dirs[ftpc->dirdepth]);
             freedirs(ftpc);
             return result;
           }