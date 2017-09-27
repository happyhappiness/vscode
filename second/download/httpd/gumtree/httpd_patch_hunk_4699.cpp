                 return DECLINED;
             }
         }
         buffer_len = sobj->buffer_len;
         rc = conf->provider->socache_provider->retrieve(
                 conf->provider->socache_instance, r->server,
-                (unsigned char *) nkey, strlen(nkey), sobj->buffer,
+                (unsigned char *) nkey, len, sobj->buffer,
                 &buffer_len, r->pool);
         if (socache_mutex) {
             apr_status_t status = apr_global_mutex_unlock(socache_mutex);
             if (status != APR_SUCCESS) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02356)
                         "could not release lock, ignoring: %s", obj->key);
