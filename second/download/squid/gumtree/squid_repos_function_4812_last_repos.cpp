SBuf
Parser::BinaryTokenizer::pstring8(const char *description)
{
    BinaryTokenizerContext pstring(*this, description);
    if (const uint8_t length = uint8(".length"))
        return area(length, ".octets");
    return SBuf();
}