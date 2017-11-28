void
Ftp::Relay::readPasvReply()
{
    assert(serverState() == fssHandlePasv || serverState() == fssHandleEpsv || serverState() == fssHandlePort || serverState() == fssHandleEprt);

    if (100 <= ctrl.replycode && ctrl.replycode < 200)
        return; // ignore preliminary replies

    if (handlePasvReply(updateMaster().clientDataAddr))
        forwardReply();
    else
        forwardError();
}