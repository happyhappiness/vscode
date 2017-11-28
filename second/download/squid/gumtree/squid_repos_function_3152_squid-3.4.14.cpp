void
CommIoCbPtrFun::dial()
{
    handler(params.conn, params.buf, params.size, params.flag, params.xerrno, params.data);
}