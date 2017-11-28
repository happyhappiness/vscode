void
Parser::BinaryTokenizer::skip(uint64_t size, const char *description)
{
    want(size, description);
    parsed_ += size;
    skipped(size, description);
}