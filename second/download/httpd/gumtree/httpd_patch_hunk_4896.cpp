                     "warning: crypto for '%s' was already initialised, "
                     "using existing configuration", conf->library);
             rv = APR_SUCCESS;
         }
         if (APR_SUCCESS != rv && err) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01845)
-                    "%s", err->msg);
+                    "The crypto library '%s' could not be loaded: %s (%s: %d)", conf->library, err->msg, err->reason, err->rc);
             return rv;
         }
         if (APR_ENOTIMPL == rv) {
             ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01846)
                     "The crypto library '%s' could not be found",
                     conf->library);
