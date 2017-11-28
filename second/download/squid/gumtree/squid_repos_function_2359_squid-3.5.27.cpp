void
FwdState::retryOrBail()
{
    if (checkRetry()) {
        debugs(17, 3, HERE << "re-forwarding (" << n_tries << " tries, " << (squid_curtime - start_t) << " secs)");
        // we should retry the same destination if it failed due to pconn race
        if (pconnRace == raceHappened)
            debugs(17, 4, HERE << "retrying the same destination");
        else
            serverDestinations.erase(serverDestinations.begin()); // last one failed. try another.
        startConnectionOrFail();
        return;
    }

    // TODO: should we call completed() here and move doneWithRetries there?
    doneWithRetries();

    request->hier.stopPeerClock(false);

    if (self != NULL && !err && shutting_down && entry->isEmpty()) {
        ErrorState *anErr = new ErrorState(ERR_SHUTTING_DOWN, Http::scServiceUnavailable, request);
        errorAppendEntry(entry, anErr);
    }

    self = NULL;    // refcounted
}