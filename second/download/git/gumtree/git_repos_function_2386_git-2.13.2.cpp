int check_dir_entry_contains(const struct dir_entry *out, const struct dir_entry *in)
{
	return (out->len < in->len) &&
		(out->name[out->len - 1] == '/') &&
		!memcmp(out->name, in->name, out->len);
}