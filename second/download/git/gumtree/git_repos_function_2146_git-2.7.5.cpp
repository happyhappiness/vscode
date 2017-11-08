static int fetch_objs_via_rsync(struct transport *transport,
				int nr_objs, struct ref **to_fetch)
{
	struct child_process rsync = CHILD_PROCESS_INIT;

	rsync.stdout_to_stderr = 1;
	argv_array_push(&rsync.args, "rsync");
	argv_array_push(&rsync.args, (transport->verbose > 1) ? "-rv" : "-r");
	argv_array_push(&rsync.args, "--ignore-existing");
	argv_array_push(&rsync.args, "--exclude");
	argv_array_push(&rsync.args, "info");
	argv_array_pushf(&rsync.args, "%s/objects/", rsync_url(transport->url));
	argv_array_push(&rsync.args, get_object_directory());

	/* NEEDSWORK: handle one level of alternates */
	return run_command(&rsync);
}