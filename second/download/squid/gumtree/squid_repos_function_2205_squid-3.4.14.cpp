void
FwdState::abort(void* d)
{
    FwdState* fwd = (FwdState*)d;
    Pointer tmp = fwd; // Grab a temporary pointer to keep the object alive during our scope.

    if (Comm::IsConnOpen(fwd->serverConnection())) {
        comm_remove_close_handler(fwd->serverConnection()->fd, fwdServerClosedWrapper, fwd);
        debugs(17, 3, HERE << "store entry aborted; closing " <<
               fwd->serverConnection());
        fwd->serverConnection()->close();
    } else {
        debugs(17, 7, HERE << "store entry aborted; no connection to close");
    }
    fwd->serverDestinations.clean();
    fwd->self = NULL;
}