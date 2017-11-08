static void proxy_html_insert(request_rec *r)
{
    proxy_html_conf *cfg;
    cfg = ap_get_module_config(r->per_dir_config, &proxy_html_module);
    if (cfg->enabled) {
        if (xml2enc_filter)
            xml2enc_filter(r, NULL, ENCIO_INPUT_CHECKS);
        ap_add_output_filter("proxy-html", NULL, r, r->connection);
    }
}