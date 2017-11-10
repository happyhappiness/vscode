static int http_create_request(request_rec *r)
{
    if (!r->main && !r->prev) {
        ap_add_output_filter_handle(ap_byterange_filter_handle,
                                    NULL, r, r->connection);
        ap_add_output_filter_handle(ap_content_length_filter_handle,
                                    NULL, r, r->connection);
        ap_add_output_filter_handle(ap_http_header_filter_handle,
                                    NULL, r, r->connection);
        ap_add_output_filter_handle(ap_http_outerror_filter_handle,
                                    NULL, r, r->connection);
    }

    return OK;
}