void
aclParseHTTPStatusList(SplayNode<acl_httpstatus_data *> **curlist)
{
    char *t = NULL;
    SplayNode<acl_httpstatus_data*> **Top = curlist;
    acl_httpstatus_data *q = NULL;

    while ((t = strtokFile())) {
        if ((q = aclParseHTTPStatusData(t)) == NULL)
            continue;

        *Top = (*Top)->insert(q, acl_httpstatus_data::compare);
    }
}