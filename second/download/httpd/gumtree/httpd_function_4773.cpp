static void modssl_proxy_info_log(server_rec *s,
                                  X509_INFO *info,
                                  const char *msg)
{
    SSLSrvConfigRec *sc = mySrvConfig(s);
    char name_buf[256];
    X509_NAME *name;
    char *dn;

    if (!APLOGdebug(s)) {
        return;
    }

    name = X509_get_subject_name(info->x509);
    dn = X509_NAME_oneline(name, name_buf, sizeof(name_buf));

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 SSLPROXY_CERT_CB_LOG_FMT "%s, sending %s",
                 sc->vhost_id, msg, dn ? dn : "-uknown-");
}