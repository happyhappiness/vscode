		die("BUG: unknown ref type %d of ref %s",
		    ref_type(refname), refname);
	}
}

/*
 * Get the packed_ref_cache for the specified files_ref_store,
 * creating it if necessary.
 */
static struct packed_ref_cache *get_packed_ref_cache(struct files_ref_store *refs)
{
	const char *packed_refs_file = files_packed_refs_path(refs);

	if (refs->packed &&
	    !stat_validity_check(&refs->packed->validity, packed_refs_file))
		clear_packed_ref_cache(refs);

	if (!refs->packed) {
		FILE *f;

		refs->packed = xcalloc(1, sizeof(*refs->packed));
		acquire_packed_ref_cache(refs->packed);
		refs->packed->cache = create_ref_cache(&refs->base, NULL);
		refs->packed->cache->root->flag &= ~REF_INCOMPLETE;
		f = fopen(packed_refs_file, "r");
		if (f) {
			stat_validity_update(&refs->packed->validity, fileno(f));
			read_packed_refs(f, get_ref_dir(refs->packed->cache->root));
			fclose(f);
		}
	}
	return refs->packed;
}

static struct ref_dir *get_packed_ref_dir(struct packed_ref_cache *packed_ref_cache)
{
	return get_ref_dir(packed_ref_cache->cache->root);
