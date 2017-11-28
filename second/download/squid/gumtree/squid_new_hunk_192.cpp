    if (!helperStartStats(sentry, hlp, label))
        return;

    storeAppendPrintf(sentry, "program: %s\n",
                      hlp->cmdline->key);
    storeAppendPrintf(sentry, "number active: %d of %d (%d shutting down)\n",
                      hlp->childs.n_active, hlp->childs.n_max, (hlp->childs.n_running - hlp->childs.n_active) );
    storeAppendPrintf(sentry, "requests sent: %d\n",
                      hlp->stats.requests);
    storeAppendPrintf(sentry, "replies received: %d\n",
                      hlp->stats.replies);
    storeAppendPrintf(sentry, "queue length: %d\n",
                      hlp->stats.queue_size);
