        exit(0);
    }

    /* if either user or group are not the default, restore them */
    if (cfg->uid || cfg->gid) {
        if (setppriv(PRIV_ON, PRIV_EFFECTIVE, priv_setid) == -1) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02136)
                          "PRIV_ON failed restoring default user/group");
        }
        if (cfg->uid && (setuid(ap_unixd_config.user_id) == -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02137)
                          "Error restoring default userid");
        }
        if (cfg->gid && (setgid(ap_unixd_config.group_id) == -1)) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02138)
                          "Error restoring default group");
        }
    }

    /* restore default privileges */
    if (setppriv(PRIV_SET, PRIV_EFFECTIVE, priv_default) == -1) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, APLOGNO(02139)
                      "Error restoring default privileges");
    }
    return APR_SUCCESS;
}
static int privileges_req(request_rec *r)
{
