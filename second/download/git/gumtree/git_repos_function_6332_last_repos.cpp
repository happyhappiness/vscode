static void export_object(const struct object_id *oid, enum object_type type,
			  int raw, const char *filename)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		die_errno("unable to open %s for writing", filename);

	argv_array_push(&cmd.args, "--no-replace-objects");
	argv_array_push(&cmd.args, "cat-file");
	if (raw)
		argv_array_push(&cmd.args, typename(type));
	else
		argv_array_push(&cmd.args, "-p");
	argv_array_push(&cmd.args, oid_to_hex(oid));
	cmd.git_cmd = 1;
	cmd.out = fd;

	if (run_command(&cmd))
		die("cat-file reported failure");
}