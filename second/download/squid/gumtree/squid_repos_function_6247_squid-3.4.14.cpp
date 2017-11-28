char *
Format::QuoteUrlEncodeUsername(const char *name)
{
    if (NULL == name)
        return NULL;

    if (name[0] == '\0')
        return NULL;

    return QuoteMimeBlob(name);
//    return username_quote(name);
}