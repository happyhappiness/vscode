static void
free_IpAddress_list(IpAddress_list ** head)
{
    if (*head) delete *head;
    *head = NULL;
}