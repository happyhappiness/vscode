static pinghost_t *ping_receive_ipv4 (pinghost_t *ph, char *buffer, size_t buffer_len)
{
	struct ip *ip_hdr;
	struct icmp *icmp_hdr;

	size_t ip_hdr_len;

	uint16_t recv_checksum;
	uint16_t calc_checksum;

	uint16_t ident;
	uint16_t seq;

	pinghost_t *ptr;

	if (buffer_len < sizeof (struct ip))
		return (NULL);

	ip_hdr     = (struct ip *) buffer;
	ip_hdr_len = ip_hdr->ip_hl << 2;

	if (buffer_len < ip_hdr_len)
		return (NULL);

	buffer     += ip_hdr_len;
	buffer_len -= ip_hdr_len;

	if (buffer_len < sizeof (struct icmp))
		return (NULL);

	icmp_hdr = (struct icmp *) buffer;
	buffer     += sizeof (struct icmp);
	buffer_len -= sizeof (struct icmp);

	if (icmp_hdr->icmp_type != ICMP_ECHOREPLY)
	{
		dprintf ("Unexpected ICMP type: %i\n", icmp_hdr->icmp_type);
		return (NULL);
	}

	recv_checksum = icmp_hdr->icmp_cksum;
	icmp_hdr->icmp_cksum = 0;
	calc_checksum = ping_icmp4_checksum ((char *) icmp_hdr,
			sizeof (struct icmp) + buffer_len);

	if (recv_checksum != calc_checksum)
	{
		dprintf ("Checksum missmatch: Got 0x%04x, calculated 0x%04x\n",
				recv_checksum, calc_checksum);
		return (NULL);
	}

	ident = ntohs (icmp_hdr->icmp_id);
	seq   = ntohs (icmp_hdr->icmp_seq);

	for (ptr = ph; ptr != NULL; ptr = ptr->next)
	{
		dprintf ("hostname = %s, ident = 0x%04x, seq = %i\n",
				ptr->hostname, ptr->ident, ((ptr->sequence - 1) & 0xFFFF));

		if (ptr->addrfamily != AF_INET)
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