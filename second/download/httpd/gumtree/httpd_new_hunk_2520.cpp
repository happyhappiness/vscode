        ap_remove_output_filter(next);
        next = next->next;
    }

    /* kick off the filter stack */
    out = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    e = apr_bucket_eos_create(out->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(out, e);

    return ap_pass_brigade_fchk(r, out,
                                "cache_quick_handler(%s): ap_pass_brigade returned",
                                cache->provider_name);
}

/**
 * If the two filter handles are present within the filter chain, replace
 * the last instance of the first filter with the last instance of the
 * second filter, and return true. If the second filter is not present at
 * all, the first filter is removed, and false is returned. If neither
 * filter is present, false is returned and this function does nothing.
 * If a stop filter is specified, processing will stop once this filter is
 * reached.
 */
static int cache_replace_filter(ap_filter_t *next, ap_filter_rec_t *from,
        ap_filter_rec_t *to, ap_filter_rec_t *stop) {
    ap_filter_t *ffrom = NULL, *fto = NULL;
    while (next && next->frec != stop) {
        if (next->frec == from) {
            ffrom = next;
        }
        if (next->frec == to) {
            fto = next;
        }
        next = next->next;
    }
    if (ffrom && fto) {
        ffrom->frec = fto->frec;
