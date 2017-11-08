int submodule_touches_in_range(struct object_id *excl_oid,
			       struct object_id *incl_oid)
{
	struct string_list subs = STRING_LIST_INIT_DUP;
	struct argv_array args = ARGV_ARRAY_INIT;
	int ret;

	gitmodules_config();
	/* No need to check if there are no submodules configured */
	if (!submodule_from_path(NULL, NULL))
		return 0;

	argv_array_push(&args, "--"); /* args[0] program name */
	argv_array_push(&args, oid_to_hex(incl_oid));
	argv_array_push(&args, "--not");
	argv_array_push(&args, oid_to_hex(excl_oid));

	collect_changed_submodules(&subs, &args);
	ret = subs.nr;

	argv_array_clear(&args);

	free_submodules_oids(&subs);
	return ret;
}