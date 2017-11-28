static void
free_acl_b_size_t(AclSizeLimit ** head)
{
    while (*head) {
        AclSizeLimit *l = *head;
        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}