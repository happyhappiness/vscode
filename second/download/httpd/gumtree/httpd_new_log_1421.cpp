ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                            "mem_cache: URL %s exceeds the MCacheMaxStreamingBuffer (%" APR_SIZE_T_FMT ") limit and will not be cached.", 
                            obj->key, mobj->m_len);