static struct merge_list *link_entry(unsigned stage, const struct traverse_info *info, struct name_entry *n, struct merge_list *entry)
{
	const char *path;
	struct merge_list *link;

	if (!n->mode)
		return entry;
	if (entry)
		path = entry->path;
	else
		path = traverse_path(info, n);
	link = create_entry(stage, n->mode, n->oid, path);
	link->link = entry;
	return link;
}