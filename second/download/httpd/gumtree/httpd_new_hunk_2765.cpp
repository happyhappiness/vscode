    suexec_config_t *cfg = (suexec_config_t *) mconfig;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);

    if (err != NULL) {
        return err;
    }

    if (!ap_unixd_config.suexec_enabled) {
        return apr_pstrcat(cmd->pool, "SuexecUserGroup configured, but "
                           "suEXEC is disabled: ",
                           ap_unixd_config.suexec_disabled_reason, NULL);
    }

    cfg->ugid.uid = ap_uname2id(uid);
    cfg->ugid.gid = ap_gname2id(gid);
    cfg->ugid.userdir = 0;
    cfg->active = 1;

    return NULL;
}

static ap_unix_identity_t *get_suexec_id_doer(const request_rec *r)
{
    suexec_config_t *cfg =
