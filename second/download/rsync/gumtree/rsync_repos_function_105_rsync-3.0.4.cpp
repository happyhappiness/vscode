static inline int flush_a_msg(int fd)
{
	struct msg_list_item *m = msg_queue.head;
	int len = IVAL(m->buf, 0) & 0xFFFFFF;
	int tag = *((uchar*)m->buf+3) - MPLEX_BASE;

	if (!(msg_queue.head = m->next))
		msg_queue.tail = NULL;

	defer_forwarding_messages++;
	mplex_write(fd, tag, m->buf + 4, len, m->convert);
	defer_forwarding_messages--;

	free(m);

	return len;
}