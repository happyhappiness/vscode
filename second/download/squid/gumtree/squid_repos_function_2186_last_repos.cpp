char *
ConfigParser::CfgFile::parse(ConfigParser::TokenType &type)
{
    if (!wordFile)
        return NULL;

    if (!*parseBuffer)
        return NULL;

    char *token;
    while (!(token = nextElement(type))) {
        if (!getFileLine())
            return NULL;
    }
    return token;
}