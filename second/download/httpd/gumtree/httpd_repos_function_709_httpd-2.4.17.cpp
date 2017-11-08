static int stapling_set_response(SSL *ssl, OCSP_RESPONSE *rsp)
{
    int rspderlen;
    unsigned char *rspder = NULL;

    rspderlen = i2d_OCSP_RESPONSE(rsp, &rspder);
    if (rspderlen <= 0)
        return 0;
    SSL_set_tlsext_status_ocsp_resp(ssl, rspder, rspderlen);
    return 1;
}