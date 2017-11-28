static void
free_acl_nfmark(acl_nfmark ** head)
{
    while (*head) {
        acl_nfmark *l = *head;
        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}