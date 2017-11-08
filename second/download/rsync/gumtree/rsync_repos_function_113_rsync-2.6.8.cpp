static void msg2sndr_flush(void)
{
	if (defer_forwarding_messages)
		return;

	while (msg2sndr.head && io_multiplexing_out) {
		struct msg_list_item *m = msg2sndr.head;
		if (!(msg2sndr.head = m->next))
			msg2sndr.tail = NULL;
		stats.total_written += m->len;
		defer_forwarding_messages = 1;
		writefd_unbuffered(sock_f_out, m->buf, m->len);
		defer_forwarding_messages = 0;
		free(m);
	}
}