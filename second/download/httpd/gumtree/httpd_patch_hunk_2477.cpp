             /* Testing with ab and 100k requests reveals no nasties
              * so I infer we're not leaking anything like memory
              * or file descriptors.  That's nice!
              */
             return DONE;
         case APR_INCHILD:
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "In child!");
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02142) "In child!");
             break;  /* now we'll drop privileges in the child */
         default:
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02143)
                           "Failed to fork secure child process!");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
     }
 
     /* OK, now drop privileges. */
