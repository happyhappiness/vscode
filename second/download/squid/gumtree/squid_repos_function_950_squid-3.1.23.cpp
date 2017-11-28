int
GetInteger(void)
{
    char *token = strtok(NULL, w_space);
    int i;

    if (token == NULL)
        self_destruct();

    // %i honors 0 and 0x prefixes, which are important for things like umask
    if (sscanf(token, "%i", &i) != 1)
        self_destruct();

    return i;
}