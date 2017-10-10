	}

	if (keep_msg) {
		int keep_fd, keep_msg_len = strlen(keep_msg);

		if (!keep_name)
			keep_name = odb_pack_name(&keep_name_buf, sha1, "keep");

		keep_fd = odb_pack_keep(keep_name);
		if (keep_fd < 0) {
			if (errno != EEXIST)
				die_errno(_("cannot write keep file '%s'"),
					  keep_name);
		} else {
			if (keep_msg_len > 0) {
				write_or_die(keep_fd, keep_msg, keep_msg_len);
				write_or_die(keep_fd, "\n", 1);
			}
			if (close(keep_fd) != 0)
				die_errno(_("cannot close written keep file '%s'"),
					  keep_name);
			report = "keep";
		}
	}

	if (final_pack_name != curr_pack_name) {
		if (!final_pack_name)
			final_pack_name = odb_pack_name(&pack_name, sha1, "pack");
		if (finalize_object_file(curr_pack_name, final_pack_name))
			die(_("cannot store pack file"));
	} else if (from_stdin)
		chmod(final_pack_name, 0444);

	if (final_index_name != curr_index_name) {
		if (!final_index_name)
			final_index_name = odb_pack_name(&index_name, sha1, "idx");
		if (finalize_object_file(curr_index_name, final_index_name))
			die(_("cannot store index file"));
	} else
		chmod(final_index_name, 0444);

	if (!from_stdin) {
