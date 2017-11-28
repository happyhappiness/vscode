void
HttpRequest::manager(const CbcPointer<ConnStateData> &aMgr, const AccessLogEntryPointer &al)
{
    clientConnectionManager = aMgr;

    if (!clientConnectionManager.valid())
        return;

    AnyP::PortCfgPointer port = clientConnectionManager->port;
    if (port) {
        myportname = port->name;
        flags.ignoreCc = port->ignore_cc;
    }

    if (auto clientConnection = clientConnectionManager->clientConnection) {
        client_addr = clientConnection->remote; // XXX: remove request->client_addr member.
#if FOLLOW_X_FORWARDED_FOR
        // indirect client gets stored here because it is an HTTP header result (from X-Forwarded-For:)
        // not details about the TCP connection itself
        indirect_client_addr = clientConnection->remote;
#endif /* FOLLOW_X_FORWARDED_FOR */
        my_addr = clientConnection->local;

        flags.intercepted = ((clientConnection->flags & COMM_INTERCEPTION) != 0);
        flags.interceptTproxy = ((clientConnection->flags & COMM_TRANSPARENT) != 0 ) ;
        const bool proxyProtocolPort = port ? port->flags.proxySurrogate : false;
        if (flags.interceptTproxy && !proxyProtocolPort) {
            if (Config.accessList.spoof_client_ip) {
                ACLFilledChecklist *checklist = new ACLFilledChecklist(Config.accessList.spoof_client_ip, this, clientConnection->rfc931);
                checklist->al = al;
                flags.spoofClientIp = checklist->fastCheck().allowed();
                delete checklist;
            } else
                flags.spoofClientIp = true;
        } else
            flags.spoofClientIp = false;
    }
}