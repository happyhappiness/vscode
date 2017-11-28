void
FwdState::abort(void* d)
{
    FwdState* fwd = (FwdState*)d;
    Pointer tmp = fwd; // Grab a temporary pointer to keep the object alive during our scope.

    if (Comm::IsConnOpen(fwd->serverConnection())) {
        fwd->closeServerConnection("store entry aborted");
    } else {
        debugs(17, 7, HERE << "store entry aborted; no connection to close");
    }
    fwd->serverDestinations.clear();
    fwd->self = NULL;
}