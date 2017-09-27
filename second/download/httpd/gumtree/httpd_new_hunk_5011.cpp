                         "%s server certificate is not a leaf certificate "
                         "(BasicConstraints: pathlen == %d > 0 !?)",
                         ssl_asn1_keystr(type), pathlen);
        }
    }

    if (SSL_X509_match_name(ptemp, cert, (const char *)s->server_hostname,
                            TRUE, s) == FALSE) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01909)
                     "%s certificate configured for %s does NOT include "
                     "an ID which matches the server name",
                     ssl_asn1_keystr(type), (mySrvConfig(s))->vhost_id);
    }
}

static void ssl_init_server_certs(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
