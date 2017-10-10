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

/*
 * Read a previously-exported (and possibly edited) object back from "filename",
 * interpreting it as "type", and writing the result to the object database.
 * The sha1 of the written object is returned via sha1.
 */
static void import_object(struct object_id *oid, enum object_type type,
			  int raw, const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
