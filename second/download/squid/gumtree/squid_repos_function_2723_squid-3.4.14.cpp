char *
xstrtok(char *str, const char *delimiters)
{
    assert(!str); // we are parsing the configuration file
    // no support unless enabled in the configuration and
    // no support for other delimiters (they may need to be eradicated!)
    return (ConfigParser::RecognizeQuotedValues &&
            strcmp(delimiters, " \t\n\r") == 0) ?
           ConfigParser::NextToken() : ::strtok(str, delimiters);
}