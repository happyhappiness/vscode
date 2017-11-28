void
parse_wordlist(wordlist ** list)
{
    char *token;
    char *t = strtok(NULL, "");

    while ((token = strwordtok(NULL, &t)))
        wordlistAdd(list, token);
}