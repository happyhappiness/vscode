void
Ftp::StartListening()
{
    for (AnyP::PortCfgPointer s = FtpPortList; s != NULL; s = s->next) {
        if (MAXTCPLISTENPORTS == NHttpSockets) {
            debugs(1, DBG_IMPORTANT, "Ignoring ftp_port lines exceeding the" <<
                   " limit of " << MAXTCPLISTENPORTS << " ports.");
            break;
        }

        // direct new connections accepted by listenConn to Accept()
        typedef CommCbFunPtrCallT<CommAcceptCbPtrFun> AcceptCall;
        RefCount<AcceptCall> subCall = commCbCall(5, 5, "Ftp::Server::AcceptCtrlConnection",
                                       CommAcceptCbPtrFun(Ftp::Server::AcceptCtrlConnection,
                                               CommAcceptCbParams(NULL)));
        clientStartListeningOn(s, subCall, Ipc::fdnFtpSocket);
    }
}