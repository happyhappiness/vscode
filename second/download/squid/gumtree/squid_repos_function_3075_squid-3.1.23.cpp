void
CommConnectCbPtrFun::dial()
{
    handler(params.fd, params.dns, params.flag, params.xerrno, params.data);
}