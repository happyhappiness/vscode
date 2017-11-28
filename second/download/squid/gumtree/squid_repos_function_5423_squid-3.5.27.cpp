bool
Ftp::Relay::abortOnData(const char *reason)
{
    debugs(9, 3, "aborting transaction for " << reason <<
           "; FD " << (ctrl.conn != NULL ? ctrl.conn->fd : -1) << ", Data FD " << (data.conn != NULL ? data.conn->fd : -1) << ", this " << this);
    // this method is only called to handle data connection problems
    // the control connection should keep going

#if USE_ADAPTATION
    if (adaptedBodySource != NULL)
        stopConsumingFrom(adaptedBodySource);
#endif

    if (Comm::IsConnOpen(data.conn))
        dataComplete();

    return !Comm::IsConnOpen(ctrl.conn);
}