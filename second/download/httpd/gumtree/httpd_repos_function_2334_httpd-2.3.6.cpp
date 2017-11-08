static int 
unixd_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                 apr_pool_t *ptemp)
{
    apr_finfo_t wrapper;
    ap_unixd_config.user_name = DEFAULT_USER;
    ap_unixd_config.user_id = ap_uname2id(DEFAULT_USER);
    ap_unixd_config.group_id = ap_gname2id(DEFAULT_GROUP);

    ap_unixd_config.chroot_dir = NULL; /* none */

    /* Check for suexec */
    ap_unixd_config.suexec_enabled = 0;
    if ((apr_stat(&wrapper, SUEXEC_BIN, APR_FINFO_NORM, ptemp))
         == APR_SUCCESS) {
        if ((wrapper.protection & APR_USETID) && wrapper.user == 0
            && (access(SUEXEC_BIN, R_OK|X_OK) == 0)) {
            ap_unixd_config.suexec_enabled = 1;
        }
    }

    ap_sys_privileges_handlers(1);
    return OK;
}