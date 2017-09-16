void ap_send_error_response(request_rec *r, int recursive_error)

{

    BUFF *fd = r->connection->client;

    int status = r->status;

    int idx = ap_index_of_response(status);

    char *custom_response;

    const char *location = ap_table_get(r->headers_out, "Location");



    /* We need to special-case the handling of 204 and 304 responses,

     * since they have specific HTTP requirements and do not include a

     * message body.  Note that being assbackwards here is not an option.

     */

    if (status == HTTP_NOT_MODIFIED) {

        if (!ap_is_empty_table(r->err_headers_out))

            r->headers_out = ap_overlay_tables(r->pool, r->err_headers_out,

                                               r->headers_out);

        ap_hard_timeout("send 304", r);



        ap_basic_http_header(r);

        ap_set_keepalive(r);

