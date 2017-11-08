static int check_anon_access(request_rec *r)
{
#ifdef NOTYET
    conn_rec *c = r->connection;
    anon_auth_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &auth_anon_module);

    if (!conf->anon_auth) {
        return DECLINED;
    }

    if (strcasecmp(r->connection->user, conf->anon_auth)) {
        return DECLINED;
    }

    return OK;
#endif
    return DECLINED;
}