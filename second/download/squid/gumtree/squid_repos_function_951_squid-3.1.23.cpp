unsigned short
GetShort(void)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    return xatos(token);
}