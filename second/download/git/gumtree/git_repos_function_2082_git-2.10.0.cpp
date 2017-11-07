static enum path_treatment treat_path_fast(struct dir_struct *dir,
					   struct untracked_cache_dir *untracked,
					   struct cached_dir *cdir,
					   struct strbuf *path,
					   int baselen,
					   const struct path_simplify *simplify)
{
	strbuf_setlen(path, baselen);
	if (!cdir->ucd) {
		strbuf_addstr(path, cdir->file);
		return path_untracked;
	}
	strbuf_addstr(path, cdir->ucd->name);
	/* treat_one_path() does this before it calls treat_directory() */
	strbuf_complete(path, '/');
	if (cdir->ucd->check_only)
		/*
		 * check_only is set as a result of treat_directory() getting
		 * to its bottom. Verify again the same set of directories
		 * with check_only set.
		 */
		return read_directory_recursive(dir, path->buf, path->len,
						cdir->ucd, 1, simplify);
	/*
	 * We get path_recurse in the first run when
	 * directory_exists_in_index() returns index_nonexistent. We
	 * are sure that new changes in the index does not impact the
	 * outcome. Return now.
	 */
	return path_recurse;
}