void
aclParseHTTPStatusList(Splay<acl_httpstatus_data *> **curlist)
{
    while (char *t = ConfigParser::strtokFile()) {
        if (acl_httpstatus_data *q = aclParseHTTPStatusData(t))
            (*curlist)->insert(q, acl_httpstatus_data::compare);
    }
}