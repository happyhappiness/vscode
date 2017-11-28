void
CommIoCbPtrFun::dial()
{
    handler(params.fd, params.buf, params.size, params.flag, params.xerrno, params.data);
}