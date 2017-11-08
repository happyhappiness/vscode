static apr_status_t send_begin_request(proxy_conn_rec *conn,
                                       apr_uint16_t request_id)
{
    struct iovec vec[2];
    ap_fcgi_header header;
    unsigned char farray[AP_FCGI_HEADER_LEN];
    ap_fcgi_begin_request_body brb;
    unsigned char abrb[AP_FCGI_HEADER_LEN];
    apr_size_t len;

    ap_fcgi_fill_in_header(&header, AP_FCGI_BEGIN_REQUEST, request_id,
                           sizeof(abrb), 0);

    ap_fcgi_fill_in_request_body(&brb, AP_FCGI_RESPONDER,
                                 ap_proxy_connection_reusable(conn)
                                     ? AP_FCGI_KEEP_CONN : 0);

    ap_fcgi_header_to_array(&header, farray);
    ap_fcgi_begin_request_body_to_array(&brb, abrb);

    vec[0].iov_base = (void *)farray;
    vec[0].iov_len = sizeof(farray);
    vec[1].iov_base = (void *)abrb;
    vec[1].iov_len = sizeof(abrb);

    return send_data(conn, vec, 2, &len);
}