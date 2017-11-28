void
CommAcceptCbPtrFun::dial()
{
    handler(params.fd, params.nfd, &params.details, params.flag, params.xerrno, params.data);
}