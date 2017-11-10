struct packed_git *add_packed_git(const char *path, size_t path_len, int local)
{
	static int have_set_try_to_free_routine;
	struct stat st;
	size_t alloc;
	struct packed_git *p;

	if (!have_set_try_to_free_routine) {
		have_set_try_to_free_routine = 1;
		set_try_to_free_routine(try_to_free_pack_memory);
	}

	/*
	 * Make sure a corresponding .pack file exists and that
	 * the index looks sane.
	 */
	if (!strip_suffix_mem(path, &path_len, ".idx"))
		return NULL;

	/*
	 * ".pack" is long enough to hold any suffix we're adding (and
	 * the use xsnprintf double-checks that)
	 */
	alloc = st_add3(path_len, strlen(".pack"), 1);
	p = alloc_packed_git(alloc);
	memcpy(p->pack_name, path, path_len);

	xsnprintf(p->pack_name + path_len, alloc - path_len, ".keep");
	if (!access(p->pack_name, F_OK))
		p->pack_keep = 1;

	xsnprintf(p->pack_name + path_len, alloc - path_len, ".pack");
	if (stat(p->pack_name, &st) || !S_ISREG(st.st_mode)) {
		free(p);
		return NULL;
	}

	/* ok, it looks sane as far as we can check without
	 * actually mapping the pack file.
	 */
	p->pack_size = st.st_size;
	p->pack_local = local;
	p->mtime = st.st_mtime;
	if (path_len < 40 || get_sha1_hex(path + path_len - 40, p->sha1))
		hashclr(p->sha1);
	return p;
}