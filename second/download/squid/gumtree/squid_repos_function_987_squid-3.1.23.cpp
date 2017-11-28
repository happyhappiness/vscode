void
DelaySpec::parse()
{
    int r;
    char *token;
    token = strtok(NULL, "/");

    if (token == NULL)
        self_destruct();

    if (sscanf(token, "%d", &r) != 1)
        self_destruct();

    restore_bps = r;

    max_bytes = GetInteger64();
}