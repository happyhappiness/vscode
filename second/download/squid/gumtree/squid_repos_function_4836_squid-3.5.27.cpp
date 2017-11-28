void
aclParseHTTPStatusList(Splay<acl_httpstatus_data *> **curlist)
{
    char *t = NULL;
    acl_httpstatus_data *q = NULL;

    while ((t = strtokFile())) {
        if ((q = aclParseHTTPStatusData(t)) == NULL)
            continue;

        (*curlist)->insert(q, acl_httpstatus_data::compare);
    }
}