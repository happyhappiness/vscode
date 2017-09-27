     int rv;
     const char *message;
     ap_dbd_t *dbd = dbd_handle(r);
     apr_dbd_prepared_t *query;
     apr_dbd_results_t *res = NULL;
     apr_dbd_row_t *row = NULL;
-    const char **group;
 
     if (cfg->query == NULL) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01649)
                       "No query configured for dbd-group!");
         return HTTP_INTERNAL_SERVER_ERROR;
     }
