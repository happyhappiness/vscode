bool
Parser::Tokenizer::skip(const char tokenChar)
{
    if (!buf_.isEmpty() && buf_[0] == tokenChar)
        return success(1);
    return false;
}