static const char *cmd_rewritecond(cmd_parms *cmd, void *in_dconf,
                                   const char *in_str)
{
    rewrite_perdir_conf *dconf = in_dconf;
    char *str = apr_pstrdup(cmd->pool, in_str);
    rewrite_server_conf *sconf;
    rewritecond_entry *newcond;
    ap_regex_t *regexp;
    char *a1 = NULL, *a2 = NULL, *a3 = NULL;
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
    newcond->pattern = a2;
    if (*a2 == '!') {
        newcond->flags |= CONDFLAG_NOTMATCH;
        ++a2;
    }

    /* determine the pattern type */
    newcond->ptype = CONDPAT_REGEX;
    if (strcasecmp(a1, "expr") == 0) {
        newcond->ptype = CONDPAT_AP_EXPR;
    }
    else if (*a2 && a2[1]) {
        if (*a2 == '-') {
            if (!a2[2]) {
                switch (a2[1]) {
                case 'f': newcond->ptype = CONDPAT_FILE_EXISTS; break;
                case 's': newcond->ptype = CONDPAT_FILE_SIZE;   break;
                case 'd': newcond->ptype = CONDPAT_FILE_DIR;    break;
                case 'x': newcond->ptype = CONDPAT_FILE_XBIT;   break;
                case 'h': newcond->ptype = CONDPAT_FILE_LINK;   break;
                case 'L': newcond->ptype = CONDPAT_FILE_LINK;   break;
                case 'l': newcond->ptype = CONDPAT_FILE_LINK;   break;
                case 'U': newcond->ptype = CONDPAT_LU_URL;      break;
                case 'F': newcond->ptype = CONDPAT_LU_FILE;     break;
                }
            }
            else if (a2[3]) {
                switch (a2[1]) {
                case 'l':
                    if (a2[2] == 't') {
                        a2 += 3;
                        newcond->ptype = CONDPAT_INT_LT;
                    }
                    else if (a2[2] == 'e') {
                        a2 += 3;
                        newcond->ptype = CONDPAT_INT_LE;
                    }
                    break;

                case 'g':
                    if (a2[2] == 't') {
                        a2 += 3;
                        newcond->ptype = CONDPAT_INT_GT;
                    }
                    else if (a2[2] == 'e') {
                        a2 += 3;
                        newcond->ptype = CONDPAT_INT_GE;
                    }
                    break;

                case 'e':
                    if (a2[2] == 'q') {
                        a2 += 3;
                        newcond->ptype = CONDPAT_INT_EQ;
                    }
                    break;

                case 'n':
                    if (a2[2] == 'e') {
                        /* Inversion, ensure !-ne == -eq */
                        a2 += 3;
                        newcond->ptype = CONDPAT_INT_EQ;
                        newcond->flags ^= CONDFLAG_NOTMATCH;
                    }
                    break;
                }
            }
        }
        else {
      