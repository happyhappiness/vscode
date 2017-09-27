                         "(%" APR_OFF_T_FMT " < %" APR_OFF_T_FMT ")",
                         h->cache_obj->key, dobj->file_size, conf->minfs);
            /* Remove the intermediate cache file and return non-APR_SUCCESS */
            file_cache_errorcleanup(dobj, r);
            return APR_EGENERAL;
        }
        if (cl_header) {
            apr_int64_t cl = apr_atoi64(cl_header);
            if ((errno == 0) && (dobj->file_size != cl)) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "disk_cache: URL %s didn't receive complete response, not caching",
                             h->cache_obj->key);
                /* Remove the intermediate cache file and return non-APR_SUCCESS */
                file_cache_errorcleanup(dobj, r);
                return APR_EGENERAL;
            }
        }

        /* All checks were fine. Move tempfile to final destination */
        /* Link to the perm file, and close the descriptor */
        file_cache_el_final(dobj, r);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "disk_cache: Body for URL %s cached.",  dobj->name);
