void
ACLChecklist::checkAccessList()
{
    preCheck();
    /* does the current AND clause match */
    matchAclListSlow(accessList->aclList);
}