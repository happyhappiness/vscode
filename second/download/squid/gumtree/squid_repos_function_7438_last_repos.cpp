static AnyP::ProtocolVersion
ParseProtocolVersion(Parser::BinaryTokenizer &tk)
{
    Parser::BinaryTokenizerContext context(tk, ".version");
    uint8_t vMajor = tk.uint8(".major");
    uint8_t vMinor = tk.uint8(".minor");
    if (vMajor == 0 && vMinor == 2)
        return AnyP::ProtocolVersion(AnyP::PROTO_SSL, 2, 0);

    Must(vMajor == 3);
    if (vMinor == 0)
        return AnyP::ProtocolVersion(AnyP::PROTO_SSL, 3, 0);

    return AnyP::ProtocolVersion(AnyP::PROTO_TLS, 1, (vMinor - 1));
}