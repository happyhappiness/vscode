static void networt_send_buffer_plain (const sockent_t *se, /* {{{ */
		const char *buffer, size_t buffer_size)
{
	int status;

	while (42)
	{
		status = sendto (se->data.client.fd, buffer, buffer_size,
                    /* flags = */ 0,
                    (struct sockaddr *) se->data.client.addr,
                    se->data.client.addrlen);
                if (status < 0)
		{
			char errbuf[1024];
			if (errno == EINTR)
				continue;
			ERROR ("network plugin: sendto failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			break;
		}

		break;
	} /* while (42) */
}