static apr_status_t privileges_end_req(void *data)
{
    request_rec *r = data;
    priv_cfg *cfg = ap_get_module_config(r->server->module_config,
                                         &privileges_module);
    priv_dir_cfg *dcfg = ap_get_module_config(r->per_dir_config,
                                              &privileges_module);

    /* ugly hack: grab default uid and gid from unixd */
    extern unixd_config_rec ap_unixd_config;

    /* If we forked a child, we dropped privilege to revert, so
     * all we can do now is exit
     */
    if ((cfg->mode == PRIV_SECURE) ||
        ((cfg->mode == PRIV_SELECTIVE) && (dcfg->mode == PRIV_SECURE))) {
        exit(0);
    }

    /* if either user or group are not the default, restore them */
    if (cfg->uid || cfg->gid) {
        if (setppriv(PRIV_ON, PRIV_EFFECTIVE, priv_setid) == -1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "PRIV_ON failed restoring default user/group");
        }
        if (cfg->uid && (setuid(ap_unixd_config.user_id) == -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Error restoring default userid");
        }
        if (cfg->gid && (setgid(ap_unixd_config.group_id) == -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Error restoring default group");
        }
    }

    /* restore default privileges */
    if (setppriv(PRIV_SET, PRIV_EFFECTIVE, priv_default) == -1) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                      "Error restoring default privileges");
    }
    return APR_SUCCESS;
}