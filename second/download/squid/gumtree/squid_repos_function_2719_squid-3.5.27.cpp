char *
ConfigParser::PeekAtToken()
{
    PreviewMode_ = true;
    char *token = NextToken();
    PreviewMode_ = false;
    return token;
}