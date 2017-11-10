void clear_object_flags(unsigned flags)
{
	int i;

	for (i=0; i < obj_hash_size; i++) {
		struct object *obj = obj_hash[i];
		if (obj)
			obj->flags &= ~flags;
	}
}