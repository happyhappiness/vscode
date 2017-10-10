{
	if (is_shallow != -1)
		die("BUG: is_repository_shallow must not be called before set_alternate_shallow_file");
	if (alternate_shallow_file && !override)
		return;
	free(alternate_shallow_file);
	alternate_shallow_file = path ? xstrdup(path) : NULL;
}

int register_shallow(const unsigned char *sha1)
{
	struct commit_graft *graft =
		xmalloc(sizeof(struct commit_graft));
