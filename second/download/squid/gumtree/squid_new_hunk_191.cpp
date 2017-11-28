 *	including canceling close handlers
 */
void
FtpStateData::abortTransaction(const char *reason)
{
    debugs(9, 3, HERE << "aborting transaction for " << reason <<
           "; FD " << (ctrl.conn!=NULL?ctrl.conn->fd:-1) << ", Data FD " << (data.conn!=NULL?data.conn->fd:-1) << ", this " << this);
    if (Comm::IsConnOpen(ctrl.conn)) {
        ctrl.conn->close();
        return;
    }

    fwd->handleUnregisteredServerEnd();
    mustStop("FtpStateData::abortTransaction");
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
FtpChannel::opened(const Comm::ConnectionPointer &newConn, const AsyncCall::Pointer &aCloser)
{
    assert(!Comm::IsConnOpen(conn));
    assert(closer == NULL);

    assert(Comm::IsConnOpen(newConn));
    assert(aCloser != NULL);

    conn = newConn;
    closer = aCloser;
    comm_add_close_handler(conn->fd, closer);
}

/// planned close: removes the close handler and calls comm_close
void
FtpChannel::close()
{
    // channels with active listeners will be closed when the listener handler dies.
    if (Comm::IsConnOpen(conn)) {
        comm_remove_close_handler(conn->fd, closer);
        conn->close(); // we do not expect to be called back
    }
    clear();
}

void
FtpChannel::clear()
{
    conn = NULL;
    closer = NULL;
}
