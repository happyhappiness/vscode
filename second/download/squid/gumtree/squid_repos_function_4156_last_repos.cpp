int acl_httpstatus_data::compare(acl_httpstatus_data* const& a, acl_httpstatus_data* const& b)
{
    int ret;
    ret = aclHTTPStatusCompare(b, a);

    if (ret != 0)
        ret = aclHTTPStatusCompare(a, b);

    if (ret == 0) {
        const SBuf sa = a->toStr();
        const SBuf sb = b->toStr();
        debugs(28, DBG_CRITICAL, "WARNING: '" << sa << "' is a subrange of '" << sb << "'");
        debugs(28, DBG_CRITICAL, "WARNING: because of this '" << sa << "' is ignored to keep splay tree searching predictable");
        debugs(28, DBG_CRITICAL, "WARNING: You should probably remove '" << sb << "' from the ACL named '" << AclMatchedName << "'");
    }

    return ret;
}