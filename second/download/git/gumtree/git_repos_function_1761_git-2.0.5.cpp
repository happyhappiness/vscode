static unsigned int hash_obj(const struct object *obj, unsigned int n)
{
	unsigned int hash;

	memcpy(&hash, obj->sha1, sizeof(unsigned int));
	return hash % n;
}