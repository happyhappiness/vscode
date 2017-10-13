static void final(const char *final_pack_name, const char *curr_pack_name,
		  const char *final_index_name, const char *curr_index_name,
		  const char *keep_name, const char *keep_msg,
		  unsigned char *sha1)
{
	const char *report = "pack";
	char name[PATH_MAX];
	int err;

	if (!from_stdin) {
		close(input_fd);
	} else {
		fsync_or_die(output_fd, curr_pack_name);
		err = close(output_fd);
		if (err)
			die_errno(_("error while closing pack file"));
	}

	if (keep_msg) {
		int keep_fd, keep_msg_len = strlen(keep_msg);

		if (!keep_name)
			keep_fd = odb_pack_keep(name, sizeof(name), sha1);
		else
			keep_fd = open(keep_name, O_RDWR|O_CREAT|O_EXCL, 0600);

		if (keep_fd < 0) {
			if (errno != EEXIST)
				die_errno(_("cannot write keep file '%s'"),
					  keep_name ? keep_name : name);
		} else {
			if (keep_msg_len > 0) {
				write_or_die(keep_fd, keep_msg, keep_msg_len);
				write_or_die(keep_fd, "\n", 1);
			}
			if (close(keep_fd) != 0)
				die_errno(_("cannot close written keep file '%s'"),
					  keep_name ? keep_name : name);
			report = "keep";
		}
	}

	if (final_pack_name != curr_pack_name) {
		if (!final_pack_name) {
			snprintf(name, sizeof(name), "%s/pack/pack-%s.pack",
				 get_object_directory(), sha1_to_hex(sha1));
			final_pack_name = name;
		}
		if (finalize_object_file(curr_pack_name, final_pack_name))
			die(_("cannot store pack file"));
	} else if (from_stdin)
		chmod(final_pack_name, 0444);

	if (final_index_name != curr_index_name) {
		if (!final_index_name) {
			snprintf(name, sizeof(name), "%s/pack/pack-%s.idx",
				 get_object_directory(), sha1_to_hex(sha1));
			final_index_name = name;
		}
		if (finalize_object_file(curr_index_name, final_index_name))
			die(_("cannot store index file"));
	} else
		chmod(final_index_name, 0444);

	if (!from_stdin) {
		printf("%s\n", sha1_to_hex(sha1));
	} else {
		char buf[48];
		int len = snprintf(buf, sizeof(buf), "%s\t%s\n",
				   report, sha1_to_hex(sha1));
		write_or_die(1, buf, len);

		/*
		 * Let's just mimic git-unpack-objects here and write
		 * the last part of the input buffer to stdout.
		 */
		while (input_len) {
			err = xwrite(1, input_buffer + input_offset, input_len);
			if (err <= 0)
				break;
			input_len -= err;
			input_offset += err;
		}
	}
}