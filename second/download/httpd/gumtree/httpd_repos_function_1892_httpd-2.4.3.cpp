static apr_status_t send_begin_request(proxy_conn_rec *conn, int request_id)
{
    struct iovec vec[2];
    fcgi_header header;
    unsigned char farray[FCGI_HEADER_LEN];
    fcgi_begin_request_body brb;
    unsigned char abrb[FCGI_HEADER_LEN];
    apr_size_t len;

    fill_in_header(&header, FCGI_BEGIN_REQUEST, request_id, sizeof(abrb), 0);

    brb.roleB1 = ((FCGI_RESPONDER >> 8) & 0xff);
    brb.roleB0 = ((FCGI_RESPONDER) & 0xff);
    brb.flags = FCGI_KEEP_CONN;
    brb.reserved[0] = 0;
    brb.reserved[1] = 0;
    brb.reserved[2] = 0;
    brb.reserved[3] = 0;
    brb.reserved[4] = 0;

    fcgi_header_to_array(&header, farray);
    fcgi_begin_request_body_to_array(&brb, abrb);

    vec[0].iov_base = (void *)farray;
    vec[0].iov_len = sizeof(farray);
    vec[1].iov_base = (void *)abrb;
    vec[1].iov_len = sizeof(abrb);

    return send_data(conn, vec, 2, &len, 1);
}