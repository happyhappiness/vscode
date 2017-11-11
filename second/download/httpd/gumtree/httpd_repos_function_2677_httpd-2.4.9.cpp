static apr_array_header_t *split_argv(apr_pool_t *p, const char *interp,
                                      const char *cgiprg, const char *cgiargs)
{
    apr_array_header_t *args = apr_array_make(p, 8, sizeof(char*));
    char *d = apr_palloc(p, strlen(interp)+1);
    const char *ch = interp;
    const char **arg;
    int prgtaken = 0;
    int argtaken = 0;
    int inquo;
    int sl;

    while (*ch) {
        /* Skip on through Deep Space */
        if (apr_isspace(*ch)) {
            ++ch; continue;
        }
        /* One Arg */
        if (((*ch == '$') || (*ch == '%')) && (*(ch + 1) == '*')) {
            const char *cgiarg = cgiargs;
            argtaken = 1;
            for (;;) {
                char *w = ap_getword_nulls(p, &cgiarg, '+');
                if (!*w) {
                    break;
                }
                ap_unescape_url(w);
                prep_string((const char**)&w, p);
                arg = (const char**)apr_array_push(args);
                *arg = ap_escape_shell_cmd(p, w);
            }
            ch += 2;
            continue;
        }
        if (((*ch == '$') || (*ch == '%')) && (*(ch + 1) == '1')) {
            /* Todo: Make short name!!! */
            prgtaken = 1;
            arg = (const char**)apr_array_push(args);
            if (*ch == '%') {
                char *repl = apr_pstrdup(p, cgiprg);
                *arg = repl;
                while ((repl = strchr(repl, '/'))) {
                    *repl++ = '\\';
                }
            }
            else {
                *arg = cgiprg;
            }
            ch += 2;
            continue;
        }
        if ((*ch == '\"') && ((*(ch + 1) == '$')
                              || (*(ch + 1) == '%')) && (*(ch + 2) == '1')
            && (*(ch + 3) == '\"')) {
            prgtaken = 1;
            arg = (const char**)apr_array_push(args);
            if (*(ch + 1) == '%') {
                char *repl = apr_pstrdup(p, cgiprg);
                *arg = repl;
                while ((repl = strchr(repl, '/'))) {
                    *repl++ = '\\';
                }
            }
            else {
                *arg = cgiprg;
            }
            ch += 4;
            continue;
        }
        arg = (const char**)apr_array_push(args);
        *arg = d;
        inquo = 0;
        while (*ch) {
            if (apr_isspace(*ch) && !inquo) {
                ++ch; break;
            }
            /* Get 'em backslashes */
            for (sl = 0; *ch == '\\'; ++sl) {
                *d++ = *ch++;
            }
            if (sl & 1) {
                /* last unmatched '\' + '"' sequence is a '"' */
                if (*ch == '\"') {
                    *(d - 1) = *ch++;
                }
                continue;
            }
            if (*ch == '\"') {
                /* '""' sequence within quotes is a '"' */
                if (*++ch == '\"' && inquo) {
                    *d++ = *ch++; continue;
                }
                /* Flip quote state */
                inquo = !inquo;
                if (apr_isspace(*ch) && !inquo) {
                    ++ch; break;
                }
                /* All other '"'s are Munched */
                continue;
            }
            /* Anything else is, well, something else */
            *d++ = *ch++;
        }
        /* Term that arg, already pushed on args */
        *d++ = '\0';
    }

    if (!prgtaken) {
        arg = (const char**)apr_array_push(args);
        *arg = cgiprg;
    }

    if (!argtaken) {
        const char *cgiarg = cgiargs;
        for (;;) {
            char *w = ap_getword_nulls(p, &cgiarg, '+');
            if (!*w) {
                break;
            }
            ap_unescape_url(w);
            prep_string((const char**)&w, p);
            arg = (const char**)apr_array_push(args);
            *arg = ap_escape_shell_cmd(p, w);
        }
    }

    arg = (const char**)apr_array_push(args);
    *arg = NULL;

    return args;
}