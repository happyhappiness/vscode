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

    if (n_tries > 10)
        return false;

    if (origin_tries > 2)
        return false;

    if (squid_curtime - start_t > Config.Timeout.forward)
        return false;

    if (flags.dont_retry)
        return false;

    if (!checkRetriable())
        return false;

    if (request->bodyNibbled())
        return false;

    return true;
}