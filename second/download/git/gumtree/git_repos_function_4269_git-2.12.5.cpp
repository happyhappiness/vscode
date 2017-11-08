void set_alternate_shallow_file(const char *path, int override)
{
	if (is_shallow != -1)
		die("BUG: is_repository_shallow must not be called before set_alternate_shallow_file");
	if (alternate_shallow_file && !override)
		return;
	free(alternate_shallow_file);
	alternate_shallow_file = xstrdup_or_null(path);
}