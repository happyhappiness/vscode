static mutex_cfg_t *mxcfg_lookup(apr_pool_t *p, const char *type)
{
    mutex_cfg_t *defcfg, *mxcfg, *newcfg;

    defcfg = apr_hash_get(mxcfg_by_type, "default", APR_HASH_KEY_STRING);

    /* MUST exist in table, or wasn't registered */
    mxcfg = apr_hash_get(mxcfg_by_type, type, APR_HASH_KEY_STRING);
    if (!mxcfg) {
        return NULL;
    }

    /* order of precedence:
     * 1. Mutex directive for this mutex
     * 2. Mutex directive for "default"
     * 3. Defaults for this mutex from ap_mutex_register()
     * 4. Global defaults
     */

    if (mxcfg->set) {
        newcfg = mxcfg;
    }
    else if (defcfg->set) {
        newcfg = defcfg;
    }
    else if (mxcfg->none || mxcfg->mech != APR_LOCK_DEFAULT) {
        newcfg = mxcfg;
    }
    else {
        newcfg = defcfg;
    }

    if (!newcfg->none && mutex_needs_file(newcfg->mech) && !newcfg->dir) {
        /* a file-based mutex mechanism was configured, but
         * without a mutex file directory; go back through
         * the chain to find the directory, store in new
         * mutex cfg structure
         */
        newcfg = apr_pmemdup(p, newcfg, sizeof *newcfg);

        /* !true if dir not already set: mxcfg->set && defcfg->dir */
        if (defcfg->set && defcfg->dir) {
            newcfg->dir = defcfg->dir;
        }
        else if (mxcfg->dir) {
            newcfg->dir = mxcfg->dir;
        }
        else {
            newcfg->dir = defcfg->dir;
        }
    }

    return newcfg;
}