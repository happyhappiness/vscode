		if (!len)
			break;

		if (len > 4 && skip_prefix(buffer, "ERR ", &arg))
			die("remote error: %s", arg);

		if (len == GIT_SHA1_HEXSZ + strlen("shallow ") &&
			skip_prefix(buffer, "shallow ", &arg)) {
			if (get_oid_hex(arg, &old_oid))
				die("protocol error: expected shallow sha-1, got '%s'", arg);
			if (!shallow_points)
				die("repository on the other end cannot be shallow");
			sha1_array_append(shallow_points, old_oid.hash);
			continue;
		}

		if (len < GIT_SHA1_HEXSZ + 2 || get_oid_hex(buffer, &old_oid) ||
			buffer[GIT_SHA1_HEXSZ] != ' ')
			die("protocol error: expected sha/ref, got '%s'", buffer);
		name = buffer + GIT_SHA1_HEXSZ + 1;

		name_len = strlen(name);
		if (len != name_len + GIT_SHA1_HEXSZ + 1) {
			free(server_capabilities);
			server_capabilities = xstrdup(name + name_len + 1);
		}

		if (extra_have && !strcmp(name, ".have")) {
			sha1_array_append(extra_have, old_oid.hash);
			continue;
		}

		if (!check_ref(name, flags))
			continue;
		ref = alloc_ref(buffer + GIT_SHA1_HEXSZ + 1);
		oidcpy(&ref->old_oid, &old_oid);
		*list = ref;
		list = &ref->next;
		got_at_least_one_head = 1;
	}

	annotate_refs_with_symref_info(*orig_list);
