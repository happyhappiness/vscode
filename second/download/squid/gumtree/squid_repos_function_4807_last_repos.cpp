uint16_t
Parser::BinaryTokenizer::uint16(const char *description)
{
    want(2, description);
    const uint16_t result = (octet() << 8) | octet();
    got(result, 2, description);
    return result;
}