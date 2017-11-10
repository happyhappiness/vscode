static int session_dbd_monitor(apr_pool_t *p, server_rec *s)
{
    /* TODO handle housekeeping */
    dbd_clean(p, s);
    return OK;
}