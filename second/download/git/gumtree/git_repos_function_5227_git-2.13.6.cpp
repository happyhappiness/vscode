static const char *blob_path(struct object_array_entry *entry)
{
	return entry->path ? entry->path : entry->name;
}