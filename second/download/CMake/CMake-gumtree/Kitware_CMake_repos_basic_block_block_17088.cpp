{
	struct sparse_block *sb;

	sb = (struct sparse_block *)malloc(sizeof(*sb));
	if (sb == NULL)
		return (ARCHIVE_FATAL);
	sb->next = NULL;
	sb->is_hole = is_hole;
	sb->offset = offset;
	sb->remaining = length;
	if (pax->sparse_list == NULL || pax->sparse_tail == NULL)
		pax->sparse_list = pax->sparse_tail = sb;
	else {
		pax->sparse_tail->next = sb;
		pax->sparse_tail = sb;
	}
	return (ARCHIVE_OK);
}