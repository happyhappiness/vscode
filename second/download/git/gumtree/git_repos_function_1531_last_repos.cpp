int parse_blob_buffer(struct blob *item, void *buffer, unsigned long size)
{
	item->object.parsed = 1;
	return 0;
}