static void
parse_peer_access(void)
{
    char *host = ConfigParser::NextToken();
    if (!host) {
        self_destruct();
        return;
    }

    CachePeer *p = peerFindByName(host);
    if (!p) {
        debugs(15, DBG_CRITICAL, "ERROR: " << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
        return;
    }

    std::string directive = "peer_access ";
    directive += host;
    aclParseAccessLine(directive.c_str(), LegacyParser, &p->access);
}