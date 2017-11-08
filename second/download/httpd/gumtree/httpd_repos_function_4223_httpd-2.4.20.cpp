static apr_status_t event_request_cleanup(void *dummy)
{
    conn_rec *c = dummy;
    event_conn_state_t *cs = ap_get_module_config(c->conn_config,
                                                  &mpm_event_module);

    cs->r = NULL;
    return APR_SUCCESS;
}