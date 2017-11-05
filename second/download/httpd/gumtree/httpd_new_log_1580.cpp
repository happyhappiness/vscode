ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "disk_cache: URL %s failed the size check "
                         "(%" APR_OFF_T_FMT ">%" APR_OFF_T_FMT ")",
                         h->cache_obj->key, dobj->file_size, conf->maxfs);