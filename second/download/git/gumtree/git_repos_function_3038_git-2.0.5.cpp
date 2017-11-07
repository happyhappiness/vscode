static inline khint_t __kh_oid_hash(const unsigned char *oid)
{
	khint_t hash;
	memcpy(&hash, oid, sizeof(hash));
	return hash;
}