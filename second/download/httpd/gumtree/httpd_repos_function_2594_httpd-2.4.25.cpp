static void process_proxy_header(h2_proxy_stream *stream, const char *n, const char *v)
{
    request_rec *r = stream->r;
    static const struct {
        const char *name;
        ap_proxy_header_reverse_map_fn func;
    } transform_hdrs[] = {
        { "Location", ap_proxy_location_reverse_map },
        { "Content-Location", ap_proxy_location_reverse_map },
        { "URI", ap_proxy_location_reverse_map },
        { "Destination", ap_proxy_location_reverse_map },
        { "Set-Cookie", ap_proxy_cookie_reverse_map },
        { NULL, NULL }
    };
    proxy_dir_conf *dconf;
    int i;
    
    for (i = 0; transform_hdrs[i].name; ++i) {
        if (!ap_cstr_casecmp(transform_hdrs[i].name, n)) {
            dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
            apr_table_add(r->headers_out, n,
                          (*transform_hdrs[i].func)(r, dconf, v));
            return;
       }
    }
    if (!ap_cstr_casecmp("Link", n)) {
        dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
        apr_table_add(r->headers_out, n,
                      h2_proxy_link_reverse_map(r, dconf, 
                      stream->real_server_uri, stream->p_server_uri, v));
        return;
    }
    apr_table_add(r->headers_out, n, v);
}