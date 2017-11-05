static OCSP_REQUEST *create_request(X509_STORE_CTX *ctx, X509 *cert, 
                                    OCSP_CERTID **certid, 
                                    server_rec *s, apr_pool_t *p)
{
    OCSP_REQUEST *req = OCSP_REQUEST_new();

    *certid = OCSP_cert_to_id(NULL, cert, ctx->current_issuer);
    if (!*certid || !OCSP_request_add0_id(req, *certid)) {
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "could not retrieve certificate id");
        return NULL;
    }
    
    OCSP_request_add1_nonce(req, 0, -1);
    
    return req;
}