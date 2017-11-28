void
Helper::ChildConfig::parseConfig()
{
    char const *token = ConfigParser::NextToken();

    if (!token)
        self_destruct();

    /* starts with a bare number for the max... back-compatible */
    n_max = xatoui(token);

    if (n_max < 1) {
        debugs(0, DBG_CRITICAL, "ERROR: The maximum number of processes cannot be less than 1.");
        self_destruct();
    }

    /* Parse extension options */
    for (; (token = ConfigParser::NextToken()) ;) {
        if (strncmp(token, "startup=", 8) == 0) {
            n_startup = xatoui(token + 8);
        } else if (strncmp(token, "idle=", 5) == 0) {
            n_idle = xatoui(token + 5);
            if (n_idle < 1) {
                debugs(0, DBG_CRITICAL, "WARNING OVERIDE: Using idle=0 for helpers causes request failures. Overiding to use idle=1 instead.");
                n_idle = 1;
            }
        } else if (strncmp(token, "concurrency=", 12) == 0) {
            concurrency = xatoui(token + 12);
        } else {
            debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Undefined option: " << token << ".");
            self_destruct();
        }
    }

    /* simple sanity. */

    if (n_startup > n_max) {
        debugs(0, DBG_CRITICAL, "WARNING OVERIDE: Capping startup=" << n_startup << " to the defined maximum (" << n_max <<")");
        n_startup = n_max;
    }

    if (n_idle > n_max) {
        debugs(0, DBG_CRITICAL, "WARNING OVERIDE: Capping idle=" << n_idle << " to the defined maximum (" << n_max <<")");
        n_idle = n_max;
    }
}