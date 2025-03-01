static void
idnsReadVCHeader(const Comm::ConnectionPointer &conn, char *buf, size_t len, Comm::Flag flag, int, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (flag == Comm::ERR_CLOSING)
        return;

    if (flag != Comm::OK || len <= 0) {
        if (Comm::IsConnOpen(conn))
            conn->close();
        return;
    }

    vc->read_msglen += len;

    assert(vc->read_msglen <= 2);

    if (vc->read_msglen < 2) {
        AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVCHeader",
                                             CommIoCbPtrFun(idnsReadVCHeader, vc));
        comm_read(conn, buf+len, 2 - vc->read_msglen, call);
        return;
    }

    vc->read_msglen = 0;

    vc->msglen = ntohs(vc->msglen);

    if (!vc->msglen) {
        if (Comm::IsConnOpen(conn))
            conn->close();
        return;
    }

    vc->msg->init(vc->msglen, vc->msglen);
    AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVC",
                                         CommIoCbPtrFun(idnsReadVC, vc));
    comm_read(conn, vc->msg->buf, vc->msglen, call);
}