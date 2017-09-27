            }
            else {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01937)
                             "stapling_check_response: cached response expired");
            }

            OCSP_BASICRESP_free(bs);
            return SSL_TLSEXT_ERR_NOACK;
        }
    }

    OCSP_BASICRESP_free(bs);

    return SSL_TLSEXT_ERR_OK;
}

static BOOL stapling_renew_response(server_rec *s, modssl_ctx_t *mctx, SSL *ssl,
                                    certinfo *cinf, OCSP_RESPONSE **prsp,
                                    apr_pool_t *pool)
{
    conn_rec *conn      = (conn_rec *)SSL_get_app_data(ssl);
    apr_pool_t *vpool;
    OCSP_REQUEST *req = NULL;
    OCSP_CERTID *id = NULL;
    STACK_OF(X509_EXTENSION) *exts;
    int i;
    BOOL ok = FALSE;
    BOOL rv = TRUE;
    const char *ocspuri;
    apr_uri_t uri;

    *prsp = NULL;
    /* Build up OCSP query from server certificate info */
