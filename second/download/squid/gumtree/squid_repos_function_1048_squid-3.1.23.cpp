static void
free_acl_b_size_t(acl_size_t ** head)
{
    while (*head) {
        acl_size_t *l = *head;
        *head = l->next;
        l->next = NULL;
        cbdataFree(l);
    }
}