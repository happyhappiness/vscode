	}
}

static void clear_loose_ref_cache(struct files_ref_store *refs)
{
	if (refs->loose) {
		free_ref_cache(refs->loose);
		refs->loose = NULL;
	}
}

/*
 * Create a new submodule ref cache and add it to the internal
 * set of caches.
 */
static struct ref_store *files_ref_store_create(const char *gitdir,
						unsigned int flags)
{
	struct files_ref_store *refs = xcalloc(1, sizeof(*refs));
	struct ref_store *ref_store = (struct ref_store *)refs;
	struct strbuf sb = STRBUF_INIT;

	base_ref_store_init(ref_store, &refs_be_files);
	refs->store_flags = flags;

	refs->gitdir = xstrdup(gitdir);
	get_common_dir_noenv(&sb, gitdir);
	refs->gitcommondir = strbuf_detach(&sb, NULL);
	strbuf_addf(&sb, "%s/packed-refs", refs->gitcommondir);
	refs->packed_refs_path = strbuf_detach(&sb, NULL);

	return ref_store;
}

/*
 * Die if refs is not the main ref store. caller is used in any
 * necessary error messages.
 */
static void files_assert_main_repository(struct files_ref_store *refs,
					 const char *caller)
{
	if (refs->store_flags & REF_STORE_MAIN)
		return;

	die("BUG: operation %s only allowed for main ref store", caller);
}

/*
 * Downcast ref_store to files_ref_store. Die if ref_store is not a
 * files_ref_store. required_flags is compared with ref_store's
 * store_flags to ensure the ref_store has all required capabilities.
 * "caller" is used in any necessary error messages.
 */
static struct files_ref_store *files_downcast(struct ref_store *ref_store,
					      unsigned int required_flags,
					      const char *caller)
{
	struct files_ref_store *refs;

	if (ref_store->be != &refs_be_files)
		die("BUG: ref_store is type \"%s\" not \"files\" in %s",
		    ref_store->be->name, caller);

	refs = (struct files_ref_store *)ref_store;

	if ((refs->store_flags & required_flags) != required_flags)
		die("BUG: operation %s requires abilities 0x%x, but only have 0x%x",
		    caller, required_flags, refs->store_flags);

	return refs;
}

/* The length of a peeled reference line in packed-refs, including EOL: */
#define PEELED_LINE_LENGTH 42

/*
