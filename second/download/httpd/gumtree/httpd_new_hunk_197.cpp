{
    headers_conf *serverconf = ap_get_module_config(f->r->server->module_config,
                                                    &headers_module);
    headers_conf *dirconf = ap_get_module_config(f->r->per_dir_config,
                                                 &headers_module);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, f->r->server,
		 "headers: ap_headers_output_filter()");

    /* do the fixup */
    do_headers_fixup(f->r, hdr_out, serverconf->fixup_out);
    do_headers_fixup(f->r, hdr_out, dirconf->fixup_out);

