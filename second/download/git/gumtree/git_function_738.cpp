void read_mmblob(mmfile_t *ptr, const unsigned char *sha1)
{
	unsigned long size;
	enum object_type type;

	if (!hashcmp(sha1, null_sha1)) {
		ptr->ptr = xstrdup("");
		ptr->size = 0;
		return;
	}

	ptr->ptr = read_sha1_file(sha1, &type, &size);
	if (!ptr->ptr || type != OBJ_BLOB)
		die("unable to read blob object %s", sha1_to_hex(sha1));
	ptr->size = size;
}