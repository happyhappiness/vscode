		die("unresolved deltas left after unpacking");
}

int cmd_unpack_objects(int argc, const char **argv, const char *prefix)
{
	int i;
	struct object_id oid;

	check_replace_refs = 0;

	git_config(git_default_config, NULL);

	quiet = !isatty(2);
