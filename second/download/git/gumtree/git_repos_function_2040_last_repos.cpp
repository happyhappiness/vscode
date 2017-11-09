void *create_object(const unsigned char *sha1, void *o)
{
	struct object *obj = o;

	obj->parsed = 0;
	obj->flags = 0;
	hashcpy(obj->oid.hash, sha1);

	if (obj_hash_size - 1 <= nr_objs * 2)
		grow_object_hash();

	insert_obj_hash(obj, obj_hash, obj_hash_size);
	nr_objs++;
	return obj;
}