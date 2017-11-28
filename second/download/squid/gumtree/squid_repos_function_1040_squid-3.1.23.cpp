static void
free_acl_address(acl_address ** head)
{
    while (*head) {
        acl_address *l = *head;
        *head = l->next;
        cbdataFree(l);
    }
}