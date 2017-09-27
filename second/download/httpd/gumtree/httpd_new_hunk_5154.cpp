        if (!strcasecmp(w, "inherit")) {
            options |= OPTION_INHERIT;
        }
        else if (!strcasecmp(w, "inheritbefore")) {
            options |= OPTION_INHERIT_BEFORE;
        }
        else if (!strcasecmp(w, "inheritdown")) {
            options |= OPTION_INHERIT_DOWN;
        }
        else if(!strcasecmp(w, "inheritdownbefore")) {
            options |= OPTION_INHERIT_DOWN_BEFORE;
        }
        else if (!strcasecmp(w, "ignoreinherit")) {
            options |= OPTION_IGNORE_INHERIT;
        }
        else if (!strcasecmp(w, "allownoslash")) {
            options |= OPTION_NOSLASH;
        }
        else if (!strncasecmp(w, "MaxRedirects=", 13)) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00664)
                         "RewriteOptions: MaxRedirects option has been "
