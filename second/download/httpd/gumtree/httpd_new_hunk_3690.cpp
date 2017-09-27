    }
    apr_dbm_close(dbm);
    if (size > 0 && elts > 0)
        avg = (int)(size / (long)elts);
    else
        avg = 0;
    if (!(flags & AP_STATUS_SHORT)) {
        ap_rprintf(r, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>");
        ap_rprintf(r, "current entries: <b>%d</b>, current size: <b>%ld</b> bytes<br>", elts, size);
        ap_rprintf(r, "average entry size: <b>%d</b> bytes<br>", avg);
    }
    else {
        ap_rputs("CacheType: DBM\n", r);
        ap_rputs("CacheMaximumSize: unlimited\n", r);
        ap_rprintf(r, "CacheCurrentEntries: %d\n", elts);
        ap_rprintf(r, "CacheCurrentSize: %ld\n", size);
        ap_rprintf(r, "CacheAvgEntrySize: %d\n", avg);
    }
    return;
}

static apr_status_t socache_dbm_iterate(ap_socache_instance_t *ctx,
                                        server_rec *s, void *userctx,
                                        ap_socache_iterator_t *iterator,
