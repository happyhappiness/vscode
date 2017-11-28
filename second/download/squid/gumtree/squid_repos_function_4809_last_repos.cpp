uint32_t
Parser::BinaryTokenizer::uint32(const char *description)
{
    want(4, description);
    const uint32_t result = (octet() << 24) | (octet() << 16) | (octet() << 8) | octet();
    got(result, 4, description);
    return result;
}