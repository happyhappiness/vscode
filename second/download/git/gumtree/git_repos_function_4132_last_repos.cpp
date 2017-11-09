void adjust_dirname_case(struct index_state *istate, char *name)
{
	const char *startPtr = name;
	const char *ptr = startPtr;

	lazy_init_name_hash(istate);
	while (*ptr) {
		while (*ptr && *ptr != '/')
			ptr++;

		if (*ptr == '/') {
			struct dir_entry *dir;

			ptr++;
			dir = find_dir_entry(istate, name, ptr - name + 1);
			if (dir) {
				memcpy((void *)startPtr, dir->name + (startPtr - name), ptr - startPtr);
				startPtr = ptr;
			}
		}
	}
}