static int add_excludes(const char *fname, const char *base, int baselen,
			struct exclude_list *el, int check_index,
			struct sha1_stat *sha1_stat)
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
		    (buf = read_skip_worktree_file_from_index(fname, &size, sha1_stat)) == NULL)
			return -1;
		if (size == 0) {
			free(buf);
			return 0;
		}
		if (buf[size-1] != '\n') {
			buf = xrealloc(buf, st_add(size, 1));
			buf[size++] = '\n';
		}
	} else {
		size = xsize_t(st.st_size);
		if (size == 0) {
			if (sha1_stat) {
				fill_stat_data(&sha1_stat->stat, &st);
				hashcpy(sha1_stat->sha1, EMPTY_BLOB_SHA1_BIN);
				sha1_stat->valid = 1;
			}
			close(fd);
			return 0;
		}
		buf = xmallocz(size);
		if (read_in_full(fd, buf, size) != size) {
			free(buf);
			close(fd);
			return -1;
		}
		buf[size++] = '\n';
		close(fd);
		if (sha1_stat) {
			int pos;
			if (sha1_stat->valid &&
			    !match_stat_data_racy(&the_index, &sha1_stat->stat, &st))
				; /* no content change, ss->sha1 still good */
			else if (check_index &&
				 (pos = cache_name_pos(fname, strlen(fname))) >= 0 &&
				 !ce_stage(active_cache[pos]) &&
				 ce_uptodate(active_cache[pos]) &&
				 !would_convert_to_git(fname))
				hashcpy(sha1_stat->sha1,
					active_cache[pos]->oid.hash);
			else
				hash_sha1_file(buf, size, "blob", sha1_stat->sha1);
			fill_stat_data(&sha1_stat->stat, &st);
			sha1_stat->valid = 1;
		}
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