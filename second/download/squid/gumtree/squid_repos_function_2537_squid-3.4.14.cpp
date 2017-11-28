static ftpListParts *
ftpListParseParts(const char *buf, struct _ftp_flags flags)
{
    ftpListParts *p = NULL;
    char *t = NULL;
    const char *ct = NULL;
    char *tokens[MAX_TOKENS];
    int i;
    int n_tokens;
    static char tbuf[128];
    char *xbuf = NULL;
    static int scan_ftp_initialized = 0;
    static regex_t scan_ftp_integer;
    static regex_t scan_ftp_time;
    static regex_t scan_ftp_dostime;
    static regex_t scan_ftp_dosdate;

    if (!scan_ftp_initialized) {
        scan_ftp_initialized = 1;
        regcomp(&scan_ftp_integer, "^[0123456789]+$", REG_EXTENDED | REG_NOSUB);
        regcomp(&scan_ftp_time, "^[0123456789:]+$", REG_EXTENDED | REG_NOSUB);
        regcomp(&scan_ftp_dosdate, "^[0123456789]+-[0123456789]+-[0123456789]+$", REG_EXTENDED | REG_NOSUB);
        regcomp(&scan_ftp_dostime, "^[0123456789]+:[0123456789]+[AP]M$", REG_EXTENDED | REG_NOSUB | REG_ICASE);
    }

    if (buf == NULL)
        return NULL;

    if (*buf == '\0')
        return NULL;

    p = (ftpListParts *)xcalloc(1, sizeof(ftpListParts));

    n_tokens = 0;

    memset(tokens, 0, sizeof(tokens));

    xbuf = xstrdup(buf);

    if (flags.tried_nlst) {
        /* Machine readable format, one name per line */
        p->name = xbuf;
        p->type = '\0';
        return p;
    }

    for (t = strtok(xbuf, w_space); t && n_tokens < MAX_TOKENS; t = strtok(NULL, w_space)) {
        tokens[n_tokens] = xstrdup(t);
        ++n_tokens;
    }

    xfree(xbuf);

    /* locate the Month field */
    for (i = 3; i < n_tokens - 2; ++i) {
        char *size = tokens[i - 1];
        char *month = tokens[i];
        char *day = tokens[i + 1];
        char *year = tokens[i + 2];

        if (!is_month(month))
            continue;

        if (regexec(&scan_ftp_integer, size, 0, NULL, 0) != 0)
            continue;

        if (regexec(&scan_ftp_integer, day, 0, NULL, 0) != 0)
            continue;

        if (regexec(&scan_ftp_time, year, 0, NULL, 0) != 0)	/* Yr | hh:mm */
            continue;

        snprintf(tbuf, 128, "%s %2s %5s",
                 month, day, year);

        if (!strstr(buf, tbuf))
            snprintf(tbuf, 128, "%s %2s %-5s",
                     month, day, year);

        char const *copyFrom = NULL;

        if ((copyFrom = strstr(buf, tbuf))) {
            p->type = *tokens[0];
            p->size = strtoll(size, NULL, 10);
            p->date = xstrdup(tbuf);

            if (flags.skip_whitespace) {
                copyFrom += strlen(tbuf);

                while (strchr(w_space, *copyFrom))
                    ++copyFrom;
            } else {
                /* XXX assumes a single space between date and filename
                 * suggested by:  Nathan.Bailey@cc.monash.edu.au and
                 * Mike Battersby <mike@starbug.bofh.asn.au> */
                copyFrom += strlen(tbuf) + 1;
            }

            p->name = xstrdup(copyFrom);

            if (p->type == 'l' && (t = strstr(p->name, " -> "))) {
                *t = '\0';
                p->link = xstrdup(t + 4);
            }

            goto found;
        }

        break;
    }

    /* try it as a DOS listing, 04-05-70 09:33PM ... */
    if (n_tokens > 3 &&
            regexec(&scan_ftp_dosdate, tokens[0], 0, NULL, 0) == 0 &&
            regexec(&scan_ftp_dostime, tokens[1], 0, NULL, 0) == 0) {
        if (!strcasecmp(tokens[2], "<dir>")) {
            p->type = 'd';
        } else {
            p->type = '-';
            p->size = strtoll(tokens[2], NULL, 10);
        }

        snprintf(tbuf, 128, "%s %s", tokens[0], tokens[1]);
        p->date = xstrdup(tbuf);

        if (p->type == 'd') {
            /* Directory.. name begins with first printable after <dir> */
            ct = strstr(buf, tokens[2]);
            ct += strlen(tokens[2]);

            while (xisspace(*ct))
                ++ct;

            if (!*ct)
                ct = NULL;
        } else {
            /* A file. Name begins after size, with a space in between */
            snprintf(tbuf, 128, " %s %s", tokens[2], tokens[3]);
            ct = strstr(buf, tbuf);

            if (ct) {
                ct += strlen(tokens[2]) + 2;
            }
        }

        p->name = xstrdup(ct ? ct : tokens[3]);
        goto found;
    }

    /* Try EPLF format; carson@lehman.com */
    if (buf[0] == '+') {
        ct = buf + 1;
        p->type = 0;

        while (ct && *ct) {
            time_t tm;
            int l = strcspn(ct, ",");
            char *tmp;

            if (l < 1)
                goto blank;

            switch (*ct) {

            case '\t':
                p->name = xstrndup(ct + 1, l + 1);
                break;

            case 's':
                p->size = atoi(ct + 1);
                break;

            case 'm':
                tm = (time_t) strtol(ct + 1, &tmp, 0);

                if (tmp != ct + 1)
                    break;	/* not a valid integer */

                p->date = xstrdup(ctime(&tm));

                *(strstr(p->date, "\n")) = '\0';

                break;

            case '/':
                p->type = 'd';

                break;

            case 'r':
                p->type = '-';

                break;

            case 'i':
                break;

            default:
                break;
            }

blank:
            ct = strstr(ct, ",");

            if (ct) {
                ++ct;
            }
        }

        if (p->type == 0) {
            p->type = '-';
        }

        if (p->name)
            goto found;
        else
            safe_free(p->date);
    }

found:

    for (i = 0; i < n_tokens; ++i)
        xfree(tokens[i]);

    if (!p->name)
        ftpListPartsFree(&p);	/* cleanup */

    return p;
}