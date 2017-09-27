
        cert->path = ap_server_root_relative(cmd->pool, file);
        if (cert->path &&
            ((rv = apr_stat (&finfo, cert->path, APR_FINFO_MIN, cmd->pool))
                != APR_SUCCESS))
        {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server,
                         "LDAP: Could not open SSL trusted certificate "
                         "authority file - %s",
                         cert->path == NULL ? file : cert->path);
            return "Invalid global certificate file path";
        }
    }
