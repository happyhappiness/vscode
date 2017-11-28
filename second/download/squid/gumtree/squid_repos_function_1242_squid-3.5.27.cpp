static void
free_configuration_includes_quoted_values(bool *recognizeQuotedValues)
{
    ConfigParser::RecognizeQuotedValues = false;
    ConfigParser::StrictMode = false;
}