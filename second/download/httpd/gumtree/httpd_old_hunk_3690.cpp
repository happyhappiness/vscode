    }
    apr_dbm_close(dbm);
    if (size > 0 && elts > 0)
        avg = (int)(size / (long)elts);
    else
        avg = 0;
    ap_rprintf(r, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>");
    ap_rprintf(r, "current entries: <b>%d</b>, current size: <b>%ld</b> bytes<br>", elts, size);
    ap_rprintf(r, "average entry size: <b>%d</b> bytes<br>", avg);
    return;
}

static apr_status_t socache_dbm_iterate(ap_socache_instance_t *ctx,
                                        server_rec *s, void *userctx,
                                        ap_socache_iterator_t *iterator,
