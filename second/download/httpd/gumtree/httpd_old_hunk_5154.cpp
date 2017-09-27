        if (!strcasecmp(w, "inherit")) {
            options |= OPTION_INHERIT;
        }
        else if (!strcasecmp(w, "inheritbefore")) {
            options |= OPTION_INHERIT_BEFORE;
        }
        else if (!strcasecmp(w, "allownoslash")) {
            options |= OPTION_NOSLASH;
        }
        else if (!strncasecmp(w, "MaxRedirects=", 13)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00664)
                         "RewriteOptions: MaxRedirects option has been "
