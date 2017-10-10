	}
}

static void clear_loose_ref_cache(struct files_ref_store *refs)
{
	if (refs->loose) {
		free_ref_entry(refs->loose);
		refs->loose = NULL;
	}
}

/*
 * Create a new submodule ref cache and add it to the internal
 * set of caches.
 */
static struct ref_store *files_ref_store_create(const char *submodule)
{
	struct files_ref_store *refs = xcalloc(1, sizeof(*refs));
	struct ref_store *ref_store = (struct ref_store *)refs;

	base_ref_store_init(ref_store, &refs_be_files, submodule);

	return ref_store;
}

/*
 * Downcast ref_store to files_ref_store. Die if ref_store is not a
 * files_ref_store. If submodule_allowed is not true, then also die if
 * files_ref_store is for a submodule (i.e., not for the main
 * repository). caller is used in any necessary error messages.
 */
static struct files_ref_store *files_downcast(
		struct ref_store *ref_store, int submodule_allowed,
		const char *caller)
{
	if (ref_store->be != &refs_be_files)
		die("BUG: ref_store is type \"%s\" not \"files\" in %s",
		    ref_store->be->name, caller);

	if (!submodule_allowed)
		assert_main_repository(ref_store, caller);

	return (struct files_ref_store *)ref_store;
}

/* The length of a peeled reference line in packed-refs, including EOL: */
#define PEELED_LINE_LENGTH 42

/*
