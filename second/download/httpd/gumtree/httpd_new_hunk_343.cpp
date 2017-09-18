
                return TRUE;
            }
        }
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
                            const char *status,
                            const char *result,
                            long timeout)
{
    char buf[SSL_SESSION_ID_STRING_LEN];
    char timeout_str[56] = {'\0'};

    if (s->loglevel < APLOG_DEBUG) {
        return;
    }

    if (timeout) {
        apr_snprintf(timeout_str, sizeof(timeout_str),
                     "timeout=%lds ", (timeout - time(NULL)));
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Inter-Process Session Cache: "
                 "request=%s status=%s id=%s %s(session %s)",
                 request, status,
                 SSL_SESSION_id2sz(id, idlen, buf, sizeof(buf)),
                 timeout_str, result);
}

/*
 *  This callback function is executed by OpenSSL whenever a new SSL_SESSION is
 *  added to the internal OpenSSL session cache. We use this hook to spread the
 *  SSL_SESSION also to the inter-process disk-cache to make share it with our
