static void
free_acl_address(Acl::Address ** head)
{
    delete *head;
    *head = NULL;
}