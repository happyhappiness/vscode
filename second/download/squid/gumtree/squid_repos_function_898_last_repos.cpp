static void parse_HeaderWithAclList(HeaderWithAclList **headers)
{
    char *fn;
    if (!*headers) {
        *headers = new HeaderWithAclList;
    }
    if ((fn = ConfigParser::NextToken()) == NULL) {
        self_destruct();
        return;
    }
    HeaderWithAcl hwa;
    hwa.fieldName = fn;
    hwa.fieldId = Http::HeaderLookupTable.lookup(hwa.fieldName).id;
    if (hwa.fieldId == Http::HdrType::BAD_HDR)
        hwa.fieldId = Http::HdrType::OTHER;

    Format::Format *nlf =  new ::Format::Format("hdrWithAcl");
    ConfigParser::EnableMacros();
    String buf = ConfigParser::NextQuotedToken();
    ConfigParser::DisableMacros();
    hwa.fieldValue = buf.termedBuf();
    hwa.quoted = ConfigParser::LastTokenWasQuoted();
    if (hwa.quoted) {
        if (!nlf->parse(hwa.fieldValue.c_str())) {
            self_destruct();
            return;
        }
        hwa.valueFormat = nlf;
    } else
        delete nlf;
    aclParseAclList(LegacyParser, &hwa.aclList, (hwa.fieldName + ':' + hwa.fieldValue).c_str());
    (*headers)->push_back(hwa);
}