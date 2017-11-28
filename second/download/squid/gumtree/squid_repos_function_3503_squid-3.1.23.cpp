void
ConnStateData::sslCrtdHandleReply(const char * reply)
{
    if (!reply) {
        debugs(1, 1, HERE << "\"ssl_crtd\" helper return <NULL> reply");
    } else {
        Ssl::CrtdMessage reply_message;
        if (reply_message.parse(reply, strlen(reply)) != Ssl::CrtdMessage::OK) {
            debugs(33, 5, HERE << "Reply from ssl_crtd for " << sslHostName << " is incorrect");
        } else {
            if (reply_message.getCode() != "OK") {
                debugs(33, 5, HERE << "Certificate for " << sslHostName << " cannot be generated. ssl_crtd response: " << reply_message.getBody());
            } else {
                debugs(33, 5, HERE << "Certificate for " << sslHostName << " was successfully recieved from ssl_crtd");
                getSslContextDone(Ssl::generateSslContextUsingPkeyAndCertFromMemory(reply_message.getBody().c_str()), true);
                return;
            }
        }
    }
    getSslContextDone(NULL);
}