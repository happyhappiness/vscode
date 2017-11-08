static void convert_binary_sha1(void *buffer)
{
	struct entry *entry = convert_entry(buffer);
	hashcpy(buffer, entry->new_sha1);
}