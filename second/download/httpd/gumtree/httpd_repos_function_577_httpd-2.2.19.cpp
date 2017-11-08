static apr_status_t ap_headers_early(request_rec *r)
{
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    /* do the fixup */
    if (dirconf->fixup_in->nelts) {
        do_headers_fixup(r, r->headers_in, dirconf->fixup_in, 1);
    }
    if (dirconf->fixup_err->nelts) {
        do_headers_fixup(r, r->err_headers_out, dirconf->fixup_err, 1);
    }
    if (dirconf->fixup_out->nelts) {
        do_headers_fixup(r, r->headers_out, dirconf->fixup_out, 1);
    }

    return DECLINED;
}