static apr_status_t session_dbd_load(request_rec * r, session_rec ** z)
{

    session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_dbd_module);

    apr_status_t ret = APR_SUCCESS;
    session_rec *zz = NULL;
    const char *name = NULL;
    const char *note = NULL;
    const char *val = NULL;
    const char *key = NULL;
    request_rec *m = r->main ? r->main : r;

    /* is our session in a cookie? */
    if (conf->name2_set) {
        name = conf->name2;
    }
    else if (conf->name_set) {
        name = conf->name;
    }
    else if (conf->peruser_set && r->user) {
        name = r->user;
    }
    else {
        return DECLINED;
    }

    /* first look in the notes */
    note = apr_pstrcat(r->pool, MOD_SESSION_DBD, name, NULL);
    zz = (session_rec *)apr_table_get(m->notes, note);
    if (zz) {
        *z = zz;
        return OK;
    }

    /* load anonymous sessions */
    if (conf->name_set || conf->name2_set) {

        /* load an RFC2109 or RFC2965 compliant cookie */
        ap_cookie_read(r, name, &key, conf->remove);
        if (key) {
            ret = dbd_load(r, key, &val);
            if (ret != APR_SUCCESS) {
                return ret;
            }
        }

    }

    /* load named session */
    else if (conf->peruser) {
        if (r->user) {
            ret = dbd_load(r, r->user, &val);
            if (ret != APR_SUCCESS) {
                return ret;
            }
        }
    }

    /* otherwise not for us */
    else {
        return DECLINED;
    }

    /* create a new session and return it */
    zz = (session_rec *) apr_pcalloc(r->pool, sizeof(session_rec));
    zz->pool = r->pool;
    zz->entries = apr_table_make(zz->pool, 10);
    zz->uuid = (apr_uuid_t *) apr_pcalloc(zz->pool, sizeof(apr_uuid_t));
    if (key) {
        apr_uuid_parse(zz->uuid, key);
    }
    else {
        apr_uuid_get(zz->uuid);
    }
    zz->encoded = val;
    *z = zz;

    /* put the session in the notes so we don't have to parse it again */
    apr_table_setn(m->notes, note, (char *)zz);

    return OK;

}