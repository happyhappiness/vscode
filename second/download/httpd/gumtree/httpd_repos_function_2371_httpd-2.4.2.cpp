static apr_status_t session_cookie_save(request_rec * r, session_rec * z)
{

    session_cookie_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                    &session_cookie_module);

    /* don't cache auth protected pages */
    apr_table_addn(r->headers_out, "Cache-Control", "no-cache");

    /* create RFC2109 compliant cookie */
    if (conf->name_set) {
        if (z->encoded && z->encoded[0]) {
            ap_cookie_write(r, conf->name, z->encoded, conf->name_attrs,
                            z->maxage, r->headers_out, r->err_headers_out,
                            NULL);
        }
        else {
            ap_cookie_remove(r, conf->name, conf->name_attrs, r->headers_out,
                             r->err_headers_out, NULL);
        }
    }

    /* create RFC2965 compliant cookie */
    if (conf->name2_set) {
        if (z->encoded && z->encoded[0]) {
            ap_cookie_write2(r, conf->name2, z->encoded, conf->name2_attrs,
                             z->maxage, r->headers_out, r->err_headers_out,
                             NULL);
        }
        else {
            ap_cookie_remove2(r, conf->name2, conf->name2_attrs,
                              r->headers_out, r->err_headers_out, NULL);
        }
    }

    if (conf->name_set || conf->name2_set) {
        return OK;
    }
    return DECLINED;

}