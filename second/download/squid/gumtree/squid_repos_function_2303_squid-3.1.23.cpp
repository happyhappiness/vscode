static char *
accessLogFormatName(const char *name)
{
    if (NULL == name)
        return NULL;

    if (name[0] == '\0')
        return NULL;

    return username_quote(name);
}