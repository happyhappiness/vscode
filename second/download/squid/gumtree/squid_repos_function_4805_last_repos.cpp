bool
Parser::BinaryTokenizer::atEnd() const
{
    return parsed_ >= data_.length();
}