static int ping_send_one_ipv4 (pingobj_t *obj, pinghost_t *ph)
{
	struct icmp *icmp4;
	int status;

	char buf[4096];
	int  buflen;

	char *data;
	int   datalen;

	dprintf ("ph->hostname = %s\n", ph->hostname);

	memset (buf, '\0', sizeof (buf));
	icmp4 = (struct icmp *) buf;
	data  = (char *) (icmp4 + 1);

	icmp4->icmp_type  = ICMP_ECHO;
	icmp4->icmp_code  = 0;
	icmp4->icmp_cksum = 0;
	icmp4->icmp_id    = htons (ph->ident);
	icmp4->icmp_seq   = htons (ph->sequence);

	buflen = 4096 - sizeof (struct icmp);
	strncpy (data, ph->data, buflen);
	datalen = strlen (data);

	buflen = datalen + sizeof (struct icmp);

	icmp4->icmp_cksum = ping_icmp4_checksum (buf, buflen);

	dprintf ("Sending ICMPv4 package with ID 0x%04x\n", ph->ident);

	status = ping_sendto (obj, ph, buf, buflen);
	if (status < 0)
	{
		perror ("ping_sendto");
		return (-1);
	}

	dprintf ("sendto: status = %i\n", status);

	return (0);
}