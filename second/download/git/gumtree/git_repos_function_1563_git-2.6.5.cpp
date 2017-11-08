static void insert_obj_hash(struct object *obj, struct object **hash, unsigned int size)
{
	unsigned int j = hash_obj(obj->sha1, size);

	while (hash[j]) {
		j++;
		if (j >= size)
			j = 0;
	}
	hash[j] = obj;
}