		}
	}

	strbuf_release(&line);
}

/*
 * Get the packed_ref_cache for the specified files_ref_store,
 * creating it if necessary.
 */
static struct packed_ref_cache *get_packed_ref_cache(struct files_ref_store *refs)
{
	char *packed_refs_file;

	if (*refs->base.submodule)
		packed_refs_file = git_pathdup_submodule(refs->base.submodule,
							 "packed-refs");
	else
		packed_refs_file = git_pathdup("packed-refs");

	if (refs->packed &&
	    !stat_validity_check(&refs->packed->validity, packed_refs_file))
		clear_packed_ref_cache(refs);

	if (!refs->packed) {
		FILE *f;

		refs->packed = xcalloc(1, sizeof(*refs->packed));
		acquire_packed_ref_cache(refs->packed);
		refs->packed->root = create_dir_entry(refs, "", 0, 0);
		f = fopen(packed_refs_file, "r");
		if (f) {
			stat_validity_update(&refs->packed->validity, fileno(f));
			read_packed_refs(f, get_ref_dir(refs->packed->root));
			fclose(f);
		}
	}
	free(packed_refs_file);
	return refs->packed;
}

static struct ref_dir *get_packed_ref_dir(struct packed_ref_cache *packed_ref_cache)
{
	return get_ref_dir(packed_ref_cache->root);
}

static struct ref_dir *get_packed_refs(struct files_ref_store *refs)
{
	return get_packed_ref_dir(get_packed_ref_cache(refs));
}
