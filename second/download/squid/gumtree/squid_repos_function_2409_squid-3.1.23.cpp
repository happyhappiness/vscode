void
FwdState::retryOrBail()
{
    if (checkRetry()) {
        int originserver = (servers->_peer == NULL);
        debugs(17, 3, "fwdServerClosed: re-forwarding (" << n_tries << " tries, " << (squid_curtime - start_t) << " secs)");

        if (servers->next) {
            /* use next, or cycle if origin server isn't last */
            FwdServer *fs = servers;
            FwdServer **T, *T2 = NULL;
            servers = fs->next;

            for (T = &servers; *T; T2 = *T, T = &(*T)->next);
            if (T2 && T2->_peer) {
                /* cycle */
                *T = fs;
                fs->next = NULL;
            } else {
                /* Use next. The last "direct" entry is retried multiple times */
                servers = fs->next;
                fwdServerFree(fs);
                originserver = 0;
            }
        }

        /* Ditch error page if it was created before.
         * A new one will be created if there's another problem */
        if (err) {
            errorStateFree(err);
            err = NULL;
        }

        /* use eventAdd to break potential call sequence loops and to slow things down a little */
        eventAdd("fwdConnectStart", fwdConnectStartWrapper, this, originserver ? 0.05 : 0.005, 0);

        return;
    }

    // TODO: should we call completed() here and move doneWithRetries there?
    doneWithRetries();

    if (self != NULL && !err && shutting_down) {
        errorCon(ERR_SHUTTING_DOWN, HTTP_SERVICE_UNAVAILABLE, request);
    }

    self = NULL;	// refcounted
}