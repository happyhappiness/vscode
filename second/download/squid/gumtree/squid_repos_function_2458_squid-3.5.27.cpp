static void
idnsInitVCConnected(const Comm::ConnectionPointer &conn, Comm::Flag status, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (status != Comm::OK || !conn) {
        char buf[MAX_IPSTRLEN] = "";
        if (vc->ns < nns)
            nameservers[vc->ns].S.toStr(buf,MAX_IPSTRLEN);
        debugs(78, DBG_IMPORTANT, HERE << "Failed to connect to nameserver " << buf << " using TCP.");
        return;
    }

    vc->conn = conn;

    comm_add_close_handler(conn->fd, idnsVCClosed, vc);
    AsyncCall::Pointer call = commCbCall(5,4, "idnsReadVCHeader",
                                         CommIoCbPtrFun(idnsReadVCHeader, vc));
    comm_read(conn, (char *)&vc->msglen, 2, call);
    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}