bool
Ftp::Server::handleUploadRequest(String &, String &)
{
    if (!checkDataConnPre())
        return false;

    if (Config.accessList.forceRequestBodyContinuation) {
        ClientHttpRequest *http = pipeline.front()->http;
        HttpRequest *request = http->request;
        ACLFilledChecklist bodyContinuationCheck(Config.accessList.forceRequestBodyContinuation, request, NULL);
        if (bodyContinuationCheck.fastCheck().allowed()) {
            request->forcedBodyContinuation = true;
            if (checkDataConnPost()) {
                // Write control Msg
                writeEarlyReply(150, "Data connection opened");
                maybeReadUploadData();
            } else {
                // wait for acceptDataConnection but tell it to call wroteEarlyReply
                // after writing "150 Data connection opened"
                typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
                AsyncCall::Pointer call = JobCallback(33, 5, Dialer, this, Ftp::Server::wroteEarlyReply);
                onDataAcceptCall = call;
            }
        }
    }

    changeState(fssHandleUploadRequest, "handleDataRequest");

    return true;
}