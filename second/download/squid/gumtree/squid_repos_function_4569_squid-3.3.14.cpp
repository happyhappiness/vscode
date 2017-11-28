int acl_httpstatus_data::compare(acl_httpstatus_data* const& a, acl_httpstatus_data* const& b)
{
    int ret;
    ret = aclHTTPStatusCompare(b, a);

    if (ret != 0)
        ret = aclHTTPStatusCompare(a, b);

    if (ret == 0) {
        char bufa[8];
        char bufb[8];
        a->toStr(bufa, sizeof(bufa));
        b->toStr(bufb, sizeof(bufb));
        debugs(28, DBG_CRITICAL, "WARNING: '" << bufa << "' is a subrange of '" << bufb << "'");
        debugs(28, DBG_CRITICAL, "WARNING: because of this '" << bufa << "' is ignored to keep splay tree searching predictable");
        debugs(28, DBG_CRITICAL, "WARNING: You should probably remove '" << bufb << "' from the ACL named '" << AclMatchedName << "'");
    }

    return ret;
}