tatic int edit_and_replace(const char *object_ref, int force, int raw)
{
	char *tmpfile = git_pathdup("REPLACE_EDITOBJ");
	enum object_type type;
	unsigned char old[20], new[20], prev[20];
	char ref[PATH_MAX];

	if (get_sha1(object_ref, old) < 0)
		die("Not a valid object name: '%s'", object_ref);

	type = sha1_object_info(old, NULL);
	if (type < 0)
		die("unable to get object type for %s", sha1_to_hex(old));

	check_ref_valid(old, prev, ref, sizeof(ref), force);

	export_object(old, type, raw, tmpfile);
	if (launch_editor(tmpfile, NULL, NULL) < 0)
		die("editing object file failed");
	import_object(new, type, raw, tmpfile);

	free(tmpfile);

	if (!hashcmp(old, new))
		return error("new object is the same as the old one: '%s'", sha1_to_hex(old));

	return replace_object_sha1(object_ref, old, "replacement", new, force);
}