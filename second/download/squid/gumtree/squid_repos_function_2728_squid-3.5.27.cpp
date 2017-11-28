char *
ConfigParser::CfgFile::nextElement(ConfigParser::TokenType &type)
{
    const char *pos = parsePos;
    char *token = TokenParse(pos, type);
    if (!PreviewMode_ || type == FunctionParameters)
        parsePos = pos;
    // else next call will read the same token;
    return token;
}