void
Security::HandshakeParser::parseVersion2Record()
{
    const Sslv2Record record(tkRecords);
    tkRecords.commit();
    details->tlsVersion = AnyP::ProtocolVersion(AnyP::PROTO_SSL, 2, 0);
    parseVersion2HandshakeMessage(record.fragment);
    state = atHelloReceived;
    done = "SSLv2";
}