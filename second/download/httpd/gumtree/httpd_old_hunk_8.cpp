            char *v;

            if (!(groups = get_dbm_grp(r, user, conf->auth_dbmgrpfile,
                                       conf->auth_dbmtype))) {
                if (!(conf->auth_dbmauthoritative))
                    return DECLINED;
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                            "user %s not in DBM group file %s: %s",
                            user, conf->auth_dbmgrpfile, r->filename);
                ap_note_basic_auth_failure(r);
                return HTTP_UNAUTHORIZED;
            }
            orig_groups = groups;
