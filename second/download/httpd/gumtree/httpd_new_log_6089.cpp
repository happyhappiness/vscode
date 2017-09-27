ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02378)
                    "URL %s failed the buffer size check "
                    "(%" APR_OFF_T_FMT ">=%" APR_SIZE_T_FMT ")",
                    h->cache_obj->key, sobj->body_length,
                    sobj->buffer_len - sobj->body_offset);