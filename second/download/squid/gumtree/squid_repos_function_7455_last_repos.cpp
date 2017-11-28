void
Security::HandshakeParser::parseServerHelloHandshakeMessage(const SBuf &raw)
{
    Parser::BinaryTokenizer tk(raw);
    Parser::BinaryTokenizerContext hello(tk, "ServerHello");
    details->tlsSupportedVersion = ParseProtocolVersion(tk);
    tk.skip(HelloRandomSize, ".random");
    details->sessionId = tk.pstring8(".session_id");
    details->ciphers.insert(tk.uint16(".cipher_suite"));
    details->compressionSupported = tk.uint8(".compression_method") != 0; // not null
    if (!tk.atEnd()) // extensions present
        parseExtensions(tk.pstring16(".extensions"));
    hello.success();
}