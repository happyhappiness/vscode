    }
#endif

    new_cfg = apr_palloc(p, sizeof(*new_cfg));
    new_cfg->param = file;
    new_cfg->name = apr_pstrdup(p, name);
    new_cfg->getch = cfg_getch;
    new_cfg->getstr = cfg_getstr;
    new_cfg->close = cfg_close;
    new_cfg->line_number = 0;
    *ret_cfg = new_cfg;
    return APR_SUCCESS;
}


/* Allocate a ap_configfile_t handle with user defined functions and params */
AP_DECLARE(ap_configfile_t *) ap_pcfg_open_custom(
            apr_pool_t *p, const char *descr, void *param,
            apr_status_t (*getc_func) (char *ch, void *param),
            apr_status_t (*gets_func) (void *buf, apr_size_t bufsize, void *param),
            apr_status_t (*close_func) (void *param))
{
    ap_configfile_t *new_cfg = apr_palloc(p, sizeof(*new_cfg));
    new_cfg->param = param;
    new_cfg->name = descr;
    new_cfg->getch = getc_func;
    new_cfg->getstr = gets_func;
    new_cfg->close = close_func;
    new_cfg->line_number = 0;
    return new_cfg;
}

/* Read one character from a configfile_t */
AP_DECLARE(apr_status_t) ap_cfg_getc(char *ch, ap_configfile_t *cfp)
{
    apr_status_t rc = cfp->getch(ch, cfp->param);
    if (rc == APR_SUCCESS && *ch == LF)
        ++cfp->line_number;
    return rc;
}

AP_DECLARE(const char *) ap_pcfg_strerror(apr_pool_t *p, ap_configfile_t *cfp,
                                          apr_status_t rc)
{
    char buf[MAX_STRING_LEN];
    if (rc == APR_SUCCESS)
        return NULL;
    return apr_psprintf(p, "Error reading %s at line %d: %s",
                        cfp->name, cfp->line_number,
                        rc == APR_ENOSPC ? "Line too long"
                                         : apr_strerror(rc, buf, sizeof(buf)));
}

/* Read one line from open ap_configfile_t, strip LF, increase line number */
/* If custom handler does not define a getstr() function, read char by char */
static apr_status_t ap_cfg_getline_core(char *buf, apr_size_t bufsize,
                                        ap_configfile_t *cfp)
{
    apr_status_t rc;
    /* If a "get string" function is defined, use it */
    if (cfp->getstr != NULL) {
        char *cp;
        char *cbuf = buf;
        apr_size_t cbufsize = bufsize;

        while (1) {
            ++cfp->line_number;
            rc = cfp->getstr(cbuf, cbufsize, cfp->param);
            if (rc == APR_EOF) {
                if (cbuf != buf) {
                    *cbuf = '\0';
                    break;
                }
                else {
                    return APR_EOF;
                }
            }
            if (rc != APR_SUCCESS) {
                return rc;
            }

            /*
             *  check for line continuation,
             *  i.e. match [^\\]\\[\r]\n only
             */
            cp = cbuf;
            cp += strlen(cp);
            if (cp > cbuf && cp[-1] == LF) {
                cp--;
                if (cp > cbuf && cp[-1] == CR)
                    cp--;
                if (cp > cbuf && cp[-1] == '\\') {
                    cp--;
                    /*
                     * line continuation requested -
                     * then remove backslash and continue
                     */
                    cbufsize -= (cp-cbuf);
                    cbuf = cp;
                    continue;
                }
            }
            else if (cp - buf >= bufsize - 1) {
                return APR_ENOSPC;
            }
            break;
        }
    } else {
        /* No "get string" function defined; read character by character */
        apr_size_t i = 0;

        if (bufsize < 2) {
            /* too small, assume caller is crazy */
            return APR_EINVAL;
        }
        buf[0] = '\0';

        while (1) {
            char c;
            rc = cfp->getch(&c, cfp->param);
            if (rc == APR_EOF) {
                if (i > 0)
                    break;
                else
                    return APR_EOF;
            }
            if (rc != APR_SUCCESS)
                return rc;
            if (c == LF) {
                ++cfp->line_number;
                /* check for line continuation */
                if (i > 0 && buf[i-1] == '\\') {
                    i--;
                    continue;
                }
                else {
                    break;
                }
            }
            else if (i >= bufsize - 2) {
                return APR_ENOSPC;
            }
            buf[i] = c;
            ++i;
        }
        buf[i] = '\0';
    }
    return APR_SUCCESS;
}

static int cfg_trim_line(char *buf)
{
    char *start, *end;
    /*
     * Leading and trailing white space is eliminated completely
     */
    start = buf;
    while (apr_isspace(*start))
        ++start;
    /* blast trailing whitespace */
    end = &start[strlen(start)];
    while (--end >= start && apr_isspace(*end))
        *end = '\0';
    /* Zap leading whitespace by shifting */
    if (start != buf)
        memmove(buf, start, end - start + 2);
#ifdef DEBUG_CFG_LINES
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL, APLOGNO(00555) "Read config: '%s'", buf);
#endif
    return end - start + 1;
}

/* Read one line from open ap_configfile_t, strip LF, increase line number */
/* If custom handler does not define a getstr() function, read char by char */
AP_DECLARE(apr_status_t) ap_cfg_getline(char *buf, apr_size_t bufsize,
                                        ap_configfile_t *cfp)
{
    apr_status_t rc = ap_cfg_getline_core(buf, bufsize, cfp);
    if (rc == APR_SUCCESS)
        cfg_trim_line(buf);
    return rc;
}

AP_DECLARE(apr_status_t) ap_varbuf_cfg_getline(struct ap_varbuf *vb,
                                               ap_configfile_t *cfp,
                                               apr_size_t max_len)
{
    apr_status_t rc;
    vb->strlen = 0;
    *vb->buf = '\0';

    for (;;) {
        apr_size_t new_len;
        rc = ap_cfg_getline_core(vb->buf + vb->strlen, vb->avail - vb->strlen, cfp);
        if (rc == APR_ENOSPC || rc == APR_SUCCESS)
            vb->strlen += strlen(vb->buf + vb->strlen);
        if (rc != APR_ENOSPC)
            break;
        if (vb->avail >= max_len)
            return APR_ENOSPC;
        new_len = vb->avail * 2;
        if (new_len > max_len)
            new_len = max_len;
        ap_varbuf_grow(vb, new_len);
        --cfp->line_number;
    }
    if (vb->strlen > max_len)
        return APR_ENOSPC;
    if (rc == APR_SUCCESS)
        vb->strlen = cfg_trim_line(vb->buf);
    return rc;
}

/* Size an HTTP header field list item, as separated by a comma.
 * The return value is a pointer to the beginning of the non-empty list item
 * within the original string (or NULL if there is none) and the address
 * of field is shifted to the next non-comma, non-whitespace character.
