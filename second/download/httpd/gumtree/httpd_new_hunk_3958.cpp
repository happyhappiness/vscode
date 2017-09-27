                    h->cache_obj->key);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }
        if (cl_header) {
            apr_off_t cl;
            char *cl_endp;
            if (apr_strtoff(&cl, cl_header, &cl_endp, 10) != APR_SUCCESS
                    || *cl_endp != '\0' || cl != sobj->body_length) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02381)
                        "URL %s didn't receive complete response, not caching",
                        h->cache_obj->key);
                apr_pool_destroy(sobj->pool);
                sobj->pool = NULL;
                return APR_EGENERAL;
