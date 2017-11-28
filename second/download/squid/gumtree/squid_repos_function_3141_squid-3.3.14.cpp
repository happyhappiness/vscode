void
errorSend(const Comm::ConnectionPointer &conn, ErrorState * err)
{
    HttpReply *rep;
    debugs(4, 3, HERE << conn << ", err=" << err);
    assert(Comm::IsConnOpen(conn));

    /* moved in front of errorBuildBuf @?@ */
    err->flags.flag_cbdata = 1;

    rep = err->BuildHttpReply();

    MemBuf *mb = rep->pack();
    AsyncCall::Pointer call = commCbCall(78, 5, "errorSendComplete",
                                         CommIoCbPtrFun(&errorSendComplete, err));
    Comm::Write(conn, mb, call);
    delete mb;

    delete rep;
}