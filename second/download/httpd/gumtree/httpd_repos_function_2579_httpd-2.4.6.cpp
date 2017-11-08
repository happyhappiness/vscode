static apr_status_t session_cookie_load(request_rec * r, session_rec ** z)
{

    session_cookie_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                    &session_cookie_module);

    session_rec *zz = NULL;
    const char *val = NULL;
    const char *note = NULL;
    const char *name = NULL;
    request_rec *m = r;

    /* find the first redirect */
    while (m->prev) {
        m = m->prev;
    }
    /* find the main request */
    while (m->main) {
        m = m->main;
    }

    /* is our session in a cookie? */
    if (conf->name2_set) {
        name = conf->name2;
    }
    else if (conf->name_set) {
        name = conf->name;
    }
    else {
        return DECLINED;
    }

    /* first look in the notes */
    note = apr_pstrcat(m->pool, MOD_SESSION_COOKIE, name, NULL);
    zz = (session_rec *)apr_table_get(m->notes, note);
    if (zz) {
        *z = zz;
        return OK;
    }

    /* otherwise, try parse the cookie */
    ap_cookie_read(r, name, &val, conf->remove);

    /* create a new session and return it */
    zz = (session_rec *) apr_pcalloc(m->pool, sizeof(session_rec));
    zz->pool = m->pool;
    zz->entries = apr_table_make(m->pool, 10);
    zz->encoded = val;
    *z = zz;

    /* put the session in the notes so we don't have to parse it again */
    apr_table_setn(m->notes, note, (char *)zz);

    return OK;

}