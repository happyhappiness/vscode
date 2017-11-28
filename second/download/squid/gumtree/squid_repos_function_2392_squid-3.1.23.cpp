void
FwdState::abort(void* d)
{
    FwdState* fwd = (FwdState*)d;
    Pointer tmp = fwd; // Grab a temporary pointer to keep the object alive during our scope.

    if (fwd->server_fd >= 0) {
        comm_close(fwd->server_fd);
        fwd->server_fd = -1;
    }

    fwd->self = NULL;
}