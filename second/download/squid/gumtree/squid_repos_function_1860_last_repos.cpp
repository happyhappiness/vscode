tos_t
aclMapTOS(acl_tos * head, ACLChecklist * ch)
{
    for (acl_tos *l = head; l; l = l->next) {
        if (!l->aclList || ch->fastCheck(l->aclList).allowed())
            return l->tos;
    }

    return 0;
}