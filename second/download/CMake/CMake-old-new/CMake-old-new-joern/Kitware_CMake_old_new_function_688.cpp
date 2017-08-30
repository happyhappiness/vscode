static int
parse_device(struct archive *a, struct archive_entry *entry, char *val)
{
	char *comma1, *comma2;

	comma1 = strchr(val, ',');
	if (comma1 == NULL) {
		archive_entry_set_dev(entry, (dev_t)mtree_atol10(&val));
		return (ARCHIVE_OK);
	}
	++comma1;
	comma2 = strchr(comma1, ',');
	if (comma2 == NULL) {
		archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Malformed device attribute");
		return (ARCHIVE_WARN);
	}
	++comma2;
	archive_entry_set_rdevmajor(entry, (dev_t)mtree_atol(&comma1));
	archive_entry_set_rdevminor(entry, (dev_t)mtree_atol(&comma2));
	return (ARCHIVE_OK);
}