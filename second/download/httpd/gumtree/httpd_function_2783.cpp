static const char *set_override(cmd_parms *cmd, void *d_, const char *l)
{
    core_dir_config *d = d_;
    char *w;
    char *k, *v;

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);
    if (err != NULL) {
        return err;
    }

    /* Throw a warning if we're in <Location> or <Files> */
    if (ap_check_cmd_context(cmd, NOT_IN_LOCATION | NOT_IN_FILES)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "Useless use of AllowOverride in line %d.",
                     cmd->directive->line_num);
    }

    d->override = OR_NONE;
    while (l[0]) {
        w = ap_getword_conf(cmd->pool, &l);

        k = w;
        v = strchr(k, '=');
        if (v) {
                *v++ = '\0';
        }

        if (!strcasecmp(w, "Limit")) {
            d->override |= OR_LIMIT;
        }
        else if (!strcasecmp(k, "Options")) {
            d->override |= OR_OPTIONS;
            if (v)
                set_allow_opts(cmd, &(d->override_opts), v);
            else
                d->override_opts = OPT_ALL;
        }
        else if (!strcasecmp(w, "FileInfo")) {
            d->override |= OR_FILEINFO;
        }
        else if (!strcasecmp(w, "AuthConfig")) {
            d->override |= OR_AUTHCFG;
        }
        else if (!strcasecmp(w, "Indexes")) {
            d->override |= OR_INDEXES;
        }
        else if (!strcasecmp(w, "None")) {
            d->override = OR_NONE;
        }
        else if (!strcasecmp(w, "All")) {
            d->override = OR_ALL;
        }
        else {
            return apr_pstrcat(cmd->pool, "Illegal override option ", w, NULL);
        }

        d->override &= ~OR_UNSET;
    }

    return NULL;
}