static void
idnsReadVC(const Comm::ConnectionPointer &conn, char *buf, size_t len, Comm::Flag flag, int, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == Comm::ERR_CLOSING)
        return;

    if (flag != Comm::OK || len <= 0) {
        if (Comm::IsConnOpen(conn))
            conn->close();
        return;
    }

    vc->msg->size += len;       // XXX should not access -> size directly

    if (vc->msg->contentSize() < vc->msglen) {
        AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVC",
                                             CommIoCbPtrFun(idnsReadVC, vc));
        comm_read(conn, buf+len, vc->msglen - vc->msg->contentSize(), call);
        return;
    }

    assert(vc->ns < nns);
    debugs(78, 3, HERE << conn << ": received " << vc->msg->contentSize() << " bytes via TCP from " << nameservers[vc->ns].S << ".");

    idnsGrokReply(vc->msg->buf, vc->msg->contentSize(), vc->ns);
    vc->msg->clean();
    AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVCHeader",
                                         CommIoCbPtrFun(idnsReadVCHeader, vc));
    comm_read(conn, (char *)&vc->msglen, 2, call);
}