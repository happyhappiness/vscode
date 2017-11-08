static int net_time_filter(ap_filter_t *f, apr_bucket_brigade *b,
                           ap_input_mode_t mode, apr_read_type_e block,
                           apr_off_t readbytes)
{
    int keptalive = f->c->keepalive == AP_CONN_KEEPALIVE;
    apr_socket_t *csd = ap_get_module_config(f->c->conn_config, &core_module);
    int *first_line = f->ctx;

    if (!f->ctx) {
        f->ctx = first_line = apr_palloc(f->r->pool, sizeof(*first_line));
        *first_line = 1;
    }

    if (mode != AP_MODE_INIT && mode != AP_MODE_EATCRLF) {
        if (*first_line) {
            apr_socket_timeout_set(csd, 
                                   keptalive
                                      ? f->c->base_server->keep_alive_timeout
                                      : f->c->base_server->timeout);
            *first_line = 0;
        }
        else {
            if (keptalive) {
                apr_socket_timeout_set(csd, f->c->base_server->timeout);
            }
        }
    }
    return ap_get_brigade(f->next, b, mode, block, readbytes);
}