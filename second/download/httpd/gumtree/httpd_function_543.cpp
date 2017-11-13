static void ssl_add_version_components(apr_pool_t *p,
                                       server_rec *s)
{
    char *vals[sizeof(version_components)/sizeof(char *)];
    int i;

    for (i=0; version_components[i]; i++) {
        vals[i] = ssl_add_version_component(p, s,
                                            version_components[i]);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Server: %s, Interface: %s, Library: %s",
                 AP_SERVER_BASEVERSION,
                 vals[1],  /* SSL_VERSION_INTERFACE */
                 vals[2]); /* SSL_VERSION_LIBRARY */
}