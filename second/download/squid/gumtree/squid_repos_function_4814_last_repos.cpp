SBuf
Parser::BinaryTokenizer::pstring24(const char *description)
{
    BinaryTokenizerContext pstring(*this, description);
    if (const uint32_t length = uint24(".length"))
        return area(length, ".octets");
    return SBuf();
}