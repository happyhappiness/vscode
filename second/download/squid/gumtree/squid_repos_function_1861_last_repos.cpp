nfmark_t
aclMapNfmark(acl_nfmark * head, ACLChecklist * ch)
{
    for (acl_nfmark *l = head; l; l = l->next) {
        if (!l->aclList || ch->fastCheck(l->aclList).allowed())
            return l->nfmark;
    }

    return 0;
}