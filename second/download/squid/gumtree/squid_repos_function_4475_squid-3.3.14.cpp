void
ACLHTTPHeaderData::parse()
{
    char* t = strtokFile();
    assert (t != NULL);
    hdrName = t;
    hdrId = httpHeaderIdByNameDef(hdrName.rawBuf(), hdrName.size());
    regex_rule->parse();
}