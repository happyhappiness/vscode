static void ap_logio_add_bytes_out(conn_rec *c, apr_off_t bytes)
{
    logio_config_t *cf = ap_get_module_config(c->conn_config, &logio_module);
    cf->bytes_out += bytes;

    if (!cf->first_byte_seen) {
        /* cleared during log_transaction, after mod_log_config */ 
        cf->first_byte_seen = 1; 

        if (cf->r) { 
            logio_dirconf_t *conf = (logio_dirconf_t*) 
                ap_get_module_config(cf->r->per_dir_config, &logio_module);
            if (conf && conf->track_ttfb) { 
                cf->ttfb = apr_time_now() - cf->r->request_time;
            }
        }
    }
}