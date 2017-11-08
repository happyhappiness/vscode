static unsigned int hash_obj(const struct object *obj, unsigned int n)
{
	return sha1hash(obj->oid.hash) % n;
}