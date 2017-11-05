static void note_cookie_auth_failure(request_rec * r)
{
    auth_form_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                      &auth_form_module);

    if (conf->location && ap_strchr_c(conf->location, ':')) {
        apr_table_setn(r->err_headers_out, "Location", conf->location);
    }
}