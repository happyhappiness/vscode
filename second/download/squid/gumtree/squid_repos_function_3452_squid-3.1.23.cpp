void
ConnStateData::readNextRequest()
{
    debugs(33, 5, "ConnStateData::readNextRequest: FD " << fd << " reading next req");

    fd_note(fd, "Waiting for next request");
    /**
     * Set the timeout BEFORE calling clientReadRequest().
     */
    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(33, 5,
                                     TimeoutDialer, this, ConnStateData::requestTimeout);
    commSetTimeout(fd, Config.Timeout.persistent_request, timeoutCall);

    readSomeData();
    /** Please don't do anything with the FD past here! */
}