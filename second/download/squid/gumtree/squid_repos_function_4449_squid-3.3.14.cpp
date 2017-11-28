void
aclDestroyAclList(ACLList ** head)
{
    ACLList *l;
    debugs(28, 8, "aclDestroyAclList: invoked");

    for (l = *head; l; l = *head) {
        *head = l->next;
        delete l;
    }
}