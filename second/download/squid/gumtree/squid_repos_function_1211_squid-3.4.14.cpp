static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
{
    if (ssl_bump) {
        wordlist *lines = ssl_bump->treeDump(name, Ssl::BumpModeStr);
        dump_wordlist(entry, lines);
        wordlistDestroy(&lines);
    }
}