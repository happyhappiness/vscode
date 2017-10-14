apr_pstrcat(cmd->pool, "SuexecUserGroup configured, but "
                           "suEXEC is disabled: ",
                           ap_unixd_config.suexec_disabled_reason, NULL);