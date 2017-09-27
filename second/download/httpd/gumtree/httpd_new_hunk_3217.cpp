    apr_brigade_destroy(tmpbb);

    /* Finally decode the OCSP response from what's stored in the
     * bio. */
    response = d2i_OCSP_RESPONSE_bio(bio, NULL);
    if (response == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01988)
                      "failed to decode OCSP response data");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, mySrvFromConn(c));
    }

    return response;
}

OCSP_RESPONSE *modssl_dispatch_ocsp_request(const apr_uri_t *uri,
                                            apr_interval_time_t timeout,
                                            OCSP_REQUEST *request,
                                            conn_rec *c, apr_pool_t *p)
{
    OCSP_RESPONSE *response = NULL;
    apr_socket_t *sd;
    BIO *bio;

    bio = serialize_request(request, uri);
    if (bio == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(01989)
                      "could not serialize OCSP request");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, mySrvFromConn(c));
        return NULL;
    }

    sd = send_request(bio, uri, timeout, c, p);
    if (sd == NULL) {
        /* Errors already logged. */
        BIO_free(bio);
        return NULL;
    }
