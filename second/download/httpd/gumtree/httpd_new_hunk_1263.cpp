        }
        rv = apr_bucket_read(e, &s, &len, eblock);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (len) {
            /* Check for buffer (max_streaming_buffer_size) overflow  */
           if ((obj->count + len) > mobj->m_len) {
               ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                            "mem_cache: URL %s exceeds the MCacheMaxStreamingBuffer (%" APR_SIZE_T_FMT ") limit and will not be cached.", 
                            obj->key, mobj->m_len);
               return APR_ENOMEM;
           }
           else {
               memcpy(cur, s, len);
               cur+=len;
               obj->count+=len;
