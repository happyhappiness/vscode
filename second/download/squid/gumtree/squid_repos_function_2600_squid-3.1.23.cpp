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