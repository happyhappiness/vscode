static void event_pre_read_request(request_rec *r, conn_rec *c)
{
    event_conn_state_t *cs = ap_get_module_config(c->conn_config,
                                                  &mpm_event_module);

    cs->r = r;
    apr_pool_cleanup_register(r->pool, c, event_request_cleanup,
                              apr_pool_cleanup_null);
}