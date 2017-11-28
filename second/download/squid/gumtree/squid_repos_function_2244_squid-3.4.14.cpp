nfmark_t
aclMapNfmark(acl_nfmark * head, ACLChecklist * ch)
{
    acl_nfmark *l;

    for (l = head; l; l = l->next) {
        if (!l->aclList || ch->fastCheck(l->aclList) == ACCESS_ALLOWED)
            return l->nfmark;
    }

    return 0;
}