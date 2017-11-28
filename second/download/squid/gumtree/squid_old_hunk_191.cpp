 *	including canceling close handlers
 */
void
FtpStateData::abortTransaction(const char *reason)
{
    debugs(9, 3, HERE << "aborting transaction for " << reason <<
           "; FD " << ctrl.fd << ", Data FD " << data.fd << ", this " << this);
    if (ctrl.fd >= 0) {
        comm_close(ctrl.fd);
        return;
    }

    fwd->handleUnregisteredServerEnd();
    deleteThis("FtpStateData::abortTransaction");
}

/// creates a data channel Comm close callback
AsyncCall::Pointer
FtpStateData::dataCloser()
{
    typedef CommCbMemFunT<FtpStateData, CommCloseCbParams> Dialer;
    return JobCallback(9, 5, Dialer, this, FtpStateData::dataClosed);
}

/// configures the channel with a descriptor and registers a close handler
void
FtpChannel::opened(int aFd, const AsyncCall::Pointer &aCloser)
{
    assert(fd < 0);
    assert(closer == NULL);

    assert(aFd >= 0);
    assert(aCloser != NULL);

    fd = aFd;
    closer = aCloser;
    comm_add_close_handler(fd, closer);
}

/// planned close: removes the close handler and calls comm_close
void
FtpChannel::close()
{
    if (fd >= 0) {
        comm_remove_close_handler(fd, closer);
        closer = NULL;
        comm_close(fd); // we do not expect to be called back
        fd = -1;
    }
}

/// just resets fd and close handler
void
FtpChannel::clear()
{
    fd = -1;
    closer = NULL;
}
