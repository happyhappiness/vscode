static void log_provider_info(const fcgi_provider_conf *conf, request_rec *r)
{
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  APLOGNO(02496) "name %s, backend %s, host %s, port %d, "
                  "first address %pI, %c%c",
                  conf->name,
                  conf->backend,
                  conf->host,
                  (int)conf->port,
                  conf->backend_addrs,
                  conf->is_authn ? 'N' : '_',
                  conf->is_authz ? 'Z' : '_');
}