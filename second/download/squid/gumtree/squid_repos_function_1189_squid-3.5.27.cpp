static AnyP::ProtocolVersion
parsePortProtocol(const SBuf &value)
{
    // HTTP/1.0 not supported because we are version 1.1 which contains a superset of 1.0
    // and RFC 2616 requires us to upgrade 1.0 to 1.1
    if (value.cmp("HTTP") == 0 || value.cmp("HTTP/1.1") == 0)
        return AnyP::ProtocolVersion(AnyP::PROTO_HTTP, 1,1);

    if (value.cmp("HTTPS") == 0 || value.cmp("HTTPS/1.1") == 0)
        return AnyP::ProtocolVersion(AnyP::PROTO_HTTPS, 1,1);

    if (value.cmp("FTP") == 0)
        return Ftp::ProtocolVersion();

    fatalf("%s directive does not support protocol=" SQUIDSBUFPH "\n", cfg_directive, SQUIDSBUFPRINT(value));
    return AnyP::ProtocolVersion(); // not reached
}