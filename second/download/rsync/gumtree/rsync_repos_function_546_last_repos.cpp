int flist_find_name(struct file_list *flist, const char *fname, int want_dir_match)
{
	struct { /* We have to create a temporary file_struct for the search. */
		struct file_struct f;
		char name_space[MAXPATHLEN];
	} t;
	char fbuf[MAXPATHLEN];
	const char *slash = strrchr(fname, '/');
	const char *basename = slash ? slash+1 : fname;

	memset(&t.f, 0, FILE_STRUCT_LEN);
	memcpy((void *)t.f.basename, basename, strlen(basename)+1);

	if (slash) {
		strlcpy(fbuf, fname, slash - fname + 1);
		t.f.dirname = fbuf;
	} else
		t.f.dirname = NULL;

	t.f.mode = want_dir_match > 0 ? S_IFDIR : S_IFREG;

	if (want_dir_match < 0)
		return flist_find_ignore_dirness(flist, &t.f);
	return flist_find(flist, &t.f);
}