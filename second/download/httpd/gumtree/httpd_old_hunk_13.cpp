        }
        conf->qop_list[0] = "none";
        return NULL;
    }

    if (!strcasecmp(op, "auth-int")) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, cmd->server,
                     "Digest: WARNING: qop `auth-int' currently only works "
                     "correctly for responses with no entity");
    }
    else if (strcasecmp(op, "auth")) {
        return apr_pstrcat(cmd->pool, "Unrecognized qop: ", op, NULL);
    }
