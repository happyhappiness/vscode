static void
dump_on_unsupported_protocol(StoreEntry *entry, const char *name, acl_access *access)
{
    static const std::vector<const char *> onErrorTunnelMode = {
        "none",
        "tunnel",
        "respond"
    };
    if (access) {
        SBufList lines = access->treeDump(name, [](const allow_t &action) {
            return onErrorTunnelMode.at(action.kind);
        });
        dump_SBufList(entry, lines);
    }
}