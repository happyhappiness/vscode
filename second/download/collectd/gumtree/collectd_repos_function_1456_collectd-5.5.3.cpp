static int riemann_recv_ack(struct riemann_host *host) /* {{{ */
{
	int status = 0;
	Msg *msg = NULL;
	uint32_t header;

	status = (int) sread (host->s, &header, 4);

	if (status != 0)
		return -1;

	size_t size = ntohl(header);

	// Buffer on the stack since acknowledges are typically small.
	u_char buffer[size];
	memset (buffer, 0, size);

	status = (int) sread (host->s, buffer, size);

	if (status != 0)
		return status;

	msg = msg__unpack (NULL, size, buffer);

	if (msg == NULL)
		return -1;

	if (!msg->ok)
	{
		ERROR ("write_riemann plugin: Sending to Riemann at %s:%s acknowledgement message reported error: %s",
				(host->node != NULL) ? host->node : RIEMANN_HOST,
				(host->service != NULL) ? host->service : RIEMANN_PORT,
				msg->error);

		msg__free_unpacked(msg, NULL);
		return -1;
	}

	msg__free_unpacked (msg, NULL);
	return 0;
}