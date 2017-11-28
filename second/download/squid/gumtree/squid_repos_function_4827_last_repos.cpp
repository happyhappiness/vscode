bool
Parser::Tokenizer::skipOneTrailing(const CharacterSet &skippable)
{
    if (!buf_.isEmpty() && skippable[buf_[buf_.length()-1]]) {
        debugs(24, 8, "skipping one-of " << skippable.name);
        return successTrailing(1);
    }
    debugs(24, 8, "no match while skipping one-of " << skippable.name);
    return false;
}