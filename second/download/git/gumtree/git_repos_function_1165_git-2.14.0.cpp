static int oidset_hashcmp(const void *unused_cmp_data,
			  const void *va, const void *vb,
			  const void *vkey)
{
	const struct oidset_entry *a = va, *b = vb;
	const struct object_id *key = vkey;
	return oidcmp(&a->oid, key ? key : &b->oid);
}