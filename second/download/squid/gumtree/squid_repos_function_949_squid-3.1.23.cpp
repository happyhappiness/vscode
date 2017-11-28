int64_t
GetInteger64(void)
{
    char *token = strtok(NULL, w_space);
    int i;

    if (token == NULL)
        self_destruct();

    i = strtoll(token, NULL, 10);

    return i;
}