static void
free_acl(ACL ** ae)
{
    aclDestroyAcls(ae);
}

static void
dump_acl_list(StoreEntry * entry, ACLList * head)
{
    ACLList *l;

    for (l = head; l; l = l->next) {
        storeAppendPrintf(entry, " %s%s",
