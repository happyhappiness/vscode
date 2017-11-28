static void
free_acl_address(AclAddress ** head)
{
    while (*head) {
        AclAddress *l = *head;
        *head = l->next;
        cbdataFree(l);
    }
}