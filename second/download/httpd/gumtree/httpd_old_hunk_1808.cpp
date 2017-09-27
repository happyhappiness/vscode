    }
}

/* Optional function coming from mod_logio, used for logging of output
 * traffic
 */
APR_OPTIONAL_FN_TYPE(ap_logio_add_bytes_out) *logio_add_bytes_out;

static int core_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    logio_add_bytes_out = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_out);
    ident_lookup = APR_RETRIEVE_OPTIONAL_FN(ap_ident_lookup);

    set_banner(pconf);
    ap_setup_make_content_type(pconf);
    return OK;
}

static void core_insert_filter(request_rec *r)
{
    core_dir_config *conf = (core_dir_config *)
