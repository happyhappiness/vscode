void acl_httpstatus_data::toStr(char* buf, int len) const
{
    if (status2 == INT_MAX)
        snprintf(buf, len, "%d-", status1);
    else if (status1 == status2)
        snprintf(buf, len, "%d", status1);
    else
        snprintf(buf, len, "%d-%d", status1, status2);
}