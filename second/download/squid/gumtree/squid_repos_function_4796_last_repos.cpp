void
Parser::BinaryTokenizer::want(uint64_t size, const char *description) const
{
    if (parsed_ + size > data_.length()) {
        debugs(24, 5, (parsed_ + size - data_.length()) << " more bytes for " <<
               context << description << BinaryTokenizer_tail(size, parsed_));
        Must(expectMore_); // throw an error on premature input termination
        throw InsufficientInput();
    }
}