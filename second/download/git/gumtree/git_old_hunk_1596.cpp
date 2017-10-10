{
	struct stat st;
	FILE *f;
	size_t sz;

	if (stat(filename, &st))
		return error("Could not stat %s", filename);
	if ((f = fopen(filename, "rb")) == NULL)
		return error("Could not open %s", filename);
	sz = xsize_t(st.st_size);
	ptr->ptr = xmalloc(sz ? sz : 1);
	if (sz && fread(ptr->ptr, sz, 1, f) != 1) {
		fclose(f);
		return error("Could not read %s", filename);
	}
