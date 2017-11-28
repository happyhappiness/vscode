SBuf::size_type
Parser::Tokenizer::skipAllTrailing(const CharacterSet &skippable)
{
    const SBuf::size_type prefixEnd = buf_.findLastNotOf(skippable);
    const SBuf::size_type prefixLen = prefixEnd == SBuf::npos ?
                                      0 : (prefixEnd + 1);
    const SBuf::size_type suffixLen = buf_.length() - prefixLen;
    if (suffixLen == 0) {
        debugs(24, 8, "no match when trying to skip " << skippable.name);
        return 0;
    }
    debugs(24, 8, "skipping in " << skippable.name << " len " << suffixLen);
    return successTrailing(suffixLen);
}