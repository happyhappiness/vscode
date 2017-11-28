void
FwdState::startConnectionOrFail()
{
    debugs(17, 3, HERE << entry->url());

    if (serverDestinations.size() > 0) {
        // Ditch error page if it was created before.
        // A new one will be created if there's another problem
        delete err;
        err = NULL;

        // Update the logging information about this new server connection.
        // Done here before anything else so the errors get logged for
        // this server link regardless of what happens when connecting to it.
        // IF sucessfuly connected this top destination will become the serverConnection().
        request->hier.note(serverDestinations[0], request->GetHost());
        request->clearError();

        connectStart();
    } else {
        debugs(17, 3, HERE << "Connection failed: " << entry->url());
        if (!err) {
            ErrorState *anErr = new ErrorState(ERR_CANNOT_FORWARD, Http::scInternalServerError, request);
            fail(anErr);
        } // else use actual error from last connection attempt
        self = NULL;       // refcounted
    }
}