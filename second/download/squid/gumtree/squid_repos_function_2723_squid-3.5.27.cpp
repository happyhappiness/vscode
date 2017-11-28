char *
ConfigParser::NextQuotedToken()
{
    const bool saveRecognizeQuotedValues = ConfigParser::RecognizeQuotedValues;
    ConfigParser::RecognizeQuotedValues = true;
    char *token = NextToken();
    ConfigParser::RecognizeQuotedValues = saveRecognizeQuotedValues;
    return token;
}