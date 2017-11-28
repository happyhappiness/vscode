static int
aclHTTPStatusCompare(acl_httpstatus_data * const &a, acl_httpstatus_data * const &b)
{
    if (a->status1 < b->status1)
        return 1;

    if (a->status1 > b->status2)
        return -1;

    return 0;
}