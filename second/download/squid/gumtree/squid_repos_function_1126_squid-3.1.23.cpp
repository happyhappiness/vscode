static void
dump_uri_whitespace(StoreEntry * entry, const char *name, int var)
{
    const char *s;

    if (var == URI_WHITESPACE_ALLOW)
        s = "allow";
    else if (var == URI_WHITESPACE_ENCODE)
        s = "encode";
    else if (var == URI_WHITESPACE_CHOP)
        s = "chop";
    else if (var == URI_WHITESPACE_DENY)
        s = "deny";
    else
        s = "strip";

    storeAppendPrintf(entry, "%s %s\n", name, s);
}