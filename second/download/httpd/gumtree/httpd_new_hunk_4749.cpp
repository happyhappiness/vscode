            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00664)
                         "RewriteOptions: MaxRedirects option has been "
                         "removed in favor of the global "
                         "LimitInternalRecursion directive and will be "
                         "ignored.");
        }
        else if (!strcasecmp(w, "allowanyuri")) {
            options |= OPTION_ANYURI;
        }
        else {
            return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
                               w, "'", NULL);
        }
    }

