static int check_site(request_rec * r, const char *site, const char *sent_user, const char *sent_hash)
{

    if (site && sent_user && sent_hash) {
        const char *hash = ap_md5(r->pool,
                      (unsigned char *) apr_pstrcat(r->pool, sent_user, ":", site, NULL));

        if (!strcmp(sent_hash, hash)) {
            return OK;
        }
        else {
            return AUTH_USER_NOT_FOUND;
        }
    }

    return DECLINED;

}