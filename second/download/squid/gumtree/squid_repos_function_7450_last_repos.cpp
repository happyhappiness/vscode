void
Security::HandshakeParser::parseClientHelloHandshakeMessage(const SBuf &raw)
{
    Parser::BinaryTokenizer tk(raw);
    Parser::BinaryTokenizerContext hello(tk, "ClientHello");
    details->tlsSupportedVersion = ParseProtocolVersion(tk);
    details->clientRandom = tk.area(HelloRandomSize, ".random");
    details->sessionId = tk.pstring8(".session_id");
    parseCiphers(tk.pstring16(".cipher_suites"));
    details->compressionSupported = parseCompressionMethods(tk.pstring8(".compression_methods"));
    if (!tk.atEnd()) // extension-free message ends here
        parseExtensions(tk.pstring16(".extensions"));
    hello.success();
}