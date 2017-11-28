bool
Parser::Tokenizer::skip(const char tokenChar)
{
    if (!buf_.isEmpty() && buf_[0] == tokenChar) {
        debugs(24, 8, "skipping char '" << tokenChar << '\'');
        return success(1);
    }
    debugs(24, 8, "no match, not skipping char '" << tokenChar << '\'');
    return false;
}