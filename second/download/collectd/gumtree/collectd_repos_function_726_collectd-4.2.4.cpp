static int ping_send_one_ipv6 (pingobj_t *obj, pinghost_t *ph)
{
	struct icmp6_hdr *icmp6;
	int status;

	char buf[4096];
	int  buflen;

	char *data;
	int   datalen;

	dprintf ("ph->hostname = %s\n", ph->hostname);

	memset (buf, '\0', sizeof (buf));
	icmp6 = (struct icmp6_hdr *) buf;
	data  = (char *) (icmp6 + 1);

	icmp6->icmp6_type  = ICMP6_ECHO_REQUEST;
	icmp6->icmp6_code  = 0;
	/* The checksum will be calculated by the TCP/IP stack.  */
	/* FIXME */
	icmp6->icmp6_cksum = 0;
	icmp6->icmp6_id    = htons (ph->ident);
	icmp6->icmp6_seq   = htons (ph->sequence);

	buflen = 4096 - sizeof (struct icmp6_hdr);
	strncpy (data, ph->data, buflen);
	datalen = strlen (data);

	buflen = datalen + sizeof (struct icmp6_hdr);

	dprintf ("Sending ICMPv6 package with ID 0x%04x\n", ph->ident);

	status = ping_sendto (obj, ph, buf, buflen);
	if (status < 0)
	{
		perror ("ping_sendto");
		return (-1);
	}

	dprintf ("sendto: status = %i\n", status);

	return (0);
}