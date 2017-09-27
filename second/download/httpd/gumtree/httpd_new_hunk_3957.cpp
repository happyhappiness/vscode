
        /* don't write empty buckets to the cache */
        if (!length) {
            continue;
        }

        sobj->body_length += length;
        if (sobj->body_length >= sobj->buffer_len - sobj->body_offset) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02378)
                    "URL %s failed the buffer size check "
                    "(%" APR_OFF_T_FMT ">=%" APR_SIZE_T_FMT ")",
                    h->cache_obj->key, sobj->body_length,
                    sobj->buffer_len - sobj->body_offset);
            apr_pool_destroy(sobj->pool);
            sobj->pool = NULL;
            return APR_EGENERAL;
        }
        memcpy(sobj->buffer + sobj->body_offset + sobj->body_length - length,
               str, length);

        /* have we reached the limit of how much we're prepared to write in one
         * go? If so, leave, we'll get called again. This prevents us from trying
         * to swallow too much data at once, or taking so long to write the data
         * the client times out.
         */
