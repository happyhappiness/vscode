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
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, mySrvFromConn(c));
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c,
                      "could not serialize OCSP request");
        return NULL;
    }
    
    sd = send_request(bio, uri, timeout, c, p);
    if (sd == NULL) {
        /* Errors already logged. */
        BIO_free(bio);
        return NULL;
    }

    /* Clear the BIO contents, ready for the response. */
    (void)BIO_reset(bio);

    response = read_response(sd, bio, c, p);

    apr_socket_close(sd);
    BIO_free(bio);

    return response;
}