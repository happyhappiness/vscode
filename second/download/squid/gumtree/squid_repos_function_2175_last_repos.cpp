char *
ConfigParser::NextElement(ConfigParser::TokenType &type)
{
    const char *pos = CfgPos;
    char *token = TokenParse(pos, type);
    // If not in preview mode the next call of this method should start
    // parsing after the end of current token.
    // For function "parameters(...)" we need always to update current parsing
    // position to allow parser read the arguments of "parameters(..)"
    if (!PreviewMode_ || type == FunctionParameters)
        CfgPos = pos;
    // else next call will read the same token
    return token;
}