void
ConnStateData::sslCrtdHandleReply(const HelperReply &reply)
{
    if (reply.result == HelperReply::BrokenHelper) {
        debugs(33, 5, HERE << "Certificate for " << sslConnectHostOrIp << " cannot be generated. ssl_crtd response: " << reply);
    } else if (!reply.other().hasContent()) {
        debugs(1, DBG_IMPORTANT, HERE << "\"ssl_crtd\" helper returned <NULL> reply.");
    } else {
        Ssl::CrtdMessage reply_message(Ssl::CrtdMessage::REPLY);
        if (reply_message.parse(reply.other().content(), reply.other().contentSize()) != Ssl::CrtdMessage::OK) {
            debugs(33, 5, HERE << "Reply from ssl_crtd for " << sslConnectHostOrIp << " is incorrect");
        } else {
            if (reply.result != HelperReply::Okay) {
                debugs(33, 5, HERE << "Certificate for " << sslConnectHostOrIp << " cannot be generated. ssl_crtd response: " << reply_message.getBody());
            } else {
                debugs(33, 5, HERE << "Certificate for " << sslConnectHostOrIp << " was successfully recieved from ssl_crtd");
                SSL_CTX *ctx = Ssl::generateSslContextUsingPkeyAndCertFromMemory(reply_message.getBody().c_str(), *port);
                getSslContextDone(ctx, true);
                return;
            }
        }
    }
    getSslContextDone(NULL);
}