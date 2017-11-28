bool
ACLChecklist::matchAclListFast(const ACLList * list)
{
    matchAclList(list, true);
    return finished();
}