char *strdup(const char *str)
{
    char *sdup;
    size_t len = strlen(str) + 1;

    sdup = (char *) malloc(len);
    memcpy(sdup, str, len);

    return sdup;
}