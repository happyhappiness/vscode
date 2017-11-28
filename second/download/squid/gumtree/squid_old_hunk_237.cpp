    if (p->options.roundrobin)
        storeAppendPrintf(sentry, " round-robin");

    if (p->options.carp)
        storeAppendPrintf(sentry, " carp");

    if (p->options.userhash)
        storeAppendPrintf(sentry, " userhash");

    if (p->options.sourcehash)
        storeAppendPrintf(sentry, " sourcehash");

    if (p->options.weighted_roundrobin)
        storeAppendPrintf(sentry, " weighted-round-robin");
