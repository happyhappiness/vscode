int64_t
GetInteger64(void)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    return xatoll(token, 10);
}