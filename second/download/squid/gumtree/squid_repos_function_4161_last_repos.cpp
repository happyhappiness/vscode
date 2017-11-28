void
ACLHTTPStatus::parse()
{
    if (!data)
        data = new Splay<acl_httpstatus_data*>();

    aclParseHTTPStatusList (&data);
}