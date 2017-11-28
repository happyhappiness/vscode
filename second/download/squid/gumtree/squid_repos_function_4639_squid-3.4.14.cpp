acl_httpstatus_data*
aclParseHTTPStatusData(const char *t)
{
    int status;
    status = atoi(t);
    t = strchr(t, '-');

    if (!t)
        return new acl_httpstatus_data(status);

    if (*(++t))
        return new acl_httpstatus_data(status, atoi(t));

    return new acl_httpstatus_data(status, INT_MAX);
}