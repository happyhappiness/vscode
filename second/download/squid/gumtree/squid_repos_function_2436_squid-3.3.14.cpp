void
FwdState::fail(ErrorState * errorState)
{
    debugs(17, 3, HERE << err_type_str[errorState->type] << " \"" << httpStatusString(errorState->httpStatus) << "\"\n\t" << entry->url()  );

    delete err;
    err = errorState;

    if (!errorState->request)
        errorState->request = HTTPMSGLOCK(request);

    if (err->type != ERR_ZERO_SIZE_OBJECT)
        return;

    if (pconnRace == racePossible) {
        debugs(17, 5, HERE << "pconn race happened");
        pconnRace = raceHappened;
    }

    if (ConnStateData *pinned_connection = request->pinnedConnection()) {
        pinned_connection->pinning.zeroReply = true;
        flags.dont_retry = true; // we want to propagate failure to the client
        debugs(17, 4, "zero reply on pinned connection");
    }
}