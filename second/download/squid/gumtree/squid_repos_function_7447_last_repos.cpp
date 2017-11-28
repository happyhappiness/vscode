void
Security::HandshakeParser::parseHandshakeMessage()
{
    Must(currentContentType == ContentType::ctHandshake);

    const Handshake message(tkMessages);

    switch (message.msg_type) {
    case HandshakeType::hskClientHello:
        Must(state < atHelloReceived);
        Security::HandshakeParser::parseClientHelloHandshakeMessage(message.msg_body);
        state = atHelloReceived;
        done = "ClientHello";
        return;
    case HandshakeType::hskServerHello:
        Must(state < atHelloReceived);
        parseServerHelloHandshakeMessage(message.msg_body);
        state = atHelloReceived;
        return;
    case HandshakeType::hskCertificate:
        Must(state < atCertificatesReceived);
        parseServerCertificates(message.msg_body);
        state = atCertificatesReceived;
        return;
    case HandshakeType::hskServerHelloDone:
        Must(state < atHelloDoneReceived);
        // zero-length
        state = atHelloDoneReceived;
        done = "ServerHelloDone";
        return;
    }
    debugs(83, 5, "ignoring " << message.msg_body.length() << "-byte type-" <<
           static_cast<unsigned int>(message.msg_type) << " handshake message");
}