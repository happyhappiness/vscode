    ap_rprintf(r, "total retrieves since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->stat_retrieves_hit,
               header->stat_retrieves_miss);
    ap_rprintf(r, "total removes since starting: <b>%lu</b> hit, "
               "<b>%lu</b> miss<br>", header->stat_removes_hit,
               header->stat_removes_miss);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00841) "leaving shmcb_status");
}

static apr_status_t socache_shmcb_iterate(ap_socache_instance_t *instance,
                                          server_rec *s, void *userctx,
                                          ap_socache_iterator_t *iterator,
                                          apr_pool_t *pool)
