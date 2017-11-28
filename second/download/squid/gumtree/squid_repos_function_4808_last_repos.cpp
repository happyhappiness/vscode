uint32_t
Parser::BinaryTokenizer::uint24(const char *description)
{
    want(3, description);
    const uint32_t result = (octet() << 16) | (octet() << 8) | octet();
    got(result, 3, description);
    return result;
}