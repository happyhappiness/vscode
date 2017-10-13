static int rsync_transport_push(struct transport *transport,
		int refspec_nr, const char **refspec, int flags)
{
	struct strbuf buf = STRBUF_INIT, temp_dir = STRBUF_INIT;
	int result = 0, i;
	struct child_process rsync = CHILD_PROCESS_INIT;
	const char *args[10];

	if (flags & TRANSPORT_PUSH_MIRROR)
		return error("rsync transport does not support mirror mode");

	/* first push the objects */

	strbuf_addstr(&buf, rsync_url(transport->url));
	strbuf_addch(&buf, '/');

	rsync.argv = args;
	rsync.stdout_to_stderr = 1;
	i = 0;
	args[i++] = "rsync";
	args[i++] = "-a";
	if (flags & TRANSPORT_PUSH_DRY_RUN)
		args[i++] = "--dry-run";
	if (transport->verbose > 1)
		args[i++] = "-v";
	args[i++] = "--ignore-existing";
	args[i++] = "--exclude";
	args[i++] = "info";
	args[i++] = get_object_directory();
	args[i++] = buf.buf;
	args[i++] = NULL;

	if (run_command(&rsync))
		return error("Could not push objects to %s",
				rsync_url(transport->url));

	/* copy the refs to the temporary directory; they could be packed. */

	strbuf_addstr(&temp_dir, git_path("rsync-refs-XXXXXX"));
	if (!mkdtemp(temp_dir.buf))
		die_errno ("Could not make temporary directory");
	strbuf_addch(&temp_dir, '/');

	if (flags & TRANSPORT_PUSH_ALL) {
		if (for_each_ref(write_one_ref, &temp_dir))
			return -1;
	} else if (write_refs_to_temp_dir(&temp_dir, refspec_nr, refspec))
		return -1;

	i = 2;
	if (flags & TRANSPORT_PUSH_DRY_RUN)
		args[i++] = "--dry-run";
	if (!(flags & TRANSPORT_PUSH_FORCE))
		args[i++] = "--ignore-existing";
	args[i++] = temp_dir.buf;
	args[i++] = rsync_url(transport->url);
	args[i++] = NULL;
	if (run_command(&rsync))
		result = error("Could not push to %s",
				rsync_url(transport->url));

	if (remove_dir_recursively(&temp_dir, 0))
		warning ("Could not remove temporary directory %s.",
				temp_dir.buf);

	strbuf_release(&buf);
	strbuf_release(&temp_dir);

	return result;
}