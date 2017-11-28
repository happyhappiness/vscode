bool
Parser::Tokenizer::skipOne(const CharacterSet &chars)
{
    if (!buf_.isEmpty() && chars[buf_[0]])
        return success(1);
    return false;
}