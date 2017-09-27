        ap_rputs("</body></html>\n", r);
    }

    return 0;
}

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

static int status_init(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp,
                       server_rec *s)
{
    status_flags[SERVER_DEAD] = '.';  /* We don't want to assume these are in */
    status_flags[SERVER_READY] = '_'; /* any particular order in scoreboard.h */
