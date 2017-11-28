bool
Security::HandshakeParser::parseCompressionMethods(const SBuf &raw)
{
    if (raw.length() == 0)
        return false;
    Parser::BinaryTokenizer tk(raw);
    while (!tk.atEnd()) {
        // Probably here we should check for DEFLATE(1) compression method
        // which is the only supported by openSSL subsystem.
        if (tk.uint8("compression_method") != 0)
            return true;
    }
    return false;
}