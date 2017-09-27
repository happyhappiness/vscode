            return ap_send_http_options(r);
        }
        return HTTP_METHOD_NOT_ALLOWED;
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

    ap_set_version(pconf);
    ap_setup_make_content_type(pconf);
    return OK;
}

