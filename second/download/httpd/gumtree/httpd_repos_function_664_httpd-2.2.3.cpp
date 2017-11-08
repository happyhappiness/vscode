apr_array_header_t *ssl_extlist_by_oid(request_rec *r, const char *oidstr)
{
    int count = 0, j;
    X509 *xs = NULL;
    ASN1_OBJECT *oid;
    apr_array_header_t *val_array;
    SSLConnRec *sslconn = myConnConfig(r->connection);

    /* trivia */
    if (oidstr == NULL || sslconn == NULL || sslconn->ssl == NULL)
        return NULL;

    /* Determine the oid we are looking for */
    if ((oid = OBJ_txt2obj(oidstr, 1)) == NULL) {
        ERR_clear_error();
        return NULL;
    }

    /* are there any extensions in the cert? */
    if ((xs = SSL_get_peer_certificate(sslconn->ssl)) == NULL ||
        (count = X509_get_ext_count(xs)) == 0) {
        return NULL;
    }

    val_array = apr_array_make(r->pool, NUM_OID_ELTS, sizeof(char *));

    /* Loop over all extensions, extract the desired oids */
    for (j = 0; j < count; j++) {
        X509_EXTENSION *ext = X509_get_ext(xs, j);

        if (OBJ_cmp(ext->object, oid) == 0) {
            BIO *bio = BIO_new(BIO_s_mem());

            if (X509V3_EXT_print(bio, ext, 0, 0) == 1) {
                BUF_MEM *buf;
                char **new = apr_array_push(val_array);

                BIO_get_mem_ptr(bio, &buf);

                *new = apr_pstrdup(r->pool, buf->data);
            }

            BIO_vfree(bio);
        }
    }

    X509_free(xs);
    ERR_clear_error();

    if (val_array->nelts == 0)
        return NULL;
    else
        return val_array;
}