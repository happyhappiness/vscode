static struct ref *get_refs_via_rsync(struct transport *transport, int for_push)
{
	struct strbuf buf = STRBUF_INIT, temp_dir = STRBUF_INIT;
	struct ref dummy = {NULL}, *tail = &dummy;
	struct child_process rsync = CHILD_PROCESS_INIT;
	const char *args[5];
	int temp_dir_len;

	if (for_push)
		return NULL;

	/* copy the refs to the temporary directory */

	strbuf_addstr(&temp_dir, git_path("rsync-refs-XXXXXX"));
	if (!mkdtemp(temp_dir.buf))
		die_errno ("Could not make temporary directory");
	temp_dir_len = temp_dir.len;

	strbuf_addstr(&buf, rsync_url(transport->url));
	strbuf_addstr(&buf, "/refs");

	rsync.argv = args;
	rsync.stdout_to_stderr = 1;
	args[0] = "rsync";
	args[1] = (transport->verbose > 1) ? "-rv" : "-r";
	args[2] = buf.buf;
	args[3] = temp_dir.buf;
	args[4] = NULL;

	if (run_command(&rsync))
		die ("Could not run rsync to get refs");

	strbuf_reset(&buf);
	strbuf_addstr(&buf, rsync_url(transport->url));
	strbuf_addstr(&buf, "/packed-refs");

	args[2] = buf.buf;

	if (run_command(&rsync))
		die ("Could not run rsync to get refs");

	/* read the copied refs */

	strbuf_addstr(&temp_dir, "/refs");
	read_loose_refs(&temp_dir, temp_dir_len + 1, &tail);
	strbuf_setlen(&temp_dir, temp_dir_len);

	tail = &dummy;
	strbuf_addstr(&temp_dir, "/packed-refs");
	insert_packed_refs(temp_dir.buf, &tail);
	strbuf_setlen(&temp_dir, temp_dir_len);

	if (remove_dir_recursively(&temp_dir, 0))
		warning ("Error removing temporary directory %s.",
				temp_dir.buf);

	strbuf_release(&buf);
	strbuf_release(&temp_dir);

	return dummy.next;
}