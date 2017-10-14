static int session_dbd_save(request_rec * r, session_rec * z)
{

    char *buffer;
    apr_status_t ret = APR_SUCCESS;
    session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_dbd_module);

    /* support anonymous sessions */
    if (conf->name_set || conf->name2_set) {

        /* don't cache pages with a session */
        apr_table_addn(r->headers_out, "Cache-Control", "no-cache");

        /* must we create a uuid? */
        buffer = apr_pcalloc(r->pool, APR_UUID_FORMATTED_LENGTH + 1);
        apr_uuid_format(buffer, z->uuid);

        /* save the session with the uuid as key */
        if (z->encoded && z->encoded[0]) {
            ret = dbd_save(r, buffer, z->encoded, z->expiry);
        }
        else {
            ret = dbd_remove(r, buffer);
        }
        if (ret != APR_SUCCESS) {
            return ret;
        }

        /* create RFC2109 compliant cookie */
        if (conf->name_set) {
            ap_cookie_write(r, conf->name, buffer, conf->name_attrs, z->maxage, r->headers_out, r->err_headers_out, NULL);
        }

        /* create RFC2965 compliant cookie */
        if (conf->name2_set) {
            ap_cookie_write2(r, conf->name2, buffer, conf->name2_attrs, z->maxage, r->headers_out, r->err_headers_out, NULL);
        }

        return OK;

    }

    /* save named session */
    else if (conf->peruser) {

        /* don't cache pages with a session */
        apr_table_addn(r->headers_out, "Cache-Control", "no-cache");

        if (r->user) {
            ret = dbd_save(r, r->user, z->encoded, z->expiry);
            if (ret != APR_SUCCESS) {
                return ret;
            }
            return OK;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
               "peruser sessions can only be saved if a user is logged in, "
                          "session not saved: %s", r->uri);
        }
    }

    return DECLINED;

}