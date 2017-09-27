     */
    if (conf->active != ACTIVE_ON ||
        (apr_is_empty_table(conf->expiresbytype) && !conf->expiresdefault)) {
        return;
    }
    ap_add_output_filter("MOD_EXPIRES", NULL, r, r->connection);
    return;
}
static void register_hooks(apr_pool_t *p)
{
    /* mod_expires needs to run *before* the cache save filter which is
     * AP_FTYPE_CONTENT_SET-1.  Otherwise, our expires won't be honored.
     */
    ap_register_output_filter("MOD_EXPIRES", expires_filter, NULL,
