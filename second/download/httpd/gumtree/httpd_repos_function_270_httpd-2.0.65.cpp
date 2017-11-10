static char *dav_fetch_next_token(char **str, char term)
{
    char *sp;
    char *token;
        
    token = *str + 1;

    while (*token && (*token == ' ' || *token == '\t'))
        token++;

    if ((sp = strchr(token, term)) == NULL)
        return NULL;

    *sp = '\0';
    *str = sp;
    return token;
}