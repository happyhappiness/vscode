void
mimeInit(char *filename)
{
    FILE *fp;
    char buf[BUFSIZ];
    char chopbuf[BUFSIZ];
    char *t;
    char *pattern;
    char *icon;
    char *type;
    char *encoding;
    char *mode;
    char *option;
    int view_option;
    int download_option;
    regex_t re;
    MimeEntry *m;
    int re_flags = REG_EXTENDED | REG_NOSUB | REG_ICASE;

    if (filename == NULL)
        return;

    if ((fp = fopen(filename, "r")) == NULL) {
        int xerrno = errno;
        debugs(25, DBG_IMPORTANT, "mimeInit: " << filename << ": " << xstrerr(xerrno));
        return;
    }

#if _SQUID_WINDOWS_
    setmode(fileno(fp), O_TEXT);
#endif

    mimeFreeMemory();

    while (fgets(buf, BUFSIZ, fp)) {
        if ((t = strchr(buf, '#')))
            *t = '\0';

        if ((t = strchr(buf, '\r')))
            *t = '\0';

        if ((t = strchr(buf, '\n')))
            *t = '\0';

        if (buf[0] == '\0')
            continue;

        xstrncpy(chopbuf, buf, BUFSIZ);

        if ((pattern = strtok(chopbuf, w_space)) == NULL) {
            debugs(25, DBG_IMPORTANT, "mimeInit: parse error: '" << buf << "'");
            continue;
        }

        if ((type = strtok(NULL, w_space)) == NULL) {
            debugs(25, DBG_IMPORTANT, "mimeInit: parse error: '" << buf << "'");
            continue;
        }

        if ((icon = strtok(NULL, w_space)) == NULL) {
            debugs(25, DBG_IMPORTANT, "mimeInit: parse error: '" << buf << "'");
            continue;
        }

        if ((encoding = strtok(NULL, w_space)) == NULL) {
            debugs(25, DBG_IMPORTANT, "mimeInit: parse error: '" << buf << "'");
            continue;
        }

        if ((mode = strtok(NULL, w_space)) == NULL) {
            debugs(25, DBG_IMPORTANT, "mimeInit: parse error: '" << buf << "'");
            continue;
        }

        download_option = 0;
        view_option = 0;

        while ((option = strtok(NULL, w_space)) != NULL) {
            if (!strcmp(option, "+download"))
                download_option = 1;
            else if (!strcmp(option, "+view"))
                view_option = 1;
            else
                debugs(25, DBG_IMPORTANT, "mimeInit: unknown option: '" << buf << "' (" << option << ")");
        }

        if (regcomp(&re, pattern, re_flags) != 0) {
            debugs(25, DBG_IMPORTANT, "mimeInit: regcomp error: '" << buf << "'");
            continue;
        }

        m = new MimeEntry(pattern,re,type,encoding,mode,view_option,
                          download_option,icon);

        *MimeTableTail = m;

        MimeTableTail = &m->next;

        debugs(25, 5, "mimeInit: added '" << buf << "'");
    }

    fclose(fp);

    for (m = MimeTable; m != NULL; m = m->next)
        m->theIcon.load();
    debugs(25, DBG_IMPORTANT, "Finished loading MIME types and icons.");
}