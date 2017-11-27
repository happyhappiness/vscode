static pinghost_t *ping_receive_ipv6 (pinghost_t *ph, char *buffer, size_t buffer_len)
{
	struct icmp6_hdr *icmp_hdr;

	uint16_t ident;
	uint16_t seq;

	pinghost_t *ptr;

	if (buffer_len < sizeof (struct icmp6_hdr))
		return (NULL);

	icmp_hdr = (struct icmp6_hdr *) buffer;
	buffer     += sizeof (struct icmp);
	buffer_len -= sizeof (struct icmp);

	if (icmp_hdr->icmp6_type != ICMP6_ECHO_REPLY)
	{
		dprintf ("Unexpected ICMP type: %02x\n", icmp_hdr->icmp6_type);
		return (NULL);
	}

	if (icmp_hdr->icmp6_code != 0)
	{
		dprintf ("Unexpected ICMP code: %02x\n", icmp_hdr->icmp6_code);
		return (NULL);
	}

	ident = ntohs (icmp_hdr->icmp6_id);
	seq   = ntohs (icmp_hdr->icmp6_seq);

	for (ptr = ph; ptr != NULL; ptr = ptr->next)
	{
		dprintf ("hostname = %s, ident = 0x%04x, seq = %i\n",
				ptr->hostname, ptr->ident, ((ptr->sequence - 1) & 0xFFFF));

		if (ptr->addrfamily != AF_INET6)
			continue;

		if (!timerisset (ptr->timer))
			continue;

		if (ptr->ident != ident)
			continue;

		if (((ptr->sequence - 1) & 0xFFFF) != seq)
			continue;

		dprintf ("Match found: hostname = %s, ident = 0x%04x, seq = %i\n",
				ptr->hostname, ident, seq);

		break;
	}

	if (ptr == NULL)
	{
		dprintf ("No match found for ident = 0x%04x, seq = %i\n",
				ident, seq);
	}

	return (ptr);
}