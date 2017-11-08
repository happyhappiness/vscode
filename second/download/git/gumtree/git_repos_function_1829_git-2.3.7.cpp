static enum path_treatment treat_path(struct dir_struct *dir,
				      struct dirent *de,
				      struct strbuf *path,
				      int baselen,
				      const struct path_simplify *simplify)
{
	int dtype;

	if (is_dot_or_dotdot(de->d_name) || !strcmp(de->d_name, ".git"))
		return path_none;
	strbuf_setlen(path, baselen);
	strbuf_addstr(path, de->d_name);
	if (simplify_away(path->buf, path->len, simplify))
		return path_none;

	dtype = DTYPE(de);
	return treat_one_path(dir, path, simplify, dtype, de);
}