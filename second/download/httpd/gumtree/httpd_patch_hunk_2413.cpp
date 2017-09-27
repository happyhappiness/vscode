     if (   (res == AUTH_USER_FOUND)
         && (!conf->mustemail || *sent_pw)
         && (   !conf->verifyemail
             || (ap_strchr_c(sent_pw, '@') && ap_strchr_c(sent_pw, '.'))))
     {
         if (conf->logemail && ap_is_initial_req(r)) {
-            ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r,
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, APR_SUCCESS, r, APLOGNO(01672)
                           "Anonymous: Passwd <%s> Accepted",
                           sent_pw ? sent_pw : "\'none\'");
         }
 
         return AUTH_GRANTED;
     }
