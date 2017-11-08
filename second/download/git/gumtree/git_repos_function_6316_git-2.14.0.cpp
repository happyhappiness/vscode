static int edit_and_replace(const char *object_ref, int force, int raw)
{
	char *tmpfile = git_pathdup("REPLACE_EDITOBJ");
	enum object_type type;
	struct object_id old, new, prev;
	struct strbuf ref = STRBUF_INIT;

	if (get_oid(object_ref, &old) < 0)
		die("Not a valid object name: '%s'", object_ref);

	type = sha1_object_info(old.hash, NULL);
	if (type < 0)
		die("unable to get object type for %s", oid_to_hex(&old));

	check_ref_valid(&old, &prev, &ref, force);
	strbuf_release(&ref);

	export_object(&old, type, raw, tmpfile);
	if (launch_editor(tmpfile, NULL, NULL) < 0)
		die("editing object file failed");
	import_object(&new, type, raw, tmpfile);

	free(tmpfile);

	if (!oidcmp(&old, &new))
		return error("new object is the same as the old one: '%s'", oid_to_hex(&old));

	return replace_object_oid(object_ref, &old, "replacement", &new, force);
}