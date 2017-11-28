static void
fwdConnectStartWrapper(void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->connectStart();
}