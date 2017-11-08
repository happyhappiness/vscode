static int status_pre_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp)
{
    /* When mod_status is loaded, default our ExtendedStatus to 'on'
     * other modules which prefer verbose scoreboards may play a similar game.
     * If left to their own requirements, mpm modules can make do with simple
     * scoreboard entries.
     */
    ap_extended_status = 1;
    return OK;
}