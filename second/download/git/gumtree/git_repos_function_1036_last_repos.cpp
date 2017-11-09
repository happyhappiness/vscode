static inline void oidcpy(struct object_id *dst, const struct object_id *src)
{
	hashcpy(dst->hash, src->hash);
}