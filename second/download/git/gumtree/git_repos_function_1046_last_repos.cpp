static inline const unsigned char *lookup_replace_object(const unsigned char *sha1)
{
	if (!check_replace_refs)
		return sha1;
	return do_lookup_replace_object(sha1);
}