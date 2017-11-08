static const char *set_pattern(cmd_parms *cmd, void *cfg, const char *line)
{
    char *from = NULL;
    char *to = NULL;
    char *flags = NULL;
    char *ourline;
    char delim;
    subst_pattern_t *nscript;
    int is_pattern = 0;
    int ignore_case = 0;
    int flatten = 1;
    ap_regex_t *r = NULL;

    if (apr_tolower(*line) != 's') {
        return "Bad Substitute format, must be an s/// pattern";
    }
    ourline = apr_pstrdup(cmd->pool, line);
    delim = *++ourline;
    if (delim)
        from = ++ourline;
    if (from) {
        if (*ourline != delim) {
            while (*++ourline && *ourline != delim);
        }
        if (*ourline) {
            *ourline = '\0';
            to = ++ourline;
        }
    }
    if (to) {
        if (*ourline != delim) {
            while (*++ourline && *ourline != delim);
        }
        if (*ourline) {
            *ourline = '\0';
            flags = ++ourline;
        }
    }

    if (!delim || !from || !*from || !to) {
        return "Bad Substitute format, must be a complete s/// pattern";
    }

    if (flags) {
        while (*flags) {
            delim = apr_tolower(*flags);    /* re-use */
            if (delim == 'i')
                ignore_case = 1;
            else if (delim == 'n')
                is_pattern = 1;
            else if (delim == 'f')
                flatten = 1;
            else if (delim == 'q')
                flatten = 0;
            else
                return "Bad Substitute flag, only s///[infq] are supported";
            flags++;
        }
    }

    /* first see if we can compile the regex */
    if (!is_pattern) {
        r = ap_pregcomp(cmd->pool, from, AP_REG_EXTENDED |
                        (ignore_case ? AP_REG_ICASE : 0));
        if (!r)
            return "Substitute could not compile regex";
    }
    nscript = apr_array_push(((subst_dir_conf *) cfg)->patterns);
    /* init the new entries */
    nscript->pattern = NULL;
    nscript->regexp = NULL;
    nscript->replacement = NULL;
    nscript->patlen = 0;

    if (is_pattern) {
        nscript->patlen = strlen(from);
        nscript->pattern = apr_strmatch_precompile(cmd->pool, from, 
                                                   !ignore_case);
    }
    else {
        nscript->regexp = r;
    }

    nscript->replacement = to;
    nscript->replen = strlen(to);
    nscript->flatten = flatten;

    return NULL;
}