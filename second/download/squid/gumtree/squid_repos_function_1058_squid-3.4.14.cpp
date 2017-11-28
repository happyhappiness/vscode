static void
free_acl_tos(acl_tos ** head)
{
    while (*head) {
        acl_tos *l = *head;
        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}