                "ftpReadControlReply: read error: " << xstrerr(io.xerrno));
 
         if (ignoreErrno(io.xerrno)) {
             scheduleReadControlReply(0);
         } else {
             failed(ERR_READ_ERROR, io.xerrno);
-            /* failed closes ctrl.fd and frees ftpState */
+            /* failed closes ctrl.conn and frees ftpState */
         }
         return;
     }
 
     if (io.size == 0) {
         if (entry->store_status == STORE_PENDING) {
             failed(ERR_FTP_FAILURE, 0);
-            /* failed closes ctrl.fd and frees ftpState */
+            /* failed closes ctrl.conn and frees ftpState */
             return;
         }
 
         /* XXX this may end up having to be serverComplete() .. */
         abortTransaction("zero control reply read");
         return;
