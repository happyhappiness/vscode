          */
         *rv = nghttp2_submit_window_update(session->ngh2, NGHTTP2_FLAG_NONE,
                                            0, NGHTTP2_MAX_WINDOW_SIZE - win_size);
         if (*rv != 0) {
             status = APR_EGENERAL;
             ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
-                          APLOGNO(02970) "nghttp2_submit_window_update: %s", 
+                          H2_SSSN_LOG(APLOGNO(02970), session,
+                          "nghttp2_submit_window_update: %s"), 
                           nghttp2_strerror(*rv));        
         }
     }
     
     return status;
 }
