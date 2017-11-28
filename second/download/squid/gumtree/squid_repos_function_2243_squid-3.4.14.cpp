tos_t
aclMapTOS(acl_tos * head, ACLChecklist * ch)
{
    acl_tos *l;

    for (l = head; l; l = l->next) {
        if (!l->aclList || ch->fastCheck(l->aclList) == ACCESS_ALLOWED)
            return l->tos;
    }

    return 0;
}