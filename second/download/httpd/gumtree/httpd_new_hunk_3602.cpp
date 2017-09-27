            return NULL;
        }
    }

    rv = apr_reslist_acquire(group->reslist, (void*) &rec);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02655)
                     "Failed to acquire DBD connection from pool!");
        return NULL;
    }

    if (dbd_check(pool, s, rec) != APR_SUCCESS) {
        apr_reslist_invalidate(group->reslist, rec);
