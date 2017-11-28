void
ACLHasComponentData::parse()
{
    const char *tok = ConfigParser::NextToken();
    if (!tok) {
        debugs(28, DBG_CRITICAL, "FATAL: \"has\" acl argument missing");
        self_destruct();
        return;
    }
    if (ConfigParser::PeekAtToken()) {
        debugs(28, DBG_CRITICAL, "FATAL: multiple components not supported for \"has\" acl");
        self_destruct();
        return;
    }
    parseComponent(tok);
}