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
		unsigned char old_sha1[20];
		char *name;
		int len, name_len;
		char *buffer = packet_buffer;

		len = packet_read(in, &src_buf, &src_len,
				  packet_buffer, sizeof(packet_buffer),
				  PACKET_READ_GENTLE_ON_EOF |
				  PACKET_READ_CHOMP_NEWLINE);
		if (len < 0)
			die_initial_contact(got_at_least_one_head);

		if (!len)
			break;

		if (len > 4 && starts_with(buffer, "ERR "))
			die("remote error: %s", buffer + 4);

		if (len == 48 && starts_with(buffer, "shallow ")) {
			if (get_sha1_hex(buffer + 8, old_sha1))
				die("protocol error: expected shallow sha-1, got '%s'", buffer + 8);
			if (!shallow_points)
				die("repository on the other end cannot be shallow");
			sha1_array_append(shallow_points, old_sha1);
			continue;
		}

		if (len < 42 || get_sha1_hex(buffer, old_sha1) || buffer[40] != ' ')
			die("protocol error: expected sha/ref, got '%s'", buffer);
		name = buffer + 41;

		name_len = strlen(name);
		if (len != name_len + 41) {
			free(server_capabilities);
			server_capabilities = xstrdup(name + name_len + 1);
		}

		if (extra_have &&
		    name_len == 5 && !memcmp(".have", name, 5)) {
			sha1_array_append(extra_have, old_sha1);
			continue;
		}

		if (!check_ref(name, name_len, flags))
			continue;
		ref = alloc_ref(buffer + 41);
		hashcpy(ref->old_sha1, old_sha1);
		*list = ref;
		list = &ref->next;
		got_at_least_one_head = 1;
	}

	annotate_refs_with_symref_info(*orig_list);

	return list;
}