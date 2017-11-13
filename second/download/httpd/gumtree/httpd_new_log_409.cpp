ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "cache_disk: URL %s failed the size check (%lu<%lu)",
                     h->cache_obj->key, (unsigned long)dobj->file_size, (unsigned long)conf->minfs);