static int am_check_access(request_rec *r)
{
  int method = r->method_number;
  am_conf_t *conf;

  conf = (am_conf_t *) ap_get_module_config(r->per_dir_config,
                                            &allowmethods_module);
  if (!conf || conf->allowed == 0) {
    return DECLINED;
  }

  r->allowed = conf->allowed;

  if (conf->allowed & (AP_METHOD_BIT << method)) {
    return DECLINED;
  }

  ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01623)
                  "client method denied by server configuration: '%s' to %s%s",
                  r->method,
                  r->filename ? "" : "uri ",
                  r->filename ? r->filename : r->uri);

  return HTTP_METHOD_NOT_ALLOWED;
}