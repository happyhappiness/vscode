
    ACLFilledChecklist ch(Config.accessList.proxyProtocol, NULL, clientConnection->rfc931);
    ch.src_addr = clientConnection->remote;
    ch.my_addr = clientConnection->local;
    ch.conn(this);

    if (!ch.fastCheck().allowed())
        return proxyProtocolError("PROXY client not permitted by ACLs");

    return true;
}

/**
