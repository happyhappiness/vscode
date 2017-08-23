@@ -72,7 +72,7 @@
 #include "speedcheck.h"
 #include "getinfo.h"
 
-#include "strequal.h"
+#include "strcase.h"
 #include "vtls/vtls.h"
 #include "connect.h"
 #include "strerror.h"
@@ -416,12 +416,12 @@ static CURLcode ssh_getworkingpath(struct connectdata *conn,
   struct Curl_easy *data = conn->data;
   char *real_path = NULL;
   char *working_path;
-  int working_path_len;
-
-  working_path = curl_easy_unescape(data, data->state.path, 0,
-                                    &working_path_len);
-  if(!working_path)
-    return CURLE_OUT_OF_MEMORY;
+  size_t working_path_len;
+  CURLcode result =
+    Curl_urldecode(data, data->state.path, 0, &working_path,
+                   &working_path_len, FALSE);
+  if(result)
+    return result;
 
   /* Check for /~/, indicating relative to the user's home directory */
   if(conn->handler->protocol & CURLPROTO_SCP) {
@@ -676,7 +676,7 @@ static CURLcode ssh_check_fingerprint(struct connectdata *conn)
    * against a known fingerprint, if available.
    */
   if(pubkey_md5 && strlen(pubkey_md5) == 32) {
-    if(!fingerprint || !strequal(md5buffer, pubkey_md5)) {
+    if(!fingerprint || strcmp(md5buffer, pubkey_md5)) {
       if(fingerprint)
         failf(data,
             "Denied establishing ssh session: mismatch md5 fingerprint. "
@@ -1233,7 +1233,7 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
         sshc->acceptfail = TRUE;
       }
 
-      if(curl_strequal("pwd", cmd)) {
+      if(strcasecompare("pwd", cmd)) {
         /* output debug output if that is requested */
         char *tmp = aprintf("257 \"%s\" is current directory.\n",
                             sftp_scp->path);
@@ -1297,9 +1297,9 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
          * OpenSSH's sftp program and call the appropriate libssh2
          * functions.
          */
-        if(curl_strnequal(cmd, "chgrp ", 6) ||
-           curl_strnequal(cmd, "chmod ", 6) ||
-           curl_strnequal(cmd, "chown ", 6) ) {
+        if(strncasecompare(cmd, "chgrp ", 6) ||
+           strncasecompare(cmd, "chmod ", 6) ||
+           strncasecompare(cmd, "chown ", 6) ) {
           /* attribute change */
 
           /* sshc->quote_path1 contains the mode to set */
@@ -1321,8 +1321,8 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
           state(conn, SSH_SFTP_QUOTE_STAT);
           break;
         }
-        else if(curl_strnequal(cmd, "ln ", 3) ||
-                curl_strnequal(cmd, "symlink ", 8)) {
+        else if(strncasecompare(cmd, "ln ", 3) ||
+                strncasecompare(cmd, "symlink ", 8)) {
           /* symbolic linking */
           /* sshc->quote_path1 is the source */
           /* get the destination */
@@ -1342,12 +1342,12 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
           state(conn, SSH_SFTP_QUOTE_SYMLINK);
           break;
         }
-        else if(curl_strnequal(cmd, "mkdir ", 6)) {
+        else if(strncasecompare(cmd, "mkdir ", 6)) {
           /* create dir */
           state(conn, SSH_SFTP_QUOTE_MKDIR);
           break;
         }
-        else if(curl_strnequal(cmd, "rename ", 7)) {
+        else if(strncasecompare(cmd, "rename ", 7)) {
           /* rename file */
           /* first param is the source path */
           /* second param is the dest. path */
@@ -1366,17 +1366,17 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
           state(conn, SSH_SFTP_QUOTE_RENAME);
           break;
         }
-        else if(curl_strnequal(cmd, "rmdir ", 6)) {
+        else if(strncasecompare(cmd, "rmdir ", 6)) {
           /* delete dir */
           state(conn, SSH_SFTP_QUOTE_RMDIR);
           break;
         }
-        else if(curl_strnequal(cmd, "rm ", 3)) {
+        else if(strncasecompare(cmd, "rm ", 3)) {
           state(conn, SSH_SFTP_QUOTE_UNLINK);
           break;
         }
 #ifdef HAS_STATVFS_SUPPORT
-        else if(curl_strnequal(cmd, "statvfs ", 8)) {
+        else if(strncasecompare(cmd, "statvfs ", 8)) {
           state(conn, SSH_SFTP_QUOTE_STATVFS);
           break;
         }
@@ -1431,7 +1431,7 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
         sshc->acceptfail = TRUE;
       }
 
-      if(!curl_strnequal(cmd, "chmod", 5)) {
+      if(!strncasecompare(cmd, "chmod", 5)) {
         /* Since chown and chgrp only set owner OR group but libssh2 wants to
          * set them both at once, we need to obtain the current ownership
          * first.  This takes an extra protocol round trip.
@@ -1457,7 +1457,7 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
       }
 
       /* Now set the new attributes... */
-      if(curl_strnequal(cmd, "chgrp", 5)) {
+      if(strncasecompare(cmd, "chgrp", 5)) {
         sshc->quote_attrs.gid = strtoul(sshc->quote_path1, NULL, 10);
         sshc->quote_attrs.flags = LIBSSH2_SFTP_ATTR_UIDGID;
         if(sshc->quote_attrs.gid == 0 && !ISDIGIT(sshc->quote_path1[0]) &&
@@ -1471,7 +1471,7 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
           break;
         }
       }
-      else if(curl_strnequal(cmd, "chmod", 5)) {
+      else if(strncasecompare(cmd, "chmod", 5)) {
         sshc->quote_attrs.permissions = strtoul(sshc->quote_path1, NULL, 8);
         sshc->quote_attrs.flags = LIBSSH2_SFTP_ATTR_PERMISSIONS;
         /* permissions are octal */
@@ -1486,7 +1486,7 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
           break;
         }
       }
-      else if(curl_strnequal(cmd, "chown", 5)) {
+      else if(strncasecompare(cmd, "chown", 5)) {
         sshc->quote_attrs.uid = strtoul(sshc->quote_path1, NULL, 10);
         sshc->quote_attrs.flags = LIBSSH2_SFTP_ATTR_UIDGID;
         if(sshc->quote_attrs.uid == 0 && !ISDIGIT(sshc->quote_path1[0]) &&
@@ -1895,7 +1895,7 @@ static CURLcode ssh_statemach_act(struct connectdata *conn, bool *block)
         /* since we don't really wait for anything at this point, we want the
            state machine to move on as soon as possible so we set a very short
            timeout here */
-        Curl_expire(data, 1);
+        Curl_expire(data, 0);
 
         state(conn, SSH_STOP);
       }
@@ -2860,7 +2860,7 @@ static CURLcode ssh_block_statemach(struct connectdata *conn,
       if(LIBSSH2_SESSION_BLOCK_OUTBOUND & dir)
         fd_write = sock;
       /* wait for the socket to become ready */
-      Curl_socket_ready(fd_read, fd_write,
+      Curl_socket_check(fd_read, CURL_SOCKET_BAD, fd_write,
                         left>1000?1000:left); /* ignore result */
     }
 #endif
@@ -3109,7 +3109,6 @@ static CURLcode scp_done(struct connectdata *conn, CURLcode status,
 
 }
 
-/* return number of received (decrypted) bytes */
 static ssize_t scp_send(struct connectdata *conn, int sockindex,
                         const void *mem, size_t len, CURLcode *err)
 {
@@ -3134,10 +3133,6 @@ static ssize_t scp_send(struct connectdata *conn, int sockindex,
   return nwrite;
 }
 
-/*
- * If the read would block (EWOULDBLOCK) we return -1. Otherwise we return
- * a regular CURLcode value.
- */
 static ssize_t scp_recv(struct connectdata *conn, int sockindex,
                         char *mem, size_t len, CURLcode *err)
 {