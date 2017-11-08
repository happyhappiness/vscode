static void *read_object(const unsigned char *sha1, enum object_type *type,
			 unsigned long *size)
{
	struct object_info oi = OBJECT_INFO_INIT;
	void *content;
	oi.typep = type;
	oi.sizep = size;
	oi.contentp = &content;

	if (sha1_object_info_extended(sha1, &oi, 0) < 0)
		return NULL;
	return content;
}