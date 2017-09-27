{
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    /* do the fixup */
    if (dirconf->fixup_in->nelts) {
        if (!do_headers_fixup(r, r->headers_in, dirconf->fixup_in, 1))
            goto err;
    }
    if (dirconf->fixup_err->nelts) {
        if (!do_headers_fixup(r, r->err_headers_out, dirconf->fixup_err, 1))
            goto err;
    }
    if (dirconf->fixup_out->nelts) {
        if (!do_headers_fixup(r, r->headers_out, dirconf->fixup_out, 1))
            goto err;
    }

    return DECLINED;
err:
    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01504)
                  "Regular expression replacement failed (replacement too long?)");
    return HTTP_INTERNAL_SERVER_ERROR;
}

static const command_rec headers_cmds[] =
{
    AP_INIT_RAW_ARGS("Header", header_cmd, &hdr_out_onsuccess, OR_FILEINFO,
                     "an optional condition, an action, header and value "
                     "followed by optional env clause"),
    AP_INIT_RAW_ARGS("RequestHeader", header_cmd, &hdr_in, OR_FILEINFO,
                     "an action, header and value followed by optional env "
                     "clause"),
    {NULL}
