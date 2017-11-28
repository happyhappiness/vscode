void
Ftp::Client::abortAll(const char *reason)
{
    debugs(9, 3, "aborting transaction for " << reason <<
           "; FD " << (ctrl.conn!=NULL?ctrl.conn->fd:-1) << ", Data FD " << (data.conn!=NULL?data.conn->fd:-1) << ", this " << this);
    mustStop(reason);
}