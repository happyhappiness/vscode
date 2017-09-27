    }
#endif

    new_cfg = apr_palloc(p, sizeof(*new_cfg));
    new_cfg->param = file;
    new_cfg->name = apr_pstrdup(p, name);
    new_cfg->getch = (int (*)(void *)) cfg_getch;
    new_cfg->getstr = (void *(*)(void *, size_t, void *)) cfg_getstr;
    new_cfg->close = (int (*)(void *)) cfg_close;
    new_cfg->line_number = 0;
    *ret_cfg = new_cfg;
    return APR_SUCCESS;
}


/* Allocate a ap_configfile_t handle with user defined functions and params */
AP_DECLARE(ap_configfile_t *) ap_pcfg_open_custom(apr_pool_t *p,
                       const char *descr,
                       void *param,
                       int(*getch)(void *param),
                       void *(*getstr) (void *buf, size_t bufsiz, void *param),
                       int(*close_func)(void *param))
{
    ap_configfile_t *new_cfg = apr_palloc(p, sizeof(*new_cfg));
#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                 "Opening config handler %s", descr);
#endif
    new_cfg->param = param;
    new_cfg->name = descr;
    new_cfg->getch = getch;
    new_cfg->getstr = getstr;
    new_cfg->close = close_func;
    new_cfg->line_number = 0;
    return new_cfg;
}

/* Read one character from a configfile_t */
AP_DECLARE(int) ap_cfg_getc(ap_configfile_t *cfp)
{
    register int ch = cfp->getch(cfp->param);
    if (ch == LF)
        ++cfp->line_number;
    return ch;
}

/* Read one line from open ap_configfile_t, strip LF, increase line number */
/* If custom handler does not define a getstr() function, read char by char */
AP_DECLARE(int) ap_cfg_getline(char *buf, size_t bufsize, ap_configfile_t *cfp)
{
    /* If a "get string" function is defined, use it */
    if (cfp->getstr != NULL) {
        char *src, *dst;
        char *cp;
        char *cbuf = buf;
        size_t cbufsize = bufsize;

        while (1) {
            ++cfp->line_number;
            if (cfp->getstr(cbuf, cbufsize, cfp->param) == NULL)
                return 1;

            /*
             *  check for line continuation,
             *  i.e. match [^\\]\\[\r]\n only
             */
            cp = cbuf;
            while (cp < cbuf+cbufsize && *cp != '\0')
                cp++;
            if (cp > cbuf && cp[-1] == LF) {
                cp--;
                if (cp > cbuf && cp[-1] == CR)
                    cp--;
                if (cp > cbuf && cp[-1] == '\\') {
                    cp--;
                    if (!(cp > cbuf && cp[-1] == '\\')) {
                        /*
                         * line continuation requested -
                         * then remove backslash and continue
                         */
                        cbufsize -= (cp-cbuf);
                        cbuf = cp;
                        continue;
                    }
                    else {
                        /*
                         * no real continuation because escaped -
                         * then just remove escape character
                         */
                        for ( ; cp < cbuf+cbufsize && *cp != '\0'; cp++)
                            cp[0] = cp[1];
                    }
                }
            }
            break;
        }

        /*
         * Leading and trailing white space is eliminated completely
         */
        src = buf;
        while (apr_isspace(*src))
            ++src;
        /* blast trailing whitespace */
        dst = &src[strlen(src)];
        while (--dst >= src && apr_isspace(*dst))
            *dst = '\0';
        /* Zap leading whitespace by shifting */
        if (src != buf)
            for (dst = buf; (*dst++ = *src++) != '\0'; )
                ;

#ifdef DEBUG_CFG_LINES
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, "Read config: %s", buf);
#endif
        return 0;
    } else {
        /* No "get string" function defined; read character by character */
        register int c;
        register size_t i = 0;

        buf[0] = '\0';
        /* skip leading whitespace */
        do {
            c = cfp->getch(cfp->param);
        } while (c == '\t' || c == ' ');

        if (c == EOF)
            return 1;

        if(bufsize < 2) {
            /* too small, assume caller is crazy */
            return 1;
        }

        while (1) {
            if ((c == '\t') || (c == ' ')) {
                buf[i++] = ' ';
                while ((c == '\t') || (c == ' '))
                    c = cfp->getch(cfp->param);
            }
            if (c == CR) {
                /* silently ignore CR (_assume_ that a LF follows) */
                c = cfp->getch(cfp->param);
            }
            if (c == LF) {
                /* increase line number and return on LF */
                ++cfp->line_number;
            }
            if (c == EOF || c == 0x4 || c == LF || i >= (bufsize - 2)) {
                /*
                 *  check for line continuation
                 */
                if (i > 0 && buf[i-1] == '\\') {
                    i--;
                    if (!(i > 0 && buf[i-1] == '\\')) {
                        /* line is continued */
                        c = cfp->getch(cfp->param);
                        continue;
                    }
                    /* else nothing needs be done because
                     * then the backslash is escaped and
                     * we just strip to a single one
                     */
                }
                /* blast trailing whitespace */
                while (i > 0 && apr_isspace(buf[i - 1]))
                    --i;
                buf[i] = '\0';
#ifdef DEBUG_CFG_LINES
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                             "Read config: %s", buf);
#endif
                return 0;
            }
            buf[i] = c;
            ++i;
            c = cfp->getch(cfp->param);
        }
    }
}

/* Size an HTTP header field list item, as separated by a comma.
 * The return value is a pointer to the beginning of the non-empty list item
 * within the original string (or NULL if there is none) and the address
 * of field is shifted to the next non-comma, non-whitespace character.
