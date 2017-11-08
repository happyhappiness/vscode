static apr_status_t ap_headers_fixup(request_rec *r)
{
    headers_conf *serverconf = ap_get_module_config(r->server->module_config,
                                                    &headers_module);
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    /* do the fixup */
    if (serverconf->fixup_in->nelts || dirconf->fixup_in->nelts) {
        do_headers_fixup(r, hdr_in, serverconf->fixup_in);
        do_headers_fixup(r, hdr_in, dirconf->fixup_in);
    }

    return DECLINED;
}