char *
ConfigParser::RegexPattern()
{
    if (ConfigParser::RecognizeQuotedValues) {
        debugs(3, DBG_CRITICAL, "FATAL: Can not read regex expression while configuration_includes_quoted_values is enabled");
        self_destruct();
    }
    ConfigParser::RecognizeQuotedPair_ = true;
    char * token = NextToken();
    ConfigParser::RecognizeQuotedPair_ = false;
    return token;
}