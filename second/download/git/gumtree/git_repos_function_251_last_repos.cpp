static int ext_index_add_object(struct object *object, const char *name)
{
	struct eindex *eindex = &bitmap_git.ext_index;

	khiter_t hash_pos;
	int hash_ret;
	int bitmap_pos;

	hash_pos = kh_put_sha1_pos(eindex->positions, object->oid.hash, &hash_ret);
	if (hash_ret > 0) {
		if (eindex->count >= eindex->alloc) {
			eindex->alloc = (eindex->alloc + 16) * 3 / 2;
			REALLOC_ARRAY(eindex->objects, eindex->alloc);
			REALLOC_ARRAY(eindex->hashes, eindex->alloc);
		}

		bitmap_pos = eindex->count;
		eindex->objects[eindex->count] = object;
		eindex->hashes[eindex->count] = pack_name_hash(name);
		kh_value(eindex->positions, hash_pos) = bitmap_pos;
		eindex->count++;
	} else {
		bitmap_pos = kh_value(eindex->positions, hash_pos);
	}

	return bitmap_pos + bitmap_git.pack->num_objects;
}