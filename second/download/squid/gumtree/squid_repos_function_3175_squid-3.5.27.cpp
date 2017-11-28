void
CommConnectCbPtrFun::dial()
{
    handler(params.conn, params.flag, params.xerrno, params.data);
}