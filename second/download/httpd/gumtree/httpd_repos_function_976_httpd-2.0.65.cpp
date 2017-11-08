static const char *cmd_rewritecond(cmd_parms *cmd, void *in_dconf,
                                   const char *in_str)
{
    rewrite_perdir_conf *dconf = in_dconf;
    char *str = apr_pstrdup(cmd->pool, in_str);
    rewrite_server_conf *sconf;
    rewritecond_entry *newcond;
    regex_t *regexp;
    char *a1;
    char *a2;
    char *a3;
    char *cp;
    const char *err;
    int rc;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    /*  make a new entry in the internal temporary rewrite rule list */
    if (cmd->path == NULL) {   /* is server command */
        newcond = apr_array_push(sconf->rewriteconds);
    }
    else {                     /* is per-directory command */
        newcond = apr_array_push(dconf->rewriteconds);
    }

    /*  parse the argument line ourself */
    if (parseargline(str, &a1, &a2, &a3)) {
        return apr_pstrcat(cmd->pool, "RewriteCond: bad argument line '", str,
                           "'", NULL);
    }

    /*  arg1: the input string */
    newcond->input = apr_pstrdup(cmd->pool, a1);

    /* arg3: optional flags field
       (this have to be first parsed, because we need to
        know if the regex should be compiled with ICASE!) */
    newcond->flags = CONDFLAG_NONE;
    if (a3 != NULL) {
        if ((err = cmd_rewritecond_parseflagfield(cmd->pool, newcond,
                                                  a3)) != NULL) {
            return err;
        }
    }

    /*  arg2: the pattern
        try to compile the regexp to test if is ok */
    cp = a2;
    if (cp[0] == '!') {
        newcond->flags |= CONDFLAG_NOTMATCH;
        cp++;
    }

    /* now be careful: Under the POSIX regex library
       we can compile the pattern for case insensitive matching,
       under the old V8 library we have to do it self via a hack */
    if (newcond->flags & CONDFLAG_NOCASE) {
        rc = ((regexp = ap_pregcomp(cmd->pool, cp, REG_EXTENDED|REG_ICASE))
              == NULL);
    }
    else {
        rc = ((regexp = ap_pregcomp(cmd->pool, cp, REG_EXTENDED)) == NULL);
    }
    if (rc) {
        return apr_pstrcat(cmd->pool,
                           "RewriteCond: cannot compile regular expression '",
                           a2, "'", NULL);
    }

    newcond->pattern = apr_pstrdup(cmd->pool, cp);
    newcond->regexp  = regexp;

    return NULL;
}