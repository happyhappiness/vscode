ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "disk_cache: URL %s failed the size check (%lu != %lu)",
                       h->cache_obj->key,
                       (unsigned long)h->cache_obj->info.len,
                       (unsigned long)dobj->file_size);