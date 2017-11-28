void
Ftp::Server::stopWaitingForOrigin(int originStatus)
{
    Must(waitingForOrigin);
    waitingForOrigin = false;

    if (!isOpen()) // if we are closing, nothing to do
        return;

    // if we have already decided how to respond, respond now
    if (delayedReply) {
        HttpReply::Pointer reply = delayedReply;
        delayedReply = nullptr;
        writeForwardedReply(reply.getRaw());
        return; // do not completeDataDownload() after an earlier response
    }

    if (master->serverState != fssHandleDataRequest)
        return;

    // completeDataDownload() could be waitingForOrigin in fssHandleDataRequest
    // Depending on which side has finished downloading first, either trust
    // master->userDataDone status or set originDataDownloadAbortedOnError:
    if (master->userDataDone) {
        // We finished downloading before Ftp::Client. Most likely, the
        // adaptation shortened the origin response or we hit an error.
        // Our status (stored in master->userDataDone) is more informative.
        // Use master->userDataDone; avoid originDataDownloadAbortedOnError.
        completeDataDownload();
    } else {
        debugs(33, 5, "too early to write the response");
        // Ftp::Client naturally finished downloading before us. Set
        // originDataDownloadAbortedOnError to overwrite future
        // master->userDataDone and relay Ftp::Client error, if there was
        // any, to the user.
        originDataDownloadAbortedOnError = (originStatus >= 400);
    }
}