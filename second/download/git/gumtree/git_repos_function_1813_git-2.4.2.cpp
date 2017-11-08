int add_excludes_from_file_to_list(const char *fname,
				   const char *base,
				   int baselen,
				   struct exclude_list *el,
				   int check_index)
{
	struct stat st;
	int fd, i, lineno = 1;
	size_t size = 0;
	char *buf, *entry;

	fd = open(fname, O_RDONLY);
	if (fd < 0 || fstat(fd, &st) < 0) {
		if (errno != ENOENT)
			warn_on_inaccessible(fname);
		if (0 <= fd)
			close(fd);
		if (!check_index ||
		    (buf = read_skip_worktree_file_from_index(fname, &size)) == NULL)
			return -1;
		if (size == 0) {
			free(buf);
			return 0;
		}
		if (buf[size-1] != '\n') {
			buf = xrealloc(buf, size+1);
			buf[size++] = '\n';
		}
	} else {
		size = xsize_t(st.st_size);
		if (size == 0) {
			close(fd);
			return 0;
		}
		buf = xmalloc(size+1);
		if (read_in_full(fd, buf, size) != size) {
			free(buf);
			close(fd);
			return -1;
		}
		buf[size++] = '\n';
		close(fd);
	}

	el->filebuf = buf;

	if (skip_utf8_bom(&buf, size))
		size -= buf - el->filebuf;

	entry = buf;

	for (i = 0; i < size; i++) {
		if (buf[i] == '\n') {
			if (entry != buf + i && entry[0] != '#') {
				buf[i - (i && buf[i-1] == '\r')] = 0;
				trim_trailing_spaces(entry);
				add_exclude(entry, base, baselen, el, lineno);
			}
			lineno++;
			entry = buf + i + 1;
		}
	}
	return 0;
}