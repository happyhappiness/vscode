void
Security::HandshakeParser::parseVersion2HandshakeMessage(const SBuf &raw)
{
    Parser::BinaryTokenizer tk(raw);
    Parser::BinaryTokenizerContext hello(tk, "V2ClientHello");
    Must(tk.uint8(".type") == hskClientHello); // Only client hello supported.
    details->tlsSupportedVersion = ParseProtocolVersion(tk);
    const uint16_t ciphersLen = tk.uint16(".cipher_specs.length");
    const uint16_t sessionIdLen = tk.uint16(".session_id.length");
    const uint16_t challengeLen = tk.uint16(".challenge.length");
    parseV23Ciphers(tk.area(ciphersLen, ".cipher_specs.body"));
    details->sessionId = tk.area(sessionIdLen, ".session_id.body");
    tk.skip(challengeLen, ".challenge.body");
    hello.success();
}