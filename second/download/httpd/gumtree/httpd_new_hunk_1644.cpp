    /* If we have added something to the brigade above, sent it */
    if (!APR_BRIGADE_EMPTY(output_brigade))
        ap_pass_brigade(r->output_filters, output_brigade);

    apr_brigade_destroy(output_brigade);

    return rv;
}

/*
 * This handles ajp:// URLs
 */
static int proxy_ajp_handler(request_rec *r, proxy_worker *worker,
