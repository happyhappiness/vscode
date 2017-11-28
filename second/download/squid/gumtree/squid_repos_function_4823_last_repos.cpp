bool
Parser::Tokenizer::skipOne(const CharacterSet &chars)
{
    if (!buf_.isEmpty() && chars[buf_[0]]) {
        debugs(24, 8, "skipping one-of " << chars.name);
        return success(1);
    }
    debugs(24, 8, "no match while skipping one-of " << chars.name);
    return false;
}