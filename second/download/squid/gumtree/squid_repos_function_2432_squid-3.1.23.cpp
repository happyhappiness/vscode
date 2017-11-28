int
aclMapTOS(acl_tos * head, ACLChecklist * ch)
{
    acl_tos *l;

    for (l = head; l; l = l->next) {
        if (!l->aclList || ch->matchAclListFast(l->aclList))
            return l->tos;
    }

    return 0;
}