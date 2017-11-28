static void
free_acl_nfmark(acl_nfmark ** head)
{
    delete *head;
    *head = NULL;
}