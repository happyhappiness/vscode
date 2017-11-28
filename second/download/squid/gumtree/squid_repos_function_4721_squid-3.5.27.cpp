void
ACLHTTPHeaderData::parse()
{
    char* t = strtokFile();
    if (!t) {
        debugs(28, DBG_CRITICAL, "ERROR: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "ERROR: Missing header name in ACL");
        return;
    }

    if (hdrName.size() == 0) {
        hdrName = t;
        hdrId = httpHeaderIdByNameDef(hdrName.rawBuf(), hdrName.size());
    } else if (hdrName.caseCmp(t) != 0) {
        debugs(28, DBG_CRITICAL, "ERROR: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, DBG_CRITICAL, "ERROR: ACL cannot match both " << hdrName << " and " << t << " headers. Use 'anyof' ACL instead.");
        return;
    }

    regex_rule->parse();
}