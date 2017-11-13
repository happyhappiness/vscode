static const char *get_hash(request_rec *r, const char *user,
                            const char *realm, const char *auth_pwfile)
{
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    const char *rpw;
    char *w, *x;
    apr_status_t sts;

    if ((sts = ap_pcfg_openfile(&f, r->pool, auth_pwfile)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, sts, r,
                      "Digest: Could not open password file: %s", auth_pwfile);
        return NULL;
    }
    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        if ((l[0] == '#') || (!l[0])) {
            continue;
        }
        rpw = l;
        w = ap_getword(r->pool, &rpw, ':');
        x = ap_getword(r->pool, &rpw, ':');

        if (x && w && !strcmp(user, w) && !strcmp(realm, x)) {
            ap_cfg_closefile(f);
            return apr_pstrdup(r->pool, rpw);
        }
    }
    ap_cfg_closefile(f);
    return NULL;
}