    name = X509_get_subject_name(info->x509);
    dn = X509_NAME_oneline(name, name_buf, sizeof(name_buf));

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 SSLPROXY_CERT_CB_LOG_FMT "%s, sending %s", 
                 sc->vhost_id, msg, dn ? dn : "-uknown-");
    modssl_free(dn);
}

/*
 * caller will decrement the cert and key reference
 * so we need to increment here to prevent them from
 * being freed.
