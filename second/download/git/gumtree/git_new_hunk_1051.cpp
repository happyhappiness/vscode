		error("%s does not point to a valid object!", refname);
		return 0;
	}
	return 1;
}

struct packed_ref_cache {
	struct ref_cache *cache;

	/*
	 * Count of references to the data structure in this instance,
	 * including the pointer from files_ref_store::packed if any.
	 * The data will not be freed as long as the reference count
	 * is nonzero.
