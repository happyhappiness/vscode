bool
FwdState::checkRetry()
{
    if (shutting_down)
        return false;

    if (!self) { // we have aborted before the server called us back
        debugs(17, 5, HERE << "not retrying because of earlier abort");
        // we will be destroyed when the server clears its Pointer to us
        return false;
    }

    if (entry->store_status != STORE_PENDING)
        return false;

    if (!entry->isEmpty())
        return false;

    if (n_tries > Config.forward_max_tries)
        return false;

    if (!EnoughTimeToReForward(start_t))
        return false;

    if (flags.dont_retry)
        return false;

    if (request->bodyNibbled())
        return false;

    // NP: not yet actually connected anywhere. retry is safe.
    if (!flags.connected_okay)
        return true;

    if (!checkRetriable())
        return false;

    return true;
}