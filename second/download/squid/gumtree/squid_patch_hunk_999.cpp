       *  - PASV      is used if EPSV 1 fails.
       */
     switch (state) {
     case SENT_EPSV_ALL: /* EPSV ALL resulted in a bad response. Try ther EPSV methods. */
         if (ctrl.conn->local.isIPv6()) {
             debugs(9, 5, "FTP Channel is IPv6 (" << ctrl.conn->remote << ") attempting EPSV 2 after EPSV ALL has failed.");
-            mb.Printf("EPSV 2%s", Ftp::crlf);
+            mb.appendf("EPSV 2%s", Ftp::crlf);
             state = SENT_EPSV_2;
             break;
         }
     // else fall through to skip EPSV 2
 
     case SENT_EPSV_2: /* EPSV IPv6 failed. Try EPSV IPv4 */
         if (ctrl.conn->local.isIPv4()) {
             debugs(9, 5, "FTP Channel is IPv4 (" << ctrl.conn->remote << ") attempting EPSV 1 after EPSV ALL has failed.");
-            mb.Printf("EPSV 1%s", Ftp::crlf);
+            mb.appendf("EPSV 1%s", Ftp::crlf);
             state = SENT_EPSV_1;
             break;
         } else if (Config.Ftp.epsv_all) {
             debugs(9, DBG_IMPORTANT, "FTP does not allow PASV method after 'EPSV ALL' has been sent.");
             failed(ERR_FTP_FAILURE, 0);
             return false;
         }
     // else fall through to skip EPSV 1
 
     case SENT_EPSV_1: /* EPSV options exhausted. Try PASV now. */
         debugs(9, 5, "FTP Channel (" << ctrl.conn->remote << ") rejects EPSV connection attempts. Trying PASV instead.");
-        mb.Printf("PASV%s", Ftp::crlf);
+        mb.appendf("PASV%s", Ftp::crlf);
         state = SENT_PASV;
         break;
 
     default: {
         bool doEpsv = true;
         if (Config.accessList.ftp_epsv) {
             ACLFilledChecklist checklist(Config.accessList.ftp_epsv, fwd->request, NULL);
             doEpsv = (checklist.fastCheck() == ACCESS_ALLOWED);
         }
         if (!doEpsv) {
             debugs(9, 5, "EPSV support manually disabled. Sending PASV for FTP Channel (" << ctrl.conn->remote <<")");
-            mb.Printf("PASV%s", Ftp::crlf);
+            mb.appendf("PASV%s", Ftp::crlf);
             state = SENT_PASV;
         } else if (Config.Ftp.epsv_all) {
             debugs(9, 5, "EPSV ALL manually enabled. Attempting with FTP Channel (" << ctrl.conn->remote <<")");
-            mb.Printf("EPSV ALL%s", Ftp::crlf);
+            mb.appendf("EPSV ALL%s", Ftp::crlf);
             state = SENT_EPSV_ALL;
         } else {
             if (ctrl.conn->local.isIPv6()) {
                 debugs(9, 5, "FTP Channel (" << ctrl.conn->remote << "). Sending default EPSV 2");
-                mb.Printf("EPSV 2%s", Ftp::crlf);
+                mb.appendf("EPSV 2%s", Ftp::crlf);
                 state = SENT_EPSV_2;
             }
             if (ctrl.conn->local.isIPv4()) {
                 debugs(9, 5, "Channel (" << ctrl.conn->remote <<"). Sending default EPSV 1");
-                mb.Printf("EPSV 1%s", Ftp::crlf);
+                mb.appendf("EPSV 1%s", Ftp::crlf);
                 state = SENT_EPSV_1;
             }
         }
         break;
     }
     }
