void Ftp::Server::userDataCompletionCheckpoint(int finalStatusCode)
{
    Must(!master->userDataDone);
    master->userDataDone = finalStatusCode;

    if (in.bodyParser)
        finishDechunkingRequest(false);

    if (waitingForOrigin) {
        // The completeDataDownload() is not called here unconditionally
        // because we want to signal the FTP user that we are not fully
        // done processing its data stream, even though all data bytes
        // have been sent or received already.
        debugs(33, 5, "Transfering from FTP server is not complete");
        return;
    }

    // Adjust our reply if the server aborted with an error before we are done.
    if (master->userDataDone == 226 && originDataDownloadAbortedOnError) {
        debugs(33, 5, "Transfering from FTP server terminated with an error, adjust status code");
        master->userDataDone = 451;
    }
    completeDataDownload();
}