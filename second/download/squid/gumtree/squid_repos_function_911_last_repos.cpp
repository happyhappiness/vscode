static void
free_configuration_includes_quoted_values(bool *)
{
    ConfigParser::RecognizeQuotedValues = false;
    ConfigParser::StrictMode = false;
}