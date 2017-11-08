static int use_wt_file(const char *workdir, const char *name,
		       struct object_id *oid)
{
	struct strbuf buf = STRBUF_INIT;
	struct stat st;
	int use = 0;

	strbuf_addstr(&buf, workdir);
	add_path(&buf, buf.len, name);

	if (!lstat(buf.buf, &st) && !S_ISLNK(st.st_mode)) {
		struct object_id wt_oid;
		int fd = open(buf.buf, O_RDONLY);

		if (fd >= 0 &&
		    !index_fd(wt_oid.hash, fd, &st, OBJ_BLOB, name, 0)) {
			if (is_null_oid(oid)) {
				oidcpy(oid, &wt_oid);
				use = 1;
			} else if (!oidcmp(oid, &wt_oid))
				use = 1;
		}
	}

	strbuf_release(&buf);

	return use;
}