		if (!len)
			break;

		if (len > 4 && skip_prefix(buffer, "ERR ", &arg))
			die("remote error: %s", arg);

		if (len == 48 && skip_prefix(buffer, "shallow ", &arg)) {
			if (get_sha1_hex(arg, old_sha1))
				die("protocol error: expected shallow sha-1, got '%s'", arg);
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

		if (extra_have && !strcmp(name, ".have")) {
			sha1_array_append(extra_have, old_sha1);
			continue;
		}

		if (!check_ref(name, flags))
			continue;
		ref = alloc_ref(buffer + 41);
		hashcpy(ref->old_sha1, old_sha1);
		*list = ref;
		list = &ref->next;
		got_at_least_one_head = 1;
	}

	annotate_refs_with_symref_info(*orig_list);
