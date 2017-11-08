static int x_get_mgmt_items(apr_pool_t *p, const char *val, apr_hash_t *ht)
{
    /* We have nothing to do here but trace the call, and no context
     * in which to trace it.
     */
    trace_nocontext(p, __FILE__, __LINE__, "x_check_config()");
    return DECLINED;
}