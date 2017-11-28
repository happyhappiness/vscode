allow_t const &
ACLChecklist::fastCheck(const ACLList * list)
{
    PROF_start(aclCheckFast);

    preCheck("fast ACLs");

    // assume DENY/ALLOW on mis/matches due to not having acl_access object
    if (matchAclList(list, true))
        markFinished(ACCESS_ALLOWED, "all ACLs matched");
    else if (!finished())
        markFinished(ACCESS_DENIED, "ACL mismatched");
    PROF_stop(aclCheckFast);
    return currentAnswer();
}