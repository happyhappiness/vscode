void
parse_wordlist(wordlist ** list)
{
    char *token;
    while ((token = ConfigParser::NextQuotedToken()))
        wordlistAdd(list, token);
}