}

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

static void replace_parents(struct strbuf *buf, int argc, const char **argv)
{
	struct strbuf new_parents = STRBUF_INIT;
	const char *parent_start, *parent_end;
	int i;

	/* find existing parents */
	parent_start = buf->buf;
	parent_start += GIT_SHA1_HEXSZ + 6; /* "tree " + "hex sha1" + "\n" */
	parent_end = parent_start;

	while (starts_with(parent_end, "parent "))
		parent_end += 48; /* "parent " + "hex sha1" + "\n" */

	/* prepare new parents */
	for (i = 0; i < argc; i++) {
		struct object_id oid;
		if (get_oid(argv[i], &oid) < 0)
			die(_("Not a valid object name: '%s'"), argv[i]);
		lookup_commit_or_die(oid.hash, argv[i]);
		strbuf_addf(&new_parents, "parent %s\n", oid_to_hex(&oid));
	}

	/* replace existing parents with new ones */
	strbuf_splice(buf, parent_start - buf->buf, parent_end - parent_start,
		      new_parents.buf, new_parents.len);

