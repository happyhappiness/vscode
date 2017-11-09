static inline void oidclr(struct object_id *oid)
{
	hashclr(oid->hash);
}