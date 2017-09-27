               "<b>%lu</b> miss<br>", header->stat_removes_hit,
               header->stat_removes_miss);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, "leaving shmcb_status");
}

static apr_status_t socache_shmcb_iterate(ap_socache_instance_t *instance,
                                          server_rec *s,
                                          ap_socache_iterator_t *iterator,
                                          apr_pool_t *pool)
{
    SHMCBHeader *header = instance->header;
    unsigned int loop;
    apr_time_t now = apr_time_now();
