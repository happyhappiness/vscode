static void basic_http_header_check(request_rec *r,
                                    const char **protocol)
{
    if (r->assbackwards) {
        /* no such thing as a response protocol */
        return;
    }

    if (!r->status_line) {
        r->status_line = status_lines[ap_index_of_response(r->status)];
    }

    /* Note that we must downgrade before checking for force responses. */
    if (r->proto_num > HTTP_VERSION(1,0)
        && apr_table_get(r->subprocess_env, "downgrade-1.0")) {
        r->proto_num = HTTP_VERSION(1,0);
    }

    /* kludge around broken browsers when indicated by force-response-1.0
     */
    if (r->proto_num == HTTP_VERSION(1,0)
        && apr_table_get(r->subprocess_env, "force-response-1.0")) {
        *protocol = "HTTP/1.0";
        r->connection->keepalive = AP_CONN_CLOSE;
    }
    else {
        *protocol = AP_SERVER_PROTOCOL;
    }

}