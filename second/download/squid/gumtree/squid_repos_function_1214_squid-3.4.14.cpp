static void parse_HeaderWithAclList(HeaderWithAclList **headers)
{
    char *fn;
    if (!*headers) {
        *headers = new HeaderWithAclList;
    }
    if ((fn = strtok(NULL, w_space)) == NULL) {
        self_destruct();
        return;
    }
    HeaderWithAcl hwa;
    hwa.fieldName = fn;
    hwa.fieldId = httpHeaderIdByNameDef(fn, strlen(fn));
    if (hwa.fieldId == HDR_BAD_HDR)
        hwa.fieldId = HDR_OTHER;

    String buf;
    bool wasQuoted;
    ConfigParser::ParseQuotedString(&buf, &wasQuoted);
    hwa.fieldValue = buf.termedBuf();
    hwa.quoted = wasQuoted;
    if (hwa.quoted) {
        Format::Format *nlf =  new ::Format::Format("hdrWithAcl");
        if (!nlf->parse(hwa.fieldValue.c_str())) {
            self_destruct();
            return;
        }
        hwa.valueFormat = nlf;
    }

    aclParseAclList(LegacyParser, &hwa.aclList, (hwa.fieldName + ':' + hwa.fieldValue).c_str());
    (*headers)->push_back(hwa);
}