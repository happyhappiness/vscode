	argv_array_push(&rsync.args, get_object_directory());

	/* NEEDSWORK: handle one level of alternates */
	return run_command(&rsync);
}

static int write_one_ref(const char *name, const struct object_id *oid,
			 int flags, void *data)
{
	struct strbuf *buf = data;
	int len = buf->len;

	/* when called via for_each_ref(), flags is non-zero */
	if (flags && !starts_with(name, "refs/heads/") &&
			!starts_with(name, "refs/tags/"))
		return 0;

	strbuf_addstr(buf, name);
	if (safe_create_leading_directories(buf->buf) ||
	    write_file(buf->buf, 0, "%s\n", oid_to_hex(oid)))
		return error("problems writing temporary file %s: %s",
			     buf->buf, strerror(errno));
	strbuf_setlen(buf, len);
	return 0;
}

static int write_refs_to_temp_dir(struct strbuf *temp_dir,
				  int refspec_nr, const char **refspec)
{
	int i;

	for (i = 0; i < refspec_nr; i++) {
		struct object_id oid;
		char *ref;

		if (dwim_ref(refspec[i], strlen(refspec[i]), oid.hash, &ref) != 1)
			return error("Could not get ref %s", refspec[i]);

		if (write_one_ref(ref, &oid, 0, temp_dir)) {
			free(ref);
			return -1;
		}
		free(ref);
	}
	return 0;
