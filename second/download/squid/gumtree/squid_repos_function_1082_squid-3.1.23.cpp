static void
parse_peer_access(void)
{
    char *host = NULL;
    peer *p;

    if (!(host = strtok(NULL, w_space)))
        self_destruct();

    if ((p = peerFindByName(host)) == NULL) {
        debugs(15, 0, "" << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
        return;
    }

    aclParseAccessLine(LegacyParser, &p->access);
}