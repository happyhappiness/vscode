static void
parse_refreshpattern(RefreshPattern ** head)
{
    char *token;
    char *pattern;
    time_t min = 0;
    double pct = 0.0;
    time_t max = 0;
    int refresh_ims = 0;
    int store_stale = 0;
    int max_stale = -1;

#if USE_HTTP_VIOLATIONS

    int override_expire = 0;
    int override_lastmod = 0;
    int reload_into_ims = 0;
    int ignore_reload = 0;
    int ignore_no_store = 0;
    int ignore_must_revalidate = 0;
    int ignore_private = 0;
    int ignore_auth = 0;
#endif

    int i;
    RefreshPattern *t;
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
        debugs(3, DBG_CRITICAL, "FATAL: refresh_pattern missing the regex pattern parameter");
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

    i = GetPercentage();	/* token: pct */

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
        } else if (!strcmp(token, "store-stale")) {
            store_stale = 1;
        } else if (!strncmp(token, "max-stale=", 10)) {
            max_stale = xatoi(token + 10);
#if USE_HTTP_VIOLATIONS

        } else if (!strcmp(token, "override-expire"))
            override_expire = 1;
        else if (!strcmp(token, "override-lastmod"))
            override_lastmod = 1;
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

        } else if (!strcmp(token, "ignore-no-cache")) {
            debugs(22, DBG_PARSE_NOTE(2), "UPGRADE: refresh_pattern option 'ignore-no-cache' is obsolete. Remove it.");
        } else
            debugs(22, DBG_CRITICAL, "refreshAddToList: Unknown option '" << pattern << "': " << token);
    }

    if ((errcode = regcomp(&comp, pattern, flags)) != 0) {
        char errbuf[256];
        regerror(errcode, &comp, errbuf, sizeof errbuf);
        debugs(22, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(22, DBG_CRITICAL, "refreshAddToList: Invalid regular expression '" << pattern << "': " << errbuf);
        xfree(pattern);
        return;
    }

    pct = pct < 0.0 ? 0.0 : pct;
    max = max < 0 ? 0 : max;
    t = static_cast<RefreshPattern *>(xcalloc(1, sizeof(RefreshPattern)));
    t->pattern = (char *) xstrdup(pattern);
    t->compiled_pattern = comp;
    t->min = min;
    t->pct = pct;
    t->max = max;

    if (flags & REG_ICASE)
        t->flags.icase = true;

    if (refresh_ims)
        t->flags.refresh_ims = true;

    if (store_stale)
        t->flags.store_stale = true;

    t->max_stale = max_stale;

#if USE_HTTP_VIOLATIONS

    if (override_expire)
        t->flags.override_expire = true;

    if (override_lastmod)
        t->flags.override_lastmod = true;

    if (reload_into_ims)
        t->flags.reload_into_ims = true;

    if (ignore_reload)
        t->flags.ignore_reload = true;

    if (ignore_no_store)
        t->flags.ignore_no_store = true;

    if (ignore_must_revalidate)
        t->flags.ignore_must_revalidate = true;

    if (ignore_private)
        t->flags.ignore_private = true;

    if (ignore_auth)
        t->flags.ignore_auth = true;

#endif

    t->next = NULL;

    while (*head)
        head = &(*head)->next;

    *head = t;

    safe_free(pattern);
}