		die(_("Server does not support --deepen"));

	if (everything_local(args, &ref, sought, nr_sought)) {
		packet_flush(fd[1]);
		goto all_done;
	}
	if (find_common(args, fd, sha1, ref) < 0)
		if (!args->keep_pack)
			/* When cloning, it is not unusual to have
			 * no common commit.
			 */
			warning(_("no common commits"));

