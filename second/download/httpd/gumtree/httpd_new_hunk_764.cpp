    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 SSLPROXY_CERT_CB_LOG_FMT
                 "no client certificate found!?", sc->vhost_id);

    return FALSE;
}

static void ssl_session_log(server_rec *s,
                            const char *request,
                            unsigned char *id,
                            unsigned int idlen,
