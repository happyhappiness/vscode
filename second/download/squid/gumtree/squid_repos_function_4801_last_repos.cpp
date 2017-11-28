uint32_t
Parser::BinaryTokenizer::octet()
{
    // While char may be signed, we view data characters as unsigned,
    // which helps to arrive at the right 32-bit return value.
    return static_cast<uint8_t>(data_[parsed_++]);
}