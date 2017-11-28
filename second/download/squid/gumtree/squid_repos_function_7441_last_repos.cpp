bool
Security::HandshakeParser::isSslv2Record(const SBuf &raw) const
{
    Parser::BinaryTokenizer tk(raw, true);
    const uint16_t head = tk.uint16("?v2Hello.msg_head");
    const uint8_t type = tk.uint8("?v2Hello.msg_type");
    const uint16_t length = head & 0x7FFF;
    return (head & 0x8000) && length && type == 1;
}