static void
dump_http_header_replace(StoreEntry * entry, const char *name, const HeaderManglers *manglers)
{
    if (manglers)
        manglers->dumpReplacement(entry, name);
}