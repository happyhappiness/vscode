static int event_post_read_request(request_rec *r)
{
    conn_rec *c = r->connection;
    event_conn_state_t *cs = ap_get_module_config(c->conn_config,
                                                  &mpm_event_module);

    /* To preserve legacy behaviour (consistent with other MPMs), use
     * the keepalive timeout from the base server (first on this IP:port)
     * when none is explicitly configured on this server.
     */
    if (r->server->keep_alive_timeout_set) {
        cs->sc = ap_get_module_config(r->server->module_config,
                                      &mpm_event_module);
    }
    else {
        cs->sc = ap_get_module_config(c->base_server->module_config,
                                      &mpm_event_module);
    }
    return OK;
}