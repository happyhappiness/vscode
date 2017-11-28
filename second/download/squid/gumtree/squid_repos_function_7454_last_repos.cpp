void
Security::HandshakeParser::parseV23Ciphers(const SBuf &raw)
{
    Parser::BinaryTokenizer tk(raw);
    while (!tk.atEnd()) {
        // RFC 6101 Appendix E, RFC 5246 Appendix E2
        // Unlike TLS, ciphers in SSLv23 Hellos are 3 bytes long and come in
        // two versions: v2 and v3. The two versions may co-exist in a single
        // SSLv23 Hello. Only v3 ciphers have a first byte value of zero.
        // The ciphers are needed for our peeking/staring code that
        // does not support SSLv2, so we ignore v2 ciphers.
        const uint8_t prefix = tk.uint8("prefix");
        const uint16_t cipher = tk.uint16("cipher");
        if (prefix == 0)
            details->ciphers.insert(cipher);
    }
}