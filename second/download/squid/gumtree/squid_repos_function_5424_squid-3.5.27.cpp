void
Ftp::Relay::stopOriginWait(int code)
{
    if (originWaitInProgress) {
        CbcPointer<ConnStateData> &mgr = fwd->request->clientConnectionManager;
        if (mgr.valid()) {
            if (Ftp::Server *srv = dynamic_cast<Ftp::Server*>(mgr.get())) {
                typedef UnaryMemFunT<Ftp::Server, int> CbDialer;
                AsyncCall::Pointer call = asyncCall(11, 3, "Ftp::Server::stopWaitingForOrigin",
                                                    CbDialer(srv, &Ftp::Server::stopWaitingForOrigin, code));
                ScheduleCallHere(call);
            }
        }
        originWaitInProgress = false;
    }
}