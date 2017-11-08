static inline const unsigned char *lookup_replace_object_extended(const unsigned char *sha1, unsigned flag)
{
	if (!(flag & LOOKUP_REPLACE_OBJECT))
		return sha1;
	return lookup_replace_object(sha1);
}