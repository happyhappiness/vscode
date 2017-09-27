        extract_dn(t, nids, "SSL_CLIENT_S_DN_", X509_get_subject_name(xs), p);
        extract_dn(t, nids, "SSL_CLIENT_I_DN_", X509_get_issuer_name(xs), p);
        X509_free(xs);
    }
}

const char *ssl_ext_lookup(apr_pool_t *p, conn_rec *c, int peer,
                           const char *oidnum)
{
    SSLConnRec *sslconn = myConnConfig(c);
    SSL *ssl;
    X509 *xs = NULL;
    ASN1_OBJECT *oid;
    int count = 0, j;
    char *result = NULL;

    if (!sslconn || !sslconn->ssl) {
        return NULL;
    }
    ssl = sslconn->ssl;

    oid = OBJ_txt2obj(oidnum, 1);
    if (!oid) {
        ERR_clear_error();
        return NULL;
    }

    xs = peer ? SSL_get_peer_certificate(ssl) : SSL_get_certificate(ssl);
    if (xs == NULL) {
        return NULL;
    }

    count = X509_get_ext_count(xs);

    for (j = 0; j < count; j++) {
        X509_EXTENSION *ext = X509_get_ext(xs, j);

        if (OBJ_cmp(ext->object, oid) == 0) {
            BIO *bio = BIO_new(BIO_s_mem());

            if (X509V3_EXT_print(bio, ext, 0, 0) == 1) {
                BUF_MEM *buf;

                BIO_get_mem_ptr(bio, &buf);
                result = apr_pstrmemdup(p, buf->data, buf->length);
            }

            BIO_vfree(bio);
            break;
        }
    }

    if (peer) {
        /* only SSL_get_peer_certificate raises the refcount */
        X509_free(xs);
    }

    ERR_clear_error();
    return result;
}

static char *ssl_var_lookup_ssl_compress_meth(SSL *ssl)
{
    char *result = "NULL";
#ifdef OPENSSL_VERSION_NUMBER
