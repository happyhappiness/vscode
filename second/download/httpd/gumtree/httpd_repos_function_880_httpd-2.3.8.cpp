static BIO *serialize_request(OCSP_REQUEST *req, const apr_uri_t *uri)
{
    BIO *bio;
    int len;

    len = i2d_OCSP_REQUEST(req, NULL);

    bio = BIO_new(BIO_s_mem());

    BIO_printf(bio, "POST %s%s%s HTTP/1.0\r\n"
               "Host: %s:%d\r\n"
               "Content-Type: application/ocsp-request\r\n"
               "Content-Length: %d\r\n"
               "\r\n", 
               uri->path ? uri->path : "/",
               uri->query ? "?" : "", uri->query ? uri->query : "",
               uri->hostname, uri->port, len);

    if (i2d_OCSP_REQUEST_bio(bio, req) != 1) {
        BIO_free(bio);
        return NULL;
    }

    return bio;
}