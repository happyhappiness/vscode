static void read_loose_refs(const char *dirname, struct ref_dir *dir)
{
	struct ref_cache *refs = dir->ref_cache;
	DIR *d;
	const char *path;
	struct dirent *de;
	int dirnamelen = strlen(dirname);
	struct strbuf refname;

	if (*refs->name)
		path = git_path_submodule(refs->name, "%s", dirname);
	else
		path = git_path("%s", dirname);

	d = opendir(path);
	if (!d)
		return;

	strbuf_init(&refname, dirnamelen + 257);
	strbuf_add(&refname, dirname, dirnamelen);

	while ((de = readdir(d)) != NULL) {
		unsigned char sha1[20];
		struct stat st;
		int flag;
		const char *refdir;

		if (de->d_name[0] == '.')
			continue;
		if (ends_with(de->d_name, ".lock"))
			continue;
		strbuf_addstr(&refname, de->d_name);
		refdir = *refs->name
			? git_path_submodule(refs->name, "%s", refname.buf)
			: git_path("%s", refname.buf);
		if (stat(refdir, &st) < 0) {
			; /* silently ignore */
		} else if (S_ISDIR(st.st_mode)) {
			strbuf_addch(&refname, '/');
			add_entry_to_dir(dir,
					 create_dir_entry(refs, refname.buf,
							  refname.len, 1));
		} else {
			int read_ok;

			if (*refs->name) {
				hashclr(sha1);
				flag = 0;
				read_ok = !resolve_gitlink_ref(refs->name,
							       refname.buf, sha1);
			} else {
				read_ok = !read_ref_full(refname.buf,
							 RESOLVE_REF_READING,
							 sha1, &flag);
			}

			if (!read_ok) {
				hashclr(sha1);
				flag |= REF_ISBROKEN;
			} else if (is_null_sha1(sha1)) {
				/*
				 * It is so astronomically unlikely
				 * that NULL_SHA1 is the SHA-1 of an
				 * actual object that we consider its
				 * appearance in a loose reference
				 * file to be repo corruption
				 * (probably due to a software bug).
				 */
				flag |= REF_ISBROKEN;
			}

			if (check_refname_format(refname.buf,
						 REFNAME_ALLOW_ONELEVEL)) {
				if (!refname_is_safe(refname.buf))
					die("loose refname is dangerous: %s", refname.buf);
				hashclr(sha1);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			add_entry_to_dir(dir,
					 create_ref_entry(refname.buf, sha1, flag, 0));
		}
		strbuf_setlen(&refname, dirnamelen);
	}
	strbuf_release(&refname);
	closedir(d);
}