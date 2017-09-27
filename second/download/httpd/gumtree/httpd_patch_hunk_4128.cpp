 
         APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_eos_create(f->c->bucket_alloc));
         return APR_SUCCESS;
     }
 
     if (mode == AP_MODE_READBYTES) {
-        apr_bucket *e;
-
         /* Partition the buffered brigade. */
         rv = apr_brigade_partition(ctx->bb, bytes, &e);
         if (rv && rv != APR_INCOMPLETE) {
             ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, f->c, APLOGNO(02019)
                           "could not partition buffered SSL brigade");
             ap_remove_input_filter(f);
