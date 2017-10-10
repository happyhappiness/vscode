struct ref **get_remote_heads(int in, char *src_buf, size_t src_len,
			      struct ref **list, unsigned int flags,
			      struct sha1_array *extra_have,
			      struct sha1_array *shallow_points)
{
	struct ref **orig_list = list;

	/*
	 * A hang-up after seeing some response from the other end
	 * means that it is unexpected, as we know the other end is
	 * willing to talk to us.  A hang-up before seeing any
	 * response does not necessarily mean an ACL problem, though.
	 */
	int saw_response;
	int got_dummy_ref_with_capabilities_declaration = 0;

	*list = NULL;
	for (saw_response = 0; ; saw_response = 1) {
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
			die_initial_contact(saw_response);

		if (!len)
			break;

		if (len > 4 && skip_prefix(buffer, "ERR ", &arg))
			die("remote error: %s", arg);
