void
ServerStateData::handleAdaptationAborted(bool bypassable)
{
    debugs(11,5, HERE << "handleAdaptationAborted; bypassable: " << bypassable <<
           ", entry empty: " << entry->isEmpty());

    if (abortOnBadEntry("entry went bad while ICAP aborted"))
        return;

    // TODO: bypass if possible

    if (entry->isEmpty()) {
        debugs(11,9, HERE << "creating ICAP error entry after ICAP failure");
        ErrorState *err = errorCon(ERR_ICAP_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
        err->xerrno = errno;
        fwd->fail(err);
        fwd->dontRetry(true);
    }

    abortTransaction("ICAP failure");
}