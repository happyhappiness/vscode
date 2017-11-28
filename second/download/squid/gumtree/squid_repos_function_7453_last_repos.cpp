void
Security::HandshakeParser::parseCiphers(const SBuf &raw)
{
    details->ciphers.reserve(raw.length() / sizeof(uint16_t));
    Parser::BinaryTokenizer tk(raw);
    while (!tk.atEnd()) {
        const uint16_t cipher = tk.uint16("cipher");
        details->ciphers.insert(cipher);
    }
}