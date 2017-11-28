void
HttpStateData::abortTransaction(const char *reason)
{
    debugs(11,5, HERE << "aborting transaction for " << reason <<
           "; FD " << fd << ", this " << this);

    if (fd >= 0) {
        comm_close(fd);
        return;
    }

    fwd->handleUnregisteredServerEnd();
    deleteThis("HttpStateData::abortTransaction");
}