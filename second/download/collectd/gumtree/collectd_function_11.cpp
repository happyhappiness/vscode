int multicast_send (char *type, char *instance, char *value)
{
	int sd = get_write_socket ();
	struct sockaddr_in addr;

	char buf[BUFF_SIZE];
	int buflen;

	if (sd == -1)
		return (-1);

	if ((buflen = snprintf (buf, BUFF_SIZE, "%s %s %s", type, instance, value)) >= BUFF_SIZE)
	{
		fprintf (stderr, "Output truncated..");
		return (-1);
	}
	buf[buflen++] = '\0';

	memset(&addr, '\0', sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr (MCAST_GROUP);
	addr.sin_port = htons (UDP_PORT);

	return (sendto (sd, buf, buflen, 0, (struct sockaddr *) &addr, sizeof (addr)));
}