static void prepare_packed_git_one(char *objdir, int local)
{
	struct strbuf path = STRBUF_INIT;
	size_t dirnamelen;
	DIR *dir;
	struct dirent *de;
	struct string_list garbage = STRING_LIST_INIT_DUP;

	strbuf_addstr(&path, objdir);
	strbuf_addstr(&path, "/pack");
	dir = opendir(path.buf);
	if (!dir) {
		if (errno != ENOENT)
			error("unable to open object pack directory: %s: %s",
			      path.buf, strerror(errno));
		strbuf_release(&path);
		return;
	}
	strbuf_addch(&path, '/');
	dirnamelen = path.len;
	while ((de = readdir(dir)) != NULL) {
		struct packed_git *p;
		size_t base_len;

		if (is_dot_or_dotdot(de->d_name))
			continue;

		strbuf_setlen(&path, dirnamelen);
		strbuf_addstr(&path, de->d_name);

		base_len = path.len;
		if (strip_suffix_mem(path.buf, &base_len, ".idx")) {
			/* Don't reopen a pack we already have. */
			for (p = packed_git; p; p = p->next) {
				size_t len;
				if (strip_suffix(p->pack_name, ".pack", &len) &&
				    len == base_len &&
				    !memcmp(p->pack_name, path.buf, len))
					break;
			}
			if (p == NULL &&
			    /*
			     * See if it really is a valid .idx file with
			     * corresponding .pack file that we can map.
			     */
			    (p = add_packed_git(path.buf, path.len, local)) != NULL)
				install_packed_git(p);
		}

		if (!report_garbage)
			continue;

		if (ends_with(de->d_name, ".idx") ||
		    ends_with(de->d_name, ".pack") ||
		    ends_with(de->d_name, ".bitmap") ||
		    ends_with(de->d_name, ".keep"))
			string_list_append(&garbage, path.buf);
		else
			report_garbage(PACKDIR_FILE_GARBAGE, path.buf);
	}
	closedir(dir);
	report_pack_garbage(&garbage);
	string_list_clear(&garbage, 0);
	strbuf_release(&path);
}