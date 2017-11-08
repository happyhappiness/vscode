static int event_protocol_switch(conn_rec *c, request_rec *r, server_rec *s,
                                 const char *protocol)
{
    if (!r && s) {
        /* connection based switching of protocol, set the correct server
         * configuration, so that timeouts, keepalives and such are used
         * for the server that the connection was switched on.
         * Normally, we set this on post_read_request, but on a protocol
         * other than http/1.1, this might never happen.
         */
        event_conn_state_t *cs;
        
        cs = ap_get_module_config(c->conn_config, &mpm_event_module);
        cs->sc = ap_get_module_config(s->module_config, &mpm_event_module);
    }
    return DECLINED;
}