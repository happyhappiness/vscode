    // Generic independent options

    if (s->name)
        storeAppendPrintf(e, " name=%s", s->name);

#if USE_HTTP_VIOLATIONS
    if (!s->accel && s->ignore_cc)
        storeAppendPrintf(e, " ignore-cc");
#endif

    if (s->connection_auth_disabled)
        storeAppendPrintf(e, " connection-auth=off");
    else
