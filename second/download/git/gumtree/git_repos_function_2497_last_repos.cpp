static enum path_treatment treat_path(struct dir_struct *dir,
				      struct untracked_cache_dir *untracked,
				      struct cached_dir *cdir,
				      struct index_state *istate,
				      struct strbuf *path,
				      int baselen,
				      const struct pathspec *pathspec)
{
	int dtype;
	struct dirent *de = cdir->de;

	if (!de)
		return treat_path_fast(dir, untracked, cdir, istate, path,
				       baselen, pathspec);
	if (is_dot_or_dotdot(de->d_name) || !strcmp(de->d_name, ".git"))
		return path_none;
	strbuf_setlen(path, baselen);
	strbuf_addstr(path, de->d_name);
	if (simplify_away(path->buf, path->len, pathspec))
		return path_none;

	dtype = DTYPE(de);
	return treat_one_path(dir, untracked, istate, path, baselen, pathspec, dtype, de);
}