static struct dir_entry *dir_entry_new(const char *pathname, int len)
{
	struct dir_entry *ent;

	FLEX_ALLOC_MEM(ent, name, pathname, len);
	ent->len = len;
	return ent;
}