static struct merge_list *create_entry(unsigned stage, unsigned mode, const unsigned char *sha1, const char *path)
{
	struct merge_list *res = xcalloc(1, sizeof(*res));

	res->stage = stage;
	res->path = path;
	res->mode = mode;
	res->blob = lookup_blob(sha1);
	return res;
}