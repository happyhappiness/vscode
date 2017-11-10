static void flush_current_id(int patchlen, struct object_id *id, struct object_id *result)
{
	char name[50];

	if (!patchlen)
		return;

	memcpy(name, oid_to_hex(id), GIT_SHA1_HEXSZ + 1);
	printf("%s %s\n", oid_to_hex(result), name);
}