static void
fwdPeerSelectionCompleteWrapper(Comm::ConnectionList * unused, ErrorState *err, void *data)
{
    FwdState *fwd = (FwdState *) data;
    if (err)
        fwd->fail(err);
    fwd->startConnectionOrFail();
}