static int cmp_in6_addr (const struct in6_addr *a,
	const struct in6_addr *b)
{
    int i;

    assert (sizeof (struct in6_addr) == 16);

    for (i = 0; i < 16; i++)
	if (a->s6_addr[i] != b->s6_addr[i])
	    break;

    if (i >= 16)
	return (0);

    return (a->s6_addr[i] > b->s6_addr[i] ? 1 : -1);
}