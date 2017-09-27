  * In most implementations the session is only saved if the dirty flag is
  * true. This prevents the session being saved unnecessarily.
  *
  * @param r The request
  * @param z A pointer to where the session will be written.
  */
-static int ap_session_save(request_rec * r, session_rec * z)
+static apr_status_t ap_session_save(request_rec * r, session_rec * z)
 {
     if (z) {
         apr_time_t now = apr_time_now();
         int rv = 0;
 
         session_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                        &session_module);
 
         /* sanity checks, should we try save at all? */
         if (z->written) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, SESSION_PREFIX
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01818)
                           "attempt made to save the session twice, "
                           "session not saved: %s", r->uri);
             return APR_EGENERAL;
         }
         if (z->expiry && z->expiry < now) {
-            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
+            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01819)
                           "attempt made to save a session when the session had already expired, "
                           "session not saved: %s", r->uri);
             return APR_EGENERAL;
         }
 
         /* reset the expiry back to maxage, if the expiry is present */
