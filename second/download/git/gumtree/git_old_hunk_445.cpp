struct ref **get_remote_heads(int in, char *src_buf, size_t src_len,
			      struct ref **list, unsigned int flags,
			      struct sha1_array *extra_have,
			      struct sha1_array *shallow_points)
{
	struct ref **orig_list = list;
	int got_at_least_one_head = 0;

	*list = NULL;
	for (;;) {
		struct ref *ref;
		struct object_id old_oid;
		char *name;
		int len, name_len;
		char *buffer = packet_buffer;
		const char *arg;

		len = packet_read(in, &src_buf, &src_len,
				  packet_buffer, sizeof(packet_buffer),
				  PACKET_READ_GENTLE_ON_EOF |
				  PACKET_READ_CHOMP_NEWLINE);
		if (len < 0)
			die_initial_contact(got_at_least_one_head);

		if (!len)
			break;

		if (len > 4 && skip_prefix(buffer, "ERR ", &arg))
			die("remote error: %s", arg);
