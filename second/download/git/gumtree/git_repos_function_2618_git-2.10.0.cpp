static int parse_ref(char *path_to_ref, struct strbuf *ref, int *is_detached)
{
	if (is_detached)
		*is_detached = 0;
	if (!strbuf_readlink(ref, path_to_ref, 0)) {
		/* HEAD is symbolic link */
		if (!starts_with(ref->buf, "refs/") ||
				check_refname_format(ref->buf, 0))
			return -1;
	} else if (strbuf_read_file(ref, path_to_ref, 0) >= 0) {
		/* textual symref or detached */
		if (!starts_with(ref->buf, "ref:")) {
			if (is_detached)
				*is_detached = 1;
		} else {
			strbuf_remove(ref, 0, strlen("ref:"));
			strbuf_trim(ref);
			if (check_refname_format(ref->buf, 0))
				return -1;
		}
	} else
		return -1;
	return 0;
}