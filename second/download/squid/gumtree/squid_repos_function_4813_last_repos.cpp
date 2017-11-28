SBuf
Parser::BinaryTokenizer::pstring16(const char *description)
{
    BinaryTokenizerContext pstring(*this, description);
    if (const uint16_t length = uint16(".length"))
        return area(length, ".octets");
    return SBuf();
}