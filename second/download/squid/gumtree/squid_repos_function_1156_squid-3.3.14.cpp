static void
free_IpAddress_list(Ip::Address_list ** head)
{
    if (*head) delete *head;
    *head = NULL;
}