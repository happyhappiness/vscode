static void
parse_refreshpattern(refresh_t ** head)
{
    char *token;
    char *pattern;
    time_t min = 0;
    double pct = 0.0;
    time_t max = 0;
    int refresh_ims = 0;
#if HTTP_VIOLATIONS

    int override_expire = 0;
    int override_lastmod = 0;
    int reload_into_ims = 0;
    int ignore_reload = 0;
    int ignore_no_cache = 0;
    int ignore_no_store = 0;
    int ignore_must_revalidate = 0;
    int ignore_private = 0;
    int ignore_auth = 0;
#endif

    int i;
    refresh_t *t;
    regex_t comp;
    int errcode;
    int flags = REG_EXTENDED | REG_NOSUB;

    if ((token = strtok(NULL, w_space)) == NULL) {
        self_destruct();
        return;
    }

    if (strcmp(token, "-i") == 0) {
        flags |= REG_ICASE;
        token = strtok(NULL, w_space);
    } else if (strcmp(token, "+i") == 0) {
        flags &= ~REG_ICASE;
        token = strtok(NULL, w_space);
    }

    if (token == NULL) {
        self_destruct();
        return;
    }

    pattern = xstrdup(token);

    i = GetInteger();		/* token: min */

    /* catch negative and insanely huge values close to 32-bit wrap */
    if (i < 0) {
        debugs(3, DBG_IMPORTANT, "WARNING: refresh_pattern minimum age negative. Cropped back to zero.");
        i = 0;
    }
    if (i > 60*24*365) {
        debugs(3, DBG_IMPORTANT, "WARNING: refresh_pattern minimum age too high. Cropped back to 1 year.");
        i = 60*24*365;
    }

    min = (time_t) (i * 60);	/* convert minutes to seconds */

    i = GetInteger();		/* token: pct */

    pct = (double) i / 100.0;

    i = GetInteger();		/* token: max */

    /* catch negative and insanely huge values close to 32-bit wrap */
    if (i < 0) {
        debugs(3, DBG_IMPORTANT, "WARNING: refresh_pattern maximum age negative. Cropped back to zero.");
        i = 0;
    }
    if (i > 60*24*365) {
        debugs(3, DBG_IMPORTANT, "WARNING: refresh_pattern maximum age too high. Cropped back to 1 year.");
        i = 60*24*365;
    }

    max = (time_t) (i * 60);	/* convert minutes to seconds */

    /* Options */
    while ((token = strtok(NULL, w_space)) != NULL) {
        if (!strcmp(token, "refresh-ims")) {
            refresh_ims = 1;
#if HTTP_VIOLATIONS

        } else if (!strcmp(token, "override-expire"))
            override_expire = 1;
        else if (!strcmp(token, "override-lastmod"))
            override_lastmod = 1;
        else if (!strcmp(token, "ignore-no-cache"))
            ignore_no_cache = 1;
        else if (!strcmp(token, "ignore-no-store"))
            ignore_no_store = 1;
        else if (!strcmp(token, "ignore-must-revalidate"))
            ignore_must_revalidate = 1;
        else if (!strcmp(token, "ignore-private"))
            ignore_private = 1;
        else if (!strcmp(token, "ignore-auth"))
            ignore_auth = 1;
        else if (!strcmp(token, "reload-into-ims")) {
            reload_into_ims = 1;
            refresh_nocache_hack = 1;
            /* tell client_side.c that this is used */
        } else if (!strcmp(token, "ignore-reload")) {
            ignore_reload = 1;
            refresh_nocache_hack = 1;
            /* tell client_side.c that this is used */
#endif

        } else
            debugs(22, 0, "redreshAddToList: Unknown option '" << pattern << "': " << token);
    }

    if ((errcode = regcomp(&comp, pattern, flags)) != 0) {
        char errbuf[256];
        regerror(errcode, &comp, errbuf, sizeof errbuf);
        debugs(22, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(22, 0, "refreshAddToList: Invalid regular expression '" << pattern << "': " << errbuf);
        return;
    }

    pct = pct < 0.0 ? 0.0 : pct;
    max = max < 0 ? 0 : max;
    t = static_cast<refresh_t *>(xcalloc(1, sizeof(refresh_t)));
    t->pattern = (char *) xstrdup(pattern);
    t->compiled_pattern = comp;
    t->min = min;
    t->pct = pct;
    t->max = max;

    if (flags & REG_ICASE)
        t->flags.icase = 1;

    if (refresh_ims)
        t->flags.refresh_ims = 1;

#if HTTP_VIOLATIONS

    if (override_expire)
        t->flags.override_expire = 1;

    if (override_lastmod)
        t->flags.override_lastmod = 1;

    if (reload_into_ims)
        t->flags.reload_into_ims = 1;

    if (ignore_reload)
        t->flags.ignore_reload = 1;

    if (ignore_no_cache)
        t->flags.ignore_no_cache = 1;

    if (ignore_no_store)
        t->flags.ignore_no_store = 1;

    if (ignore_must_revalidate)
        t->flags.ignore_must_revalidate = 1;

    if (ignore_private)
        t->flags.ignore_private = 1;

    if (ignore_auth)
        t->flags.ignore_auth = 1;

#endif

    t->next = NULL;

    while (*head)
        head = &(*head)->next;

    *head = t;

    safe_free(pattern);
}