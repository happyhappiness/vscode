         for (b = APR_BRIGADE_FIRST(bb); b != APR_BRIGADE_SENTINEL(bb); b = APR_BUCKET_NEXT(b)) {
           dumpit(f, b);
         }
     } else {
         ap_log_error(APLOG_MARK, ptr->loglevel, 0, c->base_server,
         "mod_dumpio: %s - %d", f->frec->name, ret) ;
+        return ret;
     }
 
     return APR_SUCCESS ;
 }
 
 static int dumpio_output_filter (ap_filter_t *f, apr_bucket_brigade *bb)
