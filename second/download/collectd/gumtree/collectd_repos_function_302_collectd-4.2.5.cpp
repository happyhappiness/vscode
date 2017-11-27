static void ignore_list_add (const struct in6_addr *addr)
{
    ip_list_t *new;

    if (ignore_list_match (addr) != 0)
	return;

    new = malloc (sizeof (ip_list_t));
    if (new == NULL)
    {
	perror ("malloc");
	return;
    }

    memcpy (&new->addr, addr, sizeof (struct in6_addr));
    new->next = IgnoreList;

    IgnoreList = new;
}