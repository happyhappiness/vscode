static inline int are_same_oid(struct name_entry *name_j, struct name_entry *name_k)
{
	return name_j->oid && name_k->oid && !oidcmp(name_j->oid, name_k->oid);
}