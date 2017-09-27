        }
    }

    return NULL;
}

static const char *set_override(cmd_parms *cmd, void *d_, const char *l)
{
    core_dir_config *d = d_;
    char *w;

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);
    if (err != NULL) {
        return err;
    }

    d->override = OR_NONE;
    while (l[0]) {
        w = ap_getword_conf(cmd->pool, &l);
        if (!strcasecmp(w, "Limit")) {
            d->override |= OR_LIMIT;
        }
        else if (!strcasecmp(w, "Options")) {
            d->override |= OR_OPTIONS;
        }
        else if (!strcasecmp(w, "FileInfo")) {
            d->override |= OR_FILEINFO;
        }
        else if (!strcasecmp(w, "AuthConfig")) {
            d->override |= OR_AUTHCFG;
