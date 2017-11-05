static int dir_entry_cmp(const struct dir_entry *e1,
		const struct dir_entry *e2, const char *name)
{
	return e1->namelen != e2->namelen || strncasecmp(e1->name,
			name ? name : e2->name, e1->namelen);
}