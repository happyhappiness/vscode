static void
parse_configuration_includes_quoted_values(bool *recognizeQuotedValues)
{
    int val = 0;
    parse_onoff(&val);

    // If quoted values is set to on then enable new strict mode parsing
    if (val) {
        ConfigParser::RecognizeQuotedValues = true;
        ConfigParser::StrictMode = true;
    } else {
        ConfigParser::RecognizeQuotedValues = false;
        ConfigParser::StrictMode = false;
    }
}