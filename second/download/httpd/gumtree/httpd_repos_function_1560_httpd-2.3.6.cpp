static int ap_process_http_connection(conn_rec *c)
{
    if (async_mpm && !c->clogging_input_filters) {
        return ap_process_http_async_connection(c);
    }
    else {
        return ap_process_http_sync_connection(c);
    }
}