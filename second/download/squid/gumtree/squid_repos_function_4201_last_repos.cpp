bool
Acl::OptionExtractor::advance()
{
    const char *next = ConfigParser::PeekAtToken();
    if (!next)
        return false; // end of the "acl" line

    const char nextChar = *next;
    if (!(nextChar == '-' || nextChar == '+'))
        return false; // start of ACL parameters

    sawValue_ = strchr(next, '='); // TODO: Make ConfigParser reject '^=.*' tokens
    if (sawValue_) {
        char *rawPrefix = nullptr;
        char *rawValue = nullptr;
        if (!ConfigParser::NextKvPair(rawPrefix, rawValue))
            throw TexcHere(ToSBuf("Malformed acl option=value: ", next));
        prefix_.assign(rawPrefix);
        value_.assign(rawValue);
    } else {
        prefix_.assign(next);
        ConfigParser::NextToken(); // consume what we have peeked at
    }
    return true;
}