{
    SSLSrvConfigRec *sc = mySrvConfig(s);
    char name_buf[256];
    X509_NAME *name;
    const char *dn;

    if (sc->log_level < SSL_LOG_TRACE) {
        return;
    }

    name = X509_get_subject_name(info->x509);
    dn = X509_NAME_oneline(name, name_buf, sizeof(name_buf));

    ssl_log(s, SSL_LOG_TRACE,
            SSLPROXY_CERT_CB_LOG_FMT "%s, sending %s", 
            sc->vhost_id, msg, dn ? dn : "-uknown-");
}

/*
 * caller will decrement the cert and key reference
 * so we need to increment here to prevent them from
 * being freed.
