static void
parse_peer_access(void)
{
    char *host = NULL;
    CachePeer *p;

    if (!(host = ConfigParser::NextToken()))
        self_destruct();

    if ((p = peerFindByName(host)) == NULL) {
        debugs(15, DBG_CRITICAL, "" << cfg_filename << ", line " << config_lineno << ": No cache_peer '" << host << "'");
        return;
    }

    std::string directive = "peer_access ";
    directive += host;
    aclParseAccessLine(directive.c_str(), LegacyParser, &p->access);
}