static int compare_ref_delta_bases(const unsigned char *sha1,
				   const unsigned char *sha2,
				   enum object_type type1,
				   enum object_type type2)
{
	int cmp = type1 - type2;
	if (cmp)
		return cmp;
	return hashcmp(sha1, sha2);
}