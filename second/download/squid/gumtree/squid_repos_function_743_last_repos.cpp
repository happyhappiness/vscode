static void
free_acl_tos(acl_tos ** head)
{
    delete *head;
    *head = NULL;
}