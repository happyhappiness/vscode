static const char *cmd_rewritecond(cmd_parms *cmd, void *in_dconf,
                                   const char *in_str)
{
    rewrite_perdir_conf *dconf = in_dconf;
    char *str = apr_pstrdup(cmd->pool, in_str);
    rewrite_server_conf *sconf;
    rewritecond_entry *newcond;
    ap_regex_t *regexp;
    char *a1;
    char *a2;
    char *a3;
    const char *err;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    /*  make a new entry in the internal temporary rewrite rule list */
    if (cmd->path == NULL) {   /* is server command */
        newcond = apr_array_push(sconf->rewriteconds);
    }
    else {                     /* is per-directory command */
        newcond = apr_array_push(dconf->rewriteconds);
    }

    /* parse the argument line ourself
     * a1 .. a3 are substrings of str, which is a fresh copy
     * of the argument line. So we can use a1 .. a3 without
     * copying them again.
     */
    if (parseargline(str, &a1, &a2, &a3)) {
        return apr_pstrcat(cmd->pool, "RewriteCond: bad argument line '", str,
                           "'", NULL);
    }

    /* arg1: the input string */
    newcond->input = a1;

    /* arg3: optional flags field
     * (this has to be parsed first, because we need to
     *  know if the regex should be compiled with ICASE!)
     */
    newcond->flags = CONDFLAG_NONE;
    if (a3 != NULL) {
        if ((err = cmd_parseflagfield(cmd->pool, newcond, a3,
                                      cmd_rewritecond_setflag)) != NULL) {
            return apr_pstrcat(cmd->pool, "RewriteCond: ", err, NULL);
        }
    }

    /* arg2: the pattern */
    if (*a2 == '!') {
        newcond->flags |= CONDFLAG_NOTMATCH;
        ++a2;
    }

    /* determine the pattern type */
    newcond->ptype = 0;
    if (*a2 && a2[1]) {
        if (!a2[2] && *a2 == '-') {
            switch (a2[1]) {
            case 'f': newcond->ptype = CONDPAT_FILE_EXISTS; break;
            case 's': newcond->ptype = CONDPAT_FILE_SIZE;   break;
            case 'l': newcond->ptype = CONDPAT_FILE_LINK;   break;
            case 'd': newcond->ptype = CONDPAT_FILE_DIR;    break;
            case 'x': newcond->ptype = CONDPAT_FILE_XBIT;   break;
            case 'U': newcond->ptype = CONDPAT_LU_URL;      break;
            case 'F': newcond->ptype = CONDPAT_LU_FILE;     break;
            }
        }
        else {
            switch (*a2) {
            case '>': newcond->ptype = CONDPAT_STR_GT; break;
            case '<': newcond->ptype = CONDPAT_STR_LT; break;
            case '=': newcond->ptype = CONDPAT_STR_EQ;
                /* "" represents an empty string */
                if (*++a2 == '"' && a2[1] == '"' && !a2[2]) {
                    a2 += 2;
                }
                break;
            }
        }
    }

    if (newcond->ptype && newcond->ptype != CONDPAT_STR_EQ &&
        (newcond->flags & CONDFLAG_NOCASE)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "RewriteCond: NoCase option for non-regex pattern '%s' "
                     "is not supported and will be ignored.", a2);
        newcond->flags &= ~CONDFLAG_NOCASE;
    }

    newcond->pattern = a2;

    if (!newcond->ptype) {
        regexp = ap_pregcomp(cmd->pool, a2,
                             AP_REG_EXTENDED | ((newcond->flags & CONDFLAG_NOCASE)
                                             ? AP_REG_ICASE : 0));
        if (!regexp) {
            return apr_pstrcat(cmd->pool, "RewriteCond: cannot compile regular "
                               "expression '", a2, "'", NULL);
        }

        newcond->regexp  = regexp;
    }

    return NULL;
}