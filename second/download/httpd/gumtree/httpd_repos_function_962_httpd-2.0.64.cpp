static ap_unix_identity_t *get_suexec_id_doer(const request_rec *r)
{
    ap_unix_identity_t *ugid = NULL;
#if APR_HAS_USER
    const char *username = apr_table_get(r->notes, "mod_userdir_user");

    if (username == NULL) {
        return NULL;
    }

    if ((ugid = apr_palloc(r->pool, sizeof(*ugid))) == NULL) {
        return NULL;
    }

    if (apr_get_userid(&ugid->uid, &ugid->gid, username, r->pool) != APR_SUCCESS) {
        return NULL;
    }

    ugid->userdir = 1;
#endif 
    return ugid;
}