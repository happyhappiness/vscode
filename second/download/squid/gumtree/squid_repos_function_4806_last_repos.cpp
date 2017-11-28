uint8_t
Parser::BinaryTokenizer::uint8(const char *description)
{
    want(1, description);
    const uint8_t result = octet();
    got(result, 1, description);
    return result;
}