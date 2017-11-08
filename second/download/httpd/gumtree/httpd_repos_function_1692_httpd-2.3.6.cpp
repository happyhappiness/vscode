static void process_proxy_header(request_rec *r, proxy_dir_conf *c,
                                 const char *key, const char *value)
{
    static const char *date_hdrs[]
        = { "Date", "Expires", "Last-Modified", NULL };
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
    int i;
    for (i = 0; date_hdrs[i]; ++i) {
        if (!strcasecmp(date_hdrs[i], key)) {
            apr_table_add(r->headers_out, key,
                          ap_proxy_date_canon(r->pool, value));
            return;
        }
    }
    for (i = 0; transform_hdrs[i].name; ++i) {
        if (!strcasecmp(transform_hdrs[i].name, key)) {
            apr_table_add(r->headers_out, key,
                          (*transform_hdrs[i].func)(r, c, value));
            return;
       }
    }
    apr_table_add(r->headers_out, key, value);
    return;
}