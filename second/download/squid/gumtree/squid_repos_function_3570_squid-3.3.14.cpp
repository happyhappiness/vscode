void
ConnStateData::sslCrtdHandleReply(const char * reply)
{
    if (!reply) {
        debugs(1, DBG_IMPORTANT, HERE << "\"ssl_crtd\" helper return <NULL> reply");
    } else {
        Ssl::CrtdMessage reply_message;
        if (reply_message.parse(reply, strlen(reply)) != Ssl::CrtdMessage::OK) {
            debugs(33, 5, HERE << "Reply from ssl_crtd for " << sslConnectHostOrIp << " is incorrect");
        } else {
            if (reply_message.getCode() != "OK") {
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