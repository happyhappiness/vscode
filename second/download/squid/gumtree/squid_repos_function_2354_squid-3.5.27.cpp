static void
fwdServerClosedWrapper(const CommCloseCbParams &params)
{
    FwdState *fwd = (FwdState *)params.data;
    fwd->serverClosed(params.fd);
}