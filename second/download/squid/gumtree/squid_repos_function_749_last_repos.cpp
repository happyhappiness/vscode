static void
free_acl_b_size_t(AclSizeLimit ** head)
{
    delete *head;
    *head = NULL;
}