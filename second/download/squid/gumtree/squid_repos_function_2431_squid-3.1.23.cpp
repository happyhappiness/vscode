static IpAddress
aclMapAddr(acl_address * head, ACLChecklist * ch)
{
    acl_address *l;

    IpAddress addr;

    for (l = head; l; l = l->next) {
        if (!l->aclList || ch->matchAclListFast(l->aclList))
            return l->addr;
    }

    addr.SetAnyAddr();
    return addr;
}