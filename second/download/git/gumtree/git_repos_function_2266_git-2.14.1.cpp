int sha1_object_info(const unsigned char *sha1, unsigned long *sizep)
{
	enum object_type type;
	struct object_info oi = OBJECT_INFO_INIT;

	oi.typep = &type;
	oi.sizep = sizep;
	if (sha1_object_info_extended(sha1, &oi,
				      OBJECT_INFO_LOOKUP_REPLACE) < 0)
		return -1;
	return type;
}