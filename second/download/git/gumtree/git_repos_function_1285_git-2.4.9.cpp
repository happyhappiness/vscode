static char* make_fast_import_path(const char *path)
{
	struct strbuf abs_path = STRBUF_INIT;

	if (!relative_marks_paths || is_absolute_path(path))
		return xstrdup(path);
	strbuf_addf(&abs_path, "%s/info/fast-import/%s", get_git_dir(), path);
	return strbuf_detach(&abs_path, NULL);
}