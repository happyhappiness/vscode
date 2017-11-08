static const char *cmd_rewritecond_parseflagfield(apr_pool_t *p,
                                                  rewritecond_entry *cfg,
                                                  char *str)
{
    char *cp;
    char *cp1;
    char *cp2;
    char *cp3;
    char *key;
    char *val;
    const char *err;

    if (str[0] != '[' || str[strlen(str)-1] != ']') {
        return "RewriteCond: bad flag delimiters";
    }

    cp = str+1;
    str[strlen(str)-1] = ','; /* for simpler parsing */
    for ( ; *cp != '\0'; ) {
        /* skip whitespaces */
        for ( ; (*cp == ' ' || *cp == '\t') && *cp != '\0'; cp++)
            ;
        if (*cp == '\0') {
            break;
        }
        cp1 = cp;
        if ((cp2 = strchr(cp, ',')) != NULL) {
            cp = cp2+1;
            for ( ; (*(cp2-1) == ' ' || *(cp2-1) == '\t'); cp2--)
                ;
            *cp2 = '\0';
            if ((cp3 = strchr(cp1, '=')) != NULL) {
                *cp3 = '\0';
                key = cp1;
                val = cp3+1;
            }
            else {
                key = cp1;
                val = "";
            }
            if ((err = cmd_rewritecond_setflag(p, cfg, key, val)) != NULL) {
                return err;
            }
        }
        else {
            break;
        }
    }

    return NULL;
}