void
Ftp::Relay::serverComplete()
{
    stopOriginWait(ctrl.replycode);

    CbcPointer<ConnStateData> &mgr = fwd->request->clientConnectionManager;
    if (mgr.valid()) {
        if (Comm::IsConnOpen(ctrl.conn)) {
            debugs(9, 7, "completing FTP server " << ctrl.conn <<
                   " after " << ctrl.replycode);
            fwd->unregister(ctrl.conn);
            if (ctrl.replycode == 221) { // Server sends FTP 221 before closing
                mgr->unpinConnection(false);
                ctrl.close();
            } else {
                CallJobHere1(9, 4, mgr,
                             ConnStateData,
                             notePinnedConnectionBecameIdle,
                             ConnStateData::PinnedIdleContext(ctrl.conn, fwd->request));
                ctrl.forget();
            }
        }
    }
    Ftp::Client::serverComplete();
}