                /* Probably a mod_disk_cache cache area has been (re)mounted
                 * read-only, or that there is a permissions problem.
                 */
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                     "cache: attempt to remove url from cache unsuccessful.");
            }
        }

        return ap_pass_brigade(f->next, bb);
    }

    if(rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                     "cache: store_headers failed");
        ap_remove_output_filter(f);

        return ap_pass_brigade(f->next, in);
    }

    rv = cache->provider->store_body(cache->handle, r, in);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                     "cache: store_body failed");
        ap_remove_output_filter(f);
    }

    return ap_pass_brigade(f->next, in);
}

/*
 * CACHE_REMOVE_URL filter
 * ---------------
