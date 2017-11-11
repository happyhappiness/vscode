static int treat_leading_path(struct dir_struct *dir,
			      const char *path, int len,
			      const struct path_simplify *simplify)
{
	struct strbuf sb = STRBUF_INIT;
	int baselen, rc = 0;
	const char *cp;
	int old_flags = dir->flags;

	while (len && path[len - 1] == '/')
		len--;
	if (!len)
		return 1;
	baselen = 0;
	dir->flags &= ~DIR_SHOW_OTHER_DIRECTORIES;
	while (1) {
		cp = path + baselen + !!baselen;
		cp = memchr(cp, '/', path + len - cp);
		if (!cp)
			baselen = len;
		else
			baselen = cp - path;
		strbuf_setlen(&sb, 0);
		strbuf_add(&sb, path, baselen);
		if (!is_directory(sb.buf))
			break;
		if (simplify_away(sb.buf, sb.len, simplify))
			break;
		if (treat_one_path(dir, NULL, &sb, baselen, simplify,
				   DT_DIR, NULL) == path_none)
			break; /* do not recurse into it */
		if (len <= baselen) {
			rc = 1;
			break; /* finished checking */
		}
	}
	strbuf_release(&sb);
	dir->flags = old_flags;
	return rc;
}