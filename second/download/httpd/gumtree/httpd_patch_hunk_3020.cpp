         apr_cpystrn(message, cmd, sizeof(message));
         if ((crlf = strchr(message, '\r')) != NULL ||
             (crlf = strchr(message, '\n')) != NULL)
             *crlf = '\0';
         if (strncmp(message,"PASS ", 5) == 0)
             strcpy(&message[5], "****");
-        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
-                     "proxy:>FTP: %s", message);
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, ">%s", message);
     }
 
     rc = ftp_getrc_msg(ftp_ctrl, bb, message, sizeof message);
     if (rc == -1 || rc == 421)
         strcpy(message,"<unable to read result>");
     if ((crlf = strchr(message, '\r')) != NULL ||
         (crlf = strchr(message, '\n')) != NULL)
         *crlf = '\0';
-    ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, r->server,
-                 "proxy:<FTP: %3.3u %s", rc, message);
+    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, "<%3.3u %s", rc, message);
 
     if (pmessage != NULL)
         *pmessage = apr_pstrdup(r->pool, message);
 
     return rc;
 }
