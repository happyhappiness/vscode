static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
{
    if (ssl_bump)
        dump_SBufList(entry, ssl_bump->treeDump(name, [](const allow_t &action) {
        return Ssl::BumpModeStr.at(action.kind);
    }));
}