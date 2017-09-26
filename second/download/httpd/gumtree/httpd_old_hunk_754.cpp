
    if (dirconf->fixup_out->nelts || dirconf->fixup_err->nelts) {
        ap_add_output_filter("FIXUP_HEADERS_OUT", NULL, r, r->connection);
    }
}

static void ap_headers_insert_error_filter(request_rec *r)
{
    headers_conf *dirconf = ap_get_module_config(r->per_dir_config,
                                                 &headers_module);

    if (dirconf->fixup_err->nelts) {
