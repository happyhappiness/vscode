void
HttpStateData::doneSendingRequestBody()
{
    debugs(11,5, HERE << "doneSendingRequestBody: FD " << fd);

#if HTTP_VIOLATIONS
    if (Config.accessList.brokenPosts) {
        ACLFilledChecklist ch(Config.accessList.brokenPosts, originalRequest(), NULL);
        if (!ch.fastCheck()) {
            debugs(11, 5, "doneSendingRequestBody: didn't match brokenPosts");
            CommIoCbParams io(NULL);
            io.fd=fd;
            io.flag=COMM_OK;
            sendComplete(io);
        } else {
            debugs(11, 2, "doneSendingRequestBody: matched brokenPosts");

            if (!canSend(fd)) {
                debugs(11,2, HERE << "cannot send CRLF to closing FD " << fd);
                assert(closeHandler != NULL);
                return;
            }

            typedef CommCbMemFunT<HttpStateData, CommIoCbParams> Dialer;
            AsyncCall::Pointer call = JobCallback(11,5,
                                                  Dialer, this, HttpStateData::sendComplete);
            comm_write(fd, "\r\n", 2, call);
        }
        return;
    }
    debugs(11, 5, "doneSendingRequestBody: No brokenPosts list");
#endif /* HTTP_VIOLATIONS */

    CommIoCbParams io(NULL);
    io.fd=fd;
    io.flag=COMM_OK;
    sendComplete(io);
}