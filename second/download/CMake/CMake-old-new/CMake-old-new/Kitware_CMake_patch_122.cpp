@@ -61,7 +61,7 @@
 #include "ftplistparser.h"
 #include "curl_sec.h"
 #include "strtoofft.h"
-#include "strequal.h"
+#include "strcase.h"
 #include "vtls/vtls.h"
 #include "connect.h"
 #include "strerror.h"
@@ -72,7 +72,7 @@
 #include "sockaddr.h" /* required for Curl_sockaddr_storage */
 #include "multiif.h"
 #include "url.h"
-#include "rawstr.h"
+#include "strcase.h"
 #include "speedcheck.h"
 #include "warnless.h"
 #include "http_proxy.h"
@@ -475,7 +475,7 @@ static CURLcode ReceivedServerConnect(struct connectdata *conn, bool *received)
       if(ftpcode/100 > 3)
         return CURLE_FTP_ACCEPT_FAILED;
 
-      return CURLE_FTP_WEIRD_SERVER_REPLY;
+      return CURLE_WEIRD_SERVER_REPLY;
     }
 
     break;
@@ -741,7 +741,7 @@ CURLcode Curl_GetFTPResponse(ssize_t *nreadp, /* return number of bytes read */
        */
     }
     else {
-      switch (Curl_socket_ready(sockfd, CURL_SOCKET_BAD, interval_ms)) {
+      switch (SOCKET_READABLE(sockfd, interval_ms)) {
       case -1: /* select() error, stop reading */
         failf(data, "FTP response aborted due to select/poll error: %d",
               SOCKERRNO);
@@ -911,7 +911,7 @@ static int ftp_domore_getsock(struct connectdata *conn, curl_socket_t *socks,
     }
     else {
       socks[1] = conn->sock[SECONDARYSOCKET];
-      bits |= GETSOCK_WRITESOCK(1);
+      bits |= GETSOCK_WRITESOCK(1) | GETSOCK_READSOCK(1);
     }
 
     return bits;
@@ -1835,7 +1835,7 @@ static CURLcode ftp_epsv_disable(struct connectdata *conn)
   if(conn->bits.ipv6) {
     /* We can't disable EPSV when doing IPv6, so this is instead a fail */
     failf(conn->data, "Failed EPSV attempt, exiting\n");
-    return CURLE_FTP_WEIRD_SERVER_REPLY;
+    return CURLE_WEIRD_SERVER_REPLY;
   }
 
   infof(conn->data, "Failed EPSV attempt. Disabling EPSV\n");
@@ -2742,7 +2742,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
       else if(ftpcode != 220) {
         failf(data, "Got a %03d ftp-server response when 220 was expected",
               ftpcode);
-        return CURLE_FTP_WEIRD_SERVER_REPLY;
+        return CURLE_WEIRD_SERVER_REPLY;
       }
 
       /* We have received a 220 response fine, now we proceed. */
@@ -2999,7 +2999,7 @@ static CURLcode ftp_statemach_act(struct connectdata *conn)
 
         /* Check for special servers here. */
 
-        if(strequal(os, "OS/400")) {
+        if(strcasecompare(os, "OS/400")) {
           /* Force OS400 name format 1. */
           result = Curl_pp_sendf(&ftpc->pp, "%s", "SITE NAMEFMT 1");
           if(result) {
@@ -3165,7 +3165,7 @@ static CURLcode ftp_multi_statemach(struct connectdata *conn,
   struct ftp_conn *ftpc = &conn->proto.ftpc;
   CURLcode result = Curl_pp_statemach(&ftpc->pp, FALSE);
 
-  /* Check for the state outside of the Curl_socket_ready() return code checks
+  /* Check for the state outside of the Curl_socket_check() return code checks
      since at times we are in fact already in this state when this function
      gets called. */
   *done = (ftpc->state == FTP_STOP) ? TRUE : FALSE;
@@ -3250,7 +3250,6 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
   ssize_t nread;
   int ftpcode;
   CURLcode result = CURLE_OK;
-  bool was_ctl_valid = ftpc->ctl_valid;
   char *path;
   const char *path_to_use = data->state.path;
 
@@ -3274,10 +3273,9 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
     /* the connection stays alive fine even though this happened */
     /* fall-through */
   case CURLE_OK: /* doesn't affect the control connection's status */
-    if(!premature) {
-      ftpc->ctl_valid = was_ctl_valid;
+    if(!premature)
       break;
-    }
+
     /* until we cope better with prematurely ended requests, let them
      * fallback as if in complete failure */
   default:       /* by default, an error means the control connection is
@@ -3300,13 +3298,12 @@ static CURLcode ftp_done(struct connectdata *conn, CURLcode status,
     ftpc->known_filesize = -1;
   }
 
-  /* get the "raw" path */
-  path = curl_easy_unescape(data, path_to_use, 0, NULL);
-  if(!path) {
-    /* out of memory, but we can limp along anyway (and should try to
-     * since we may already be in the out of memory cleanup path) */
-    if(!result)
-      result = CURLE_OUT_OF_MEMORY;
+  if(!result)
+    /* get the "raw" path */
+    result = Curl_urldecode(data, path_to_use, 0, &path, NULL, FALSE);
+  if(result) {
+    /* We can limp along anyway (and should try to since we may already be in
+     * the error path) */
     ftpc->ctl_valid = FALSE; /* mark control connection as bad */
     connclose(conn, "FTP: out of memory!"); /* mark for connection closure */
     ftpc->prevpath = NULL; /* no path remembering */
@@ -4094,8 +4091,7 @@ static CURLcode ftp_do(struct connectdata *conn, bool *done)
 }
 
 
-CURLcode Curl_ftpsendf(struct connectdata *conn,
-                       const char *fmt, ...)
+CURLcode Curl_ftpsend(struct connectdata *conn, const char *cmd)
 {
   ssize_t bytes_written;
 #define SBUF_SIZE 1024
@@ -4107,10 +4103,9 @@ CURLcode Curl_ftpsendf(struct connectdata *conn,
   enum protection_level data_sec = conn->data_prot;
 #endif
 
-  va_list ap;
-  va_start(ap, fmt);
-  write_len = vsnprintf(s, SBUF_SIZE-3, fmt, ap);
-  va_end(ap);
+  write_len = strlen(cmd);
+  if(write_len > (sizeof(s) -3))
+    return CURLE_BAD_FUNCTION_ARGUMENT;
 
   strcpy(&s[write_len], "\r\n"); /* append a trailing CRLF */
   write_len +=2;
@@ -4292,6 +4287,7 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
     slash_pos=strrchr(cur_pos, '/');
     if(slash_pos || !*cur_pos) {
       size_t dirlen = slash_pos-cur_pos;
+      CURLcode result;
 
       ftpc->dirs = calloc(1, sizeof(ftpc->dirs[0]));
       if(!ftpc->dirs)
@@ -4300,12 +4296,13 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
       if(!dirlen)
         dirlen++;
 
-      ftpc->dirs[0] = curl_easy_unescape(conn->data, slash_pos ? cur_pos : "/",
-                                         slash_pos ? curlx_uztosi(dirlen) : 1,
-                                         NULL);
-      if(!ftpc->dirs[0]) {
+      result = Curl_urldecode(conn->data, slash_pos ? cur_pos : "/",
+                              slash_pos ? dirlen : 1,
+                              &ftpc->dirs[0], NULL,
+                              FALSE);
+      if(result) {
         freedirs(ftpc);
-        return CURLE_OUT_OF_MEMORY;
+        return result;
       }
       ftpc->dirdepth = 1; /* we consider it to be a single dir */
       filename = slash_pos ? slash_pos+1 : cur_pos; /* rest is file name */
@@ -4323,7 +4320,7 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
       return CURLE_OUT_OF_MEMORY;
 
     /* we have a special case for listing the root dir only */
-    if(strequal(path_to_use, "/")) {
+    if(!strcmp(path_to_use, "/")) {
       cur_pos++; /* make it point to the zero byte */
       ftpc->dirs[0] = strdup("/");
       ftpc->dirdepth++;
@@ -4340,18 +4337,15 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
           /* we skip empty path components, like "x//y" since the FTP command
              CWD requires a parameter and a non-existent parameter a) doesn't
              work on many servers and b) has no effect on the others. */
-          int len = curlx_sztosi(slash_pos - cur_pos + absolute_dir);
-          ftpc->dirs[ftpc->dirdepth] =
-            curl_easy_unescape(conn->data, cur_pos - absolute_dir, len, NULL);
-          if(!ftpc->dirs[ftpc->dirdepth]) { /* run out of memory ... */
-            failf(data, "no memory");
-            freedirs(ftpc);
-            return CURLE_OUT_OF_MEMORY;
-          }
-          if(isBadFtpString(ftpc->dirs[ftpc->dirdepth])) {
+          size_t len = slash_pos - cur_pos + absolute_dir;
+          CURLcode result =
+            Curl_urldecode(conn->data, cur_pos - absolute_dir, len,
+                           &ftpc->dirs[ftpc->dirdepth], NULL,
+                           TRUE);
+          if(result) {
             free(ftpc->dirs[ftpc->dirdepth]);
             freedirs(ftpc);
-            return CURLE_URL_MALFORMAT;
+            return result;
           }
         }
         else {
@@ -4387,15 +4381,12 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
   } /* switch */
 
   if(filename && *filename) {
-    ftpc->file = curl_easy_unescape(conn->data, filename, 0, NULL);
-    if(NULL == ftpc->file) {
-      freedirs(ftpc);
-      failf(data, "no memory");
-      return CURLE_OUT_OF_MEMORY;
-    }
-    if(isBadFtpString(ftpc->file)) {
+    CURLcode result =
+      Curl_urldecode(conn->data, filename, 0,  &ftpc->file, NULL, TRUE);
+
+    if(result) {
       freedirs(ftpc);
-      return CURLE_URL_MALFORMAT;
+      return result;
     }
   }
   else
@@ -4413,16 +4404,18 @@ CURLcode ftp_parse_url_path(struct connectdata *conn)
   if(ftpc->prevpath) {
     /* prevpath is "raw" so we convert the input path before we compare the
        strings */
-    int dlen;
-    char *path = curl_easy_unescape(conn->data, data->state.path, 0, &dlen);
-    if(!path) {
+    size_t dlen;
+    char *path;
+    CURLcode result =
+      Curl_urldecode(conn->data, data->state.path, 0, &path, &dlen, FALSE);
+    if(result) {
       freedirs(ftpc);
-      return CURLE_OUT_OF_MEMORY;
+      return result;
     }
 
-    dlen -= ftpc->file?curlx_uztosi(strlen(ftpc->file)):0;
-    if((dlen == curlx_uztosi(strlen(ftpc->prevpath))) &&
-       strnequal(path, ftpc->prevpath, dlen)) {
+    dlen -= ftpc->file?strlen(ftpc->file):0;
+    if((dlen == strlen(ftpc->prevpath)) &&
+       !strncmp(path, ftpc->prevpath, dlen)) {
       infof(data, "Request has same path as previous transfer\n");
       ftpc->cwddone = TRUE;
     }