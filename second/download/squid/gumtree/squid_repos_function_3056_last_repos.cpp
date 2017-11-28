void
ConnStateData::sslCrtdHandleReply(const Helper::Reply &reply)
{
    if (!isOpen()) {
        debugs(33, 3, "Connection gone while waiting for ssl_crtd helper reply; helper reply:" << reply);
        return;
    }

    if (reply.result == Helper::BrokenHelper) {
        debugs(33, 5, HERE << "Certificate for " << sslConnectHostOrIp << " cannot be generated. ssl_crtd response: " << reply);
    } else if (!reply.other().hasContent()) {
        debugs(1, DBG_IMPORTANT, HERE << "\"ssl_crtd\" helper returned <NULL> reply.");
    } else {
        Ssl::CrtdMessage reply_message(Ssl::CrtdMessage::REPLY);
        if (reply_message.parse(reply.other().content(), reply.other().contentSize()) != Ssl::CrtdMessage::OK) {
            debugs(33, 5, HERE << "Reply from ssl_crtd for " << sslConnectHostOrIp << " is incorrect");
        } else {
            if (reply.result != Helper::Okay) {
                debugs(33, 5, HERE << "Certificate for " << sslConnectHostOrIp << " cannot be generated. ssl_crtd response: " << reply_message.getBody());
            } else {
                debugs(33, 5, HERE << "Certificate for " << sslConnectHostOrIp << " was successfully recieved from ssl_crtd");
                if (sslServerBump && (sslServerBump->act.step1 == Ssl::bumpPeek || sslServerBump->act.step1 == Ssl::bumpStare)) {
                    doPeekAndSpliceStep();
                    auto ssl = fd_table[clientConnection->fd].ssl.get();
                    bool ret = Ssl::configureSSLUsingPkeyAndCertFromMemory(ssl, reply_message.getBody().c_str(), *port);
                    if (!ret)
                        debugs(33, 5, "Failed to set certificates to ssl object for PeekAndSplice mode");

                    Security::ContextPointer ctx(Security::GetFrom(fd_table[clientConnection->fd].ssl));
                    Ssl::configureUnconfiguredSslContext(ctx, signAlgorithm, *port);
                } else {
                    Security::ContextPointer ctx(Ssl::generateSslContextUsingPkeyAndCertFromMemory(reply_message.getBody().c_str(), *port));
                    getSslContextDone(ctx, true);
                }
                return;
            }
        }
    }
    Security::ContextPointer nil;
    getSslContextDone(nil);
}