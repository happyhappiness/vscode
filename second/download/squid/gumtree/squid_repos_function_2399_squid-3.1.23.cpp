static void
fwdStartCompleteWrapper(FwdServer * servers, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->startComplete(servers);
}