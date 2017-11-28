Eui::Eui48 *
aclParseArpData(const char *t)
{
    char buf[256];
    Eui::Eui48 *q = new Eui::Eui48;
    debugs(28, 5, "aclParseArpData: " << t);

    if (sscanf(t, "%[0-9a-fA-F:]", buf) != 1) {
        debugs(28, DBG_CRITICAL, "aclParseArpData: Bad ethernet address: '" << t << "'");
        delete q;
        return NULL;
    }

    if (!q->decode(buf)) {
        debugs(28, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "aclParseArpData: Ignoring invalid ARP acl entry: can't parse '" << buf << "'");
        delete q;
        return NULL;
    }

    return q;
}