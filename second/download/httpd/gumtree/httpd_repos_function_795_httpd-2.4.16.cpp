static void modssl_ctx_cfg_merge_certkeys_array(apr_pool_t *p,
                                                apr_array_header_t *base,
                                                apr_array_header_t *add,
                                                apr_array_header_t *mrg)
{
    int i;

    /*
     * pick up to CERTKEYS_IDX_MAX+1 entries from "add" (in which case they
     * they "knock out" their corresponding entries in "base", emulating
     * the behavior with cfgMergeString in releases up to 2.4.7)
     */
    for (i = 0; i < add->nelts && i <= CERTKEYS_IDX_MAX; i++) {
        APR_ARRAY_PUSH(mrg, const char *) = APR_ARRAY_IDX(add, i, const char *);
    }

    /* add remaining ones from "base" */
    while (i < base->nelts) {
        APR_ARRAY_PUSH(mrg, const char *) = APR_ARRAY_IDX(base, i, const char *);
        i++;
    }

    /* and finally, append the rest of "add" (if there are any) */
    for (i = CERTKEYS_IDX_MAX+1; i < add->nelts; i++) {
        APR_ARRAY_PUSH(mrg, const char *) = APR_ARRAY_IDX(add, i, const char *);
    }
}