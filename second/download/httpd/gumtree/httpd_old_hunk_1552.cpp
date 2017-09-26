            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }
        if (dobj->file_size < conf->minfs) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "cache_disk: URL %s failed the size check "
                         "(%" APR_OFF_T_FMT "<%" APR_SIZE_T_FMT ")",
                         h->cache_obj->key, dobj->file_size, conf->minfs);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }

