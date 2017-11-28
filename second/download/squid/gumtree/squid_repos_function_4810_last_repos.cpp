SBuf
Parser::BinaryTokenizer::area(uint64_t size, const char *description)
{
    want(size, description);
    const SBuf result = data_.substr(parsed_, size);
    parsed_ += size;
    got(result, size, description);
    return result;
}