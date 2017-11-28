bool
ACLChecklist::matchAclList(const ACLList * head, bool const fast)
{
    // TODO: remove by using object con/destruction-based PROF_* macros.
    PROF_start(aclMatchAclList);
    const bool result = matchNodes(head, fast);
    PROF_stop(aclMatchAclList);
    return result;
}