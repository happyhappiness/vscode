void ignore_list_add_name (const char *name)
{
    struct addrinfo *ai_list;
    struct addrinfo *ai_ptr;
    struct in6_addr  addr;
    int status;

    status = getaddrinfo (name, NULL, NULL, &ai_list);
    if (status != 0)
	return;

    for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
    {
	if (ai_ptr->ai_family == AF_INET)
	{
	    memset (&addr, '\0', sizeof (addr));
	    addr.s6_addr[10] = 0xFF;
	    addr.s6_addr[11] = 0xFF;
	    memcpy (addr.s6_addr + 12, &((struct sockaddr_in *) ai_ptr->ai_addr)->sin_addr, 4);

	    ignore_list_add (&addr);
	}
	else
	{
	    ignore_list_add (&((struct sockaddr_in6 *) ai_ptr->ai_addr)->sin6_addr);
	}
    } /* for */

    freeaddrinfo (ai_list);
}