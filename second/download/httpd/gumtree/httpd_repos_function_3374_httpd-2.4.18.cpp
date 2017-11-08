static apr_status_t send_begin_request(request_rec *r,
                                       const fcgi_provider_conf *conf,
                                       apr_socket_t *s, int role,
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
    ap_fcgi_fill_in_request_body(&brb, role, 0 /* *NOT* AP_FCGI_KEEP_CONN */);

    ap_fcgi_header_to_array(&header, farray);
    ap_fcgi_begin_request_body_to_array(&brb, abrb);

    vec[0].iov_base = (void *)farray;
    vec[0].iov_len = sizeof(farray);
    vec[1].iov_base = (void *)abrb;
    vec[1].iov_len = sizeof(abrb);

    return sendv_data(conf, r, s, vec, 2, &len);
}