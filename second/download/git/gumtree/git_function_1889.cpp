static void flush_current_id(int patchlen, unsigned char *id, unsigned char *result)
{
	char name[50];

	if (!patchlen)
		return;

	memcpy(name, sha1_to_hex(id), 41);
	printf("%s %s\n", sha1_to_hex(result), name);
}