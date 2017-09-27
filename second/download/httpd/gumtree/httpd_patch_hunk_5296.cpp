         }
     }
 
     ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                   "finished with poll() - cleaning up");
 
-    if (client_error) {
-        return HTTP_INTERNAL_SERVER_ERROR;
-    }
     return OK;
 }
 
 /*
  */
 static int proxy_wstunnel_handler(request_rec *r, proxy_worker *worker,
