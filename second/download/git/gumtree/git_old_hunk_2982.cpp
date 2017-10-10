			return 0;
		refname++;
	}
	return 1;
}

static struct ref_entry *create_ref_entry(const char *refname,
					  const unsigned char *sha1, int flag,
					  int check_name)
{
	int len;
	struct ref_entry *ref;

	if (check_name &&
	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
		die("Reference has invalid format: '%s'", refname);
	len = strlen(refname) + 1;
	ref = xmalloc(sizeof(struct ref_entry) + len);
	hashcpy(ref->u.value.oid.hash, sha1);
	oidclr(&ref->u.value.peeled);
	memcpy(ref->name, refname, len);
	ref->flag = flag;
	return ref;
}

static void clear_ref_dir(struct ref_dir *dir);

static void free_ref_entry(struct ref_entry *entry)
{
	if (entry->flag & REF_DIR) {
		/*
		 * Do not use get_ref_dir() here, as that might
		 * trigger the reading of loose refs.
		 */
		clear_ref_dir(&entry->u.subdir);
	}
	free(entry);
}

/*
 * Add a ref_entry to the end of dir (unsorted).  Entry is always
 * stored directly in dir; no recursion into subdirectories is
 * done.
 */
static void add_entry_to_dir(struct ref_dir *dir, struct ref_entry *entry)
{
	ALLOC_GROW(dir->entries, dir->nr + 1, dir->alloc);
	dir->entries[dir->nr++] = entry;
	/* optimize for the case that entries are added in order */
	if (dir->nr == 1 ||
	    (dir->nr == dir->sorted + 1 &&
	     strcmp(dir->entries[dir->nr - 2]->name,
		    dir->entries[dir->nr - 1]->name) < 0))
		dir->sorted = dir->nr;
}

/*
 * Clear and free all entries in dir, recursively.
 */
static void clear_ref_dir(struct ref_dir *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++)
		free_ref_entry(dir->entries[i]);
	free(dir->entries);
	dir->sorted = dir->nr = dir->alloc = 0;
	dir->entries = NULL;
}

/*
 * Create a struct ref_entry object for the specified dirname.
 * dirname is the name of the directory with a trailing slash (e.g.,
 * "refs/heads/") or "" for the top-level directory.
 */
static struct ref_entry *create_dir_entry(struct ref_cache *ref_cache,
					  const char *dirname, size_t len,
					  int incomplete)
{
	struct ref_entry *direntry;
	direntry = xcalloc(1, sizeof(struct ref_entry) + len + 1);
	memcpy(direntry->name, dirname, len);
	direntry->name[len] = '\0';
	direntry->u.subdir.ref_cache = ref_cache;
	direntry->flag = REF_DIR | (incomplete ? REF_INCOMPLETE : 0);
	return direntry;
}

static int ref_entry_cmp(const void *a, const void *b)
{
	struct ref_entry *one = *(struct ref_entry **)a;
	struct ref_entry *two = *(struct ref_entry **)b;
	return strcmp(one->name, two->name);
}

static void sort_ref_dir(struct ref_dir *dir);

struct string_slice {
	size_t len;
	const char *str;
};

static int ref_entry_cmp_sslice(const void *key_, const void *ent_)
{
	const struct string_slice *key = key_;
	const struct ref_entry *ent = *(const struct ref_entry * const *)ent_;
	int cmp = strncmp(key->str, ent->name, key->len);
	if (cmp)
		return cmp;
	return '\0' - (unsigned char)ent->name[key->len];
}

/*
 * Return the index of the entry with the given refname from the
 * ref_dir (non-recursively), sorting dir if necessary.  Return -1 if
 * no such entry is found.  dir must already be complete.
 */
static int search_ref_dir(struct ref_dir *dir, const char *refname, size_t len)
{
	struct ref_entry **r;
	struct string_slice key;

	if (refname == NULL || !dir->nr)
		return -1;

	sort_ref_dir(dir);
	key.len = len;
	key.str = refname;
	r = bsearch(&key, dir->entries, dir->nr, sizeof(*dir->entries),
		    ref_entry_cmp_sslice);

	if (r == NULL)
		return -1;

	return r - dir->entries;
}

/*
 * Search for a directory entry directly within dir (without
 * recursing).  Sort dir if necessary.  subdirname must be a directory
 * name (i.e., end in '/').  If mkdir is set, then create the
 * directory if it is missing; otherwise, return NULL if the desired
 * directory cannot be found.  dir must already be complete.
 */
static struct ref_dir *search_for_subdir(struct ref_dir *dir,
					 const char *subdirname, size_t len,
					 int mkdir)
{
	int entry_index = search_ref_dir(dir, subdirname, len);
	struct ref_entry *entry;
	if (entry_index == -1) {
		if (!mkdir)
			return NULL;
		/*
		 * Since dir is complete, the absence of a subdir
		 * means that the subdir really doesn't exist;
		 * therefore, create an empty record for it but mark
		 * the record complete.
		 */
		entry = create_dir_entry(dir->ref_cache, subdirname, len, 0);
		add_entry_to_dir(dir, entry);
	} else {
		entry = dir->entries[entry_index];
	}
	return get_ref_dir(entry);
}

/*
 * If refname is a reference name, find the ref_dir within the dir
 * tree that should hold refname.  If refname is a directory name
 * (i.e., ends in '/'), then return that ref_dir itself.  dir must
 * represent the top-level directory and must already be complete.
 * Sort ref_dirs and recurse into subdirectories as necessary.  If
 * mkdir is set, then create any missing directories; otherwise,
 * return NULL if the desired directory cannot be found.
 */
static struct ref_dir *find_containing_dir(struct ref_dir *dir,
					   const char *refname, int mkdir)
{
	const char *slash;
	for (slash = strchr(refname, '/'); slash; slash = strchr(slash + 1, '/')) {
		size_t dirnamelen = slash - refname + 1;
		struct ref_dir *subdir;
		subdir = search_for_subdir(dir, refname, dirnamelen, mkdir);
		if (!subdir) {
			dir = NULL;
			break;
		}
		dir = subdir;
	}

	return dir;
}

/*
 * Find the value entry with the given name in dir, sorting ref_dirs
 * and recursing into subdirectories as necessary.  If the name is not
 * found or it corresponds to a directory entry, return NULL.
 */
static struct ref_entry *find_ref(struct ref_dir *dir, const char *refname)
{
	int entry_index;
	struct ref_entry *entry;
	dir = find_containing_dir(dir, refname, 0);
	if (!dir)
		return NULL;
	entry_index = search_ref_dir(dir, refname, strlen(refname));
	if (entry_index == -1)
		return NULL;
	entry = dir->entries[entry_index];
	return (entry->flag & REF_DIR) ? NULL : entry;
}

/*
 * Remove the entry with the given name from dir, recursing into
 * subdirectories as necessary.  If refname is the name of a directory
 * (i.e., ends with '/'), then remove the directory and its contents.
 * If the removal was successful, return the number of entries
 * remaining in the directory entry that contained the deleted entry.
 * If the name was not found, return -1.  Please note that this
 * function only deletes the entry from the cache; it does not delete
 * it from the filesystem or ensure that other cache entries (which
 * might be symbolic references to the removed entry) are updated.
 * Nor does it remove any containing dir entries that might be made
 * empty by the removal.  dir must represent the top-level directory
 * and must already be complete.
 */
static int remove_entry(struct ref_dir *dir, const char *refname)
{
	int refname_len = strlen(refname);
	int entry_index;
	struct ref_entry *entry;
	int is_dir = refname[refname_len - 1] == '/';
	if (is_dir) {
		/*
		 * refname represents a reference directory.  Remove
		 * the trailing slash; otherwise we will get the
		 * directory *representing* refname rather than the
		 * one *containing* it.
		 */
		char *dirname = xmemdupz(refname, refname_len - 1);
		dir = find_containing_dir(dir, dirname, 0);
		free(dirname);
	} else {
		dir = find_containing_dir(dir, refname, 0);
	}
	if (!dir)
		return -1;
	entry_index = search_ref_dir(dir, refname, refname_len);
	if (entry_index == -1)
		return -1;
	entry = dir->entries[entry_index];

	memmove(&dir->entries[entry_index],
		&dir->entries[entry_index + 1],
		(dir->nr - entry_index - 1) * sizeof(*dir->entries)
		);
	dir->nr--;
	if (dir->sorted > entry_index)
		dir->sorted--;
	free_ref_entry(entry);
	return dir->nr;
}

/*
 * Add a ref_entry to the ref_dir (unsorted), recursing into
 * subdirectories as necessary.  dir must represent the top-level
 * directory.  Return 0 on success.
 */
static int add_ref(struct ref_dir *dir, struct ref_entry *ref)
{
	dir = find_containing_dir(dir, ref->name, 1);
	if (!dir)
		return -1;
	add_entry_to_dir(dir, ref);
	return 0;
}

/*
 * Emit a warning and return true iff ref1 and ref2 have the same name
 * and the same sha1.  Die if they have the same name but different
 * sha1s.
 */
static int is_dup_ref(const struct ref_entry *ref1, const struct ref_entry *ref2)
{
	if (strcmp(ref1->name, ref2->name))
		return 0;

	/* Duplicate name; make sure that they don't conflict: */

	if ((ref1->flag & REF_DIR) || (ref2->flag & REF_DIR))
		/* This is impossible by construction */
		die("Reference directory conflict: %s", ref1->name);

	if (oidcmp(&ref1->u.value.oid, &ref2->u.value.oid))
		die("Duplicated ref, and SHA1s don't match: %s", ref1->name);

	warning("Duplicated ref: %s", ref1->name);
	return 1;
}

/*
 * Sort the entries in dir non-recursively (if they are not already
 * sorted) and remove any duplicate entries.
 */
static void sort_ref_dir(struct ref_dir *dir)
{
	int i, j;
	struct ref_entry *last = NULL;

	/*
	 * This check also prevents passing a zero-length array to qsort(),
	 * which is a problem on some platforms.
	 */
	if (dir->sorted == dir->nr)
		return;

	qsort(dir->entries, dir->nr, sizeof(*dir->entries), ref_entry_cmp);

	/* Remove any duplicates: */
	for (i = 0, j = 0; j < dir->nr; j++) {
		struct ref_entry *entry = dir->entries[j];
		if (last && is_dup_ref(last, entry))
			free_ref_entry(entry);
		else
			last = dir->entries[i++] = entry;
	}
	dir->sorted = dir->nr = i;
}

/* Include broken references in a do_for_each_ref*() iteration: */
#define DO_FOR_EACH_INCLUDE_BROKEN 0x01

/*
 * Return true iff the reference described by entry can be resolved to
 * an object in the database.  Emit a warning if the referred-to
 * object does not exist.
 */
static int ref_resolves_to_object(struct ref_entry *entry)
{
	if (entry->flag & REF_ISBROKEN)
		return 0;
	if (!has_sha1_file(entry->u.value.oid.hash)) {
		error("%s does not point to a valid object!", entry->name);
		return 0;
	}
	return 1;
}

/*
 * current_ref is a performance hack: when iterating over references
 * using the for_each_ref*() functions, current_ref is set to the
 * current reference's entry before calling the callback function.  If
 * the callback function calls peel_ref(), then peel_ref() first
 * checks whether the reference to be peeled is the current reference
 * (it usually is) and if so, returns that reference's peeled version
 * if it is available.  This avoids a refname lookup in a common case.
 */
static struct ref_entry *current_ref;

typedef int each_ref_entry_fn(struct ref_entry *entry, void *cb_data);

struct ref_entry_cb {
	const char *base;
	int trim;
	int flags;
	each_ref_fn *fn;
	void *cb_data;
};

/*
 * Handle one reference in a do_for_each_ref*()-style iteration,
 * calling an each_ref_fn for each entry.
 */
static int do_one_ref(struct ref_entry *entry, void *cb_data)
{
	struct ref_entry_cb *data = cb_data;
	struct ref_entry *old_current_ref;
	int retval;

	if (!starts_with(entry->name, data->base))
		return 0;

	if (!(data->flags & DO_FOR_EACH_INCLUDE_BROKEN) &&
	      !ref_resolves_to_object(entry))
		return 0;

	/* Store the old value, in case this is a recursive call: */
	old_current_ref = current_ref;
	current_ref = entry;
	retval = data->fn(entry->name + data->trim, &entry->u.value.oid,
			  entry->flag, data->cb_data);
	current_ref = old_current_ref;
	return retval;
}

/*
 * Call fn for each reference in dir that has index in the range
 * offset <= index < dir->nr.  Recurse into subdirectories that are in
 * that index range, sorting them before iterating.  This function
 * does not sort dir itself; it should be sorted beforehand.  fn is
 * called for all references, including broken ones.
 */
static int do_for_each_entry_in_dir(struct ref_dir *dir, int offset,
				    each_ref_entry_fn fn, void *cb_data)
{
	int i;
	assert(dir->sorted == dir->nr);
	for (i = offset; i < dir->nr; i++) {
		struct ref_entry *entry = dir->entries[i];
		int retval;
		if (entry->flag & REF_DIR) {
			struct ref_dir *subdir = get_ref_dir(entry);
			sort_ref_dir(subdir);
			retval = do_for_each_entry_in_dir(subdir, 0, fn, cb_data);
		} else {
			retval = fn(entry, cb_data);
		}
		if (retval)
			return retval;
	}
	return 0;
}

/*
 * Call fn for each reference in the union of dir1 and dir2, in order
 * by refname.  Recurse into subdirectories.  If a value entry appears
 * in both dir1 and dir2, then only process the version that is in
 * dir2.  The input dirs must already be sorted, but subdirs will be
 * sorted as needed.  fn is called for all references, including
 * broken ones.
 */
static int do_for_each_entry_in_dirs(struct ref_dir *dir1,
				     struct ref_dir *dir2,
				     each_ref_entry_fn fn, void *cb_data)
{
	int retval;
	int i1 = 0, i2 = 0;

	assert(dir1->sorted == dir1->nr);
	assert(dir2->sorted == dir2->nr);
	while (1) {
		struct ref_entry *e1, *e2;
		int cmp;
		if (i1 == dir1->nr) {
			return do_for_each_entry_in_dir(dir2, i2, fn, cb_data);
		}
		if (i2 == dir2->nr) {
			return do_for_each_entry_in_dir(dir1, i1, fn, cb_data);
		}
		e1 = dir1->entries[i1];
		e2 = dir2->entries[i2];
		cmp = strcmp(e1->name, e2->name);
		if (cmp == 0) {
			if ((e1->flag & REF_DIR) && (e2->flag & REF_DIR)) {
				/* Both are directories; descend them in parallel. */
				struct ref_dir *subdir1 = get_ref_dir(e1);
				struct ref_dir *subdir2 = get_ref_dir(e2);
				sort_ref_dir(subdir1);
				sort_ref_dir(subdir2);
				retval = do_for_each_entry_in_dirs(
						subdir1, subdir2, fn, cb_data);
				i1++;
				i2++;
			} else if (!(e1->flag & REF_DIR) && !(e2->flag & REF_DIR)) {
				/* Both are references; ignore the one from dir1. */
				retval = fn(e2, cb_data);
				i1++;
				i2++;
			} else {
				die("conflict between reference and directory: %s",
				    e1->name);
			}
		} else {
			struct ref_entry *e;
			if (cmp < 0) {
				e = e1;
				i1++;
			} else {
				e = e2;
				i2++;
			}
			if (e->flag & REF_DIR) {
				struct ref_dir *subdir = get_ref_dir(e);
				sort_ref_dir(subdir);
				retval = do_for_each_entry_in_dir(
						subdir, 0, fn, cb_data);
			} else {
				retval = fn(e, cb_data);
			}
		}
		if (retval)
			return retval;
	}
}

/*
 * Load all of the refs from the dir into our in-memory cache. The hard work
 * of loading loose refs is done by get_ref_dir(), so we just need to recurse
 * through all of the sub-directories. We do not even need to care about
 * sorting, as traversal order does not matter to us.
 */
static void prime_ref_dir(struct ref_dir *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++) {
		struct ref_entry *entry = dir->entries[i];
		if (entry->flag & REF_DIR)
			prime_ref_dir(get_ref_dir(entry));
	}
}

struct nonmatching_ref_data {
	const struct string_list *skip;
	const char *conflicting_refname;
};

static int nonmatching_ref_fn(struct ref_entry *entry, void *vdata)
{
	struct nonmatching_ref_data *data = vdata;

	if (data->skip && string_list_has_string(data->skip, entry->name))
		return 0;

	data->conflicting_refname = entry->name;
	return 1;
}

/*
 * Return 0 if a reference named refname could be created without
 * conflicting with the name of an existing reference in dir.
 * Otherwise, return a negative value and write an explanation to err.
 * If extras is non-NULL, it is a list of additional refnames with
 * which refname is not allowed to conflict. If skip is non-NULL,
 * ignore potential conflicts with refs in skip (e.g., because they
 * are scheduled for deletion in the same operation). Behavior is
 * undefined if the same name is listed in both extras and skip.
 *
 * Two reference names conflict if one of them exactly matches the
 * leading components of the other; e.g., "refs/foo/bar" conflicts
 * with both "refs/foo" and with "refs/foo/bar/baz" but not with
 * "refs/foo/bar" or "refs/foo/barbados".
 *
 * extras and skip must be sorted.
 */
static int verify_refname_available(const char *refname,
				    const struct string_list *extras,
				    const struct string_list *skip,
				    struct ref_dir *dir,
				    struct strbuf *err)
{
	const char *slash;
	int pos;
	struct strbuf dirname = STRBUF_INIT;
	int ret = -1;

	/*
	 * For the sake of comments in this function, suppose that
	 * refname is "refs/foo/bar".
	 */

	assert(err);

	strbuf_grow(&dirname, strlen(refname) + 1);
	for (slash = strchr(refname, '/'); slash; slash = strchr(slash + 1, '/')) {
		/* Expand dirname to the new prefix, not including the trailing slash: */
		strbuf_add(&dirname, refname + dirname.len, slash - refname - dirname.len);

		/*
		 * We are still at a leading dir of the refname (e.g.,
		 * "refs/foo"; if there is a reference with that name,
		 * it is a conflict, *unless* it is in skip.
		 */
		if (dir) {
			pos = search_ref_dir(dir, dirname.buf, dirname.len);
			if (pos >= 0 &&
			    (!skip || !string_list_has_string(skip, dirname.buf))) {
				/*
				 * We found a reference whose name is
				 * a proper prefix of refname; e.g.,
				 * "refs/foo", and is not in skip.
				 */
				strbuf_addf(err, "'%s' exists; cannot create '%s'",
					    dirname.buf, refname);
				goto cleanup;
			}
		}

		if (extras && string_list_has_string(extras, dirname.buf) &&
		    (!skip || !string_list_has_string(skip, dirname.buf))) {
			strbuf_addf(err, "cannot process '%s' and '%s' at the same time",
				    refname, dirname.buf);
			goto cleanup;
		}

		/*
		 * Otherwise, we can try to continue our search with
		 * the next component. So try to look up the
		 * directory, e.g., "refs/foo/". If we come up empty,
		 * we know there is nothing under this whole prefix,
		 * but even in that case we still have to continue the
		 * search for conflicts with extras.
		 */
		strbuf_addch(&dirname, '/');
		if (dir) {
			pos = search_ref_dir(dir, dirname.buf, dirname.len);
			if (pos < 0) {
				/*
				 * There was no directory "refs/foo/",
				 * so there is nothing under this
				 * whole prefix. So there is no need
				 * to continue looking for conflicting
				 * references. But we need to continue
				 * looking for conflicting extras.
				 */
				dir = NULL;
			} else {
				dir = get_ref_dir(dir->entries[pos]);
			}
		}
	}

	/*
	 * We are at the leaf of our refname (e.g., "refs/foo/bar").
	 * There is no point in searching for a reference with that
	 * name, because a refname isn't considered to conflict with
	 * itself. But we still need to check for references whose
	 * names are in the "refs/foo/bar/" namespace, because they
	 * *do* conflict.
	 */
	strbuf_addstr(&dirname, refname + dirname.len);
	strbuf_addch(&dirname, '/');

	if (dir) {
		pos = search_ref_dir(dir, dirname.buf, dirname.len);

		if (pos >= 0) {
			/*
			 * We found a directory named "$refname/"
			 * (e.g., "refs/foo/bar/"). It is a problem
			 * iff it contains any ref that is not in
			 * "skip".
			 */
			struct nonmatching_ref_data data;

			data.skip = skip;
			data.conflicting_refname = NULL;
			dir = get_ref_dir(dir->entries[pos]);
			sort_ref_dir(dir);
			if (do_for_each_entry_in_dir(dir, 0, nonmatching_ref_fn, &data)) {
				strbuf_addf(err, "'%s' exists; cannot create '%s'",
					    data.conflicting_refname, refname);
				goto cleanup;
			}
		}
	}

	if (extras) {
		/*
		 * Check for entries in extras that start with
		 * "$refname/". We do that by looking for the place
		 * where "$refname/" would be inserted in extras. If
		 * there is an entry at that position that starts with
		 * "$refname/" and is not in skip, then we have a
		 * conflict.
		 */
		for (pos = string_list_find_insert_index(extras, dirname.buf, 0);
		     pos < extras->nr; pos++) {
			const char *extra_refname = extras->items[pos].string;

			if (!starts_with(extra_refname, dirname.buf))
				break;

			if (!skip || !string_list_has_string(skip, extra_refname)) {
				strbuf_addf(err, "cannot process '%s' and '%s' at the same time",
					    refname, extra_refname);
				goto cleanup;
			}
		}
	}

	/* No conflicts were found */
	ret = 0;

cleanup:
	strbuf_release(&dirname);
	return ret;
}

struct packed_ref_cache {
	struct ref_entry *root;

	/*
	 * Count of references to the data structure in this instance,
	 * including the pointer from ref_cache::packed if any.  The
	 * data will not be freed as long as the reference count is
	 * nonzero.
	 */
	unsigned int referrers;

	/*
	 * Iff the packed-refs file associated with this instance is
	 * currently locked for writing, this points at the associated
	 * lock (which is owned by somebody else).  The referrer count
	 * is also incremented when the file is locked and decremented
	 * when it is unlocked.
	 */
	struct lock_file *lock;

	/* The metadata from when this packed-refs cache was read */
	struct stat_validity validity;
};

/*
 * Future: need to be in "struct repository"
 * when doing a full libification.
 */
static struct ref_cache {
	struct ref_cache *next;
	struct ref_entry *loose;
	struct packed_ref_cache *packed;
	/*
	 * The submodule name, or "" for the main repo.  We allocate
	 * length 1 rather than FLEX_ARRAY so that the main ref_cache
	 * is initialized correctly.
	 */
	char name[1];
} ref_cache, *submodule_ref_caches;

/* Lock used for the main packed-refs file: */
static struct lock_file packlock;

/*
 * Increment the reference count of *packed_refs.
 */
static void acquire_packed_ref_cache(struct packed_ref_cache *packed_refs)
{
	packed_refs->referrers++;
}

/*
 * Decrease the reference count of *packed_refs.  If it goes to zero,
 * free *packed_refs and return true; otherwise return false.
 */
static int release_packed_ref_cache(struct packed_ref_cache *packed_refs)
{
	if (!--packed_refs->referrers) {
		free_ref_entry(packed_refs->root);
		stat_validity_clear(&packed_refs->validity);
		free(packed_refs);
		return 1;
	} else {
		return 0;
	}
}

static void clear_packed_ref_cache(struct ref_cache *refs)
{
	if (refs->packed) {
		struct packed_ref_cache *packed_refs = refs->packed;

		if (packed_refs->lock)
			die("internal error: packed-ref cache cleared while locked");
		refs->packed = NULL;
		release_packed_ref_cache(packed_refs);
	}
}

static void clear_loose_ref_cache(struct ref_cache *refs)
{
	if (refs->loose) {
		free_ref_entry(refs->loose);
		refs->loose = NULL;
	}
}

static struct ref_cache *create_ref_cache(const char *submodule)
{
	int len;
	struct ref_cache *refs;
	if (!submodule)
		submodule = "";
	len = strlen(submodule) + 1;
	refs = xcalloc(1, sizeof(struct ref_cache) + len);
	memcpy(refs->name, submodule, len);
	return refs;
}

/*
 * Return a pointer to a ref_cache for the specified submodule. For
 * the main repository, use submodule==NULL. The returned structure
 * will be allocated and initialized but not necessarily populated; it
 * should not be freed.
 */
static struct ref_cache *get_ref_cache(const char *submodule)
{
	struct ref_cache *refs;

	if (!submodule || !*submodule)
		return &ref_cache;

	for (refs = submodule_ref_caches; refs; refs = refs->next)
		if (!strcmp(submodule, refs->name))
			return refs;

	refs = create_ref_cache(submodule);
	refs->next = submodule_ref_caches;
	submodule_ref_caches = refs;
	return refs;
}

/* The length of a peeled reference line in packed-refs, including EOL: */
#define PEELED_LINE_LENGTH 42

/*
 * The packed-refs header line that we write out.  Perhaps other
 * traits will be added later.  The trailing space is required.
 */
static const char PACKED_REFS_HEADER[] =
	"# pack-refs with: peeled fully-peeled \n";

/*
 * Parse one line from a packed-refs file.  Write the SHA1 to sha1.
 * Return a pointer to the refname within the line (null-terminated),
 * or NULL if there was a problem.
 */
static const char *parse_ref_line(struct strbuf *line, unsigned char *sha1)
{
	const char *ref;

	/*
	 * 42: the answer to everything.
	 *
	 * In this case, it happens to be the answer to
	 *  40 (length of sha1 hex representation)
	 *  +1 (space in between hex and name)
	 *  +1 (newline at the end of the line)
	 */
	if (line->len <= 42)
		return NULL;

	if (get_sha1_hex(line->buf, sha1) < 0)
		return NULL;
	if (!isspace(line->buf[40]))
		return NULL;

	ref = line->buf + 41;
	if (isspace(*ref))
		return NULL;

	if (line->buf[line->len - 1] != '\n')
		return NULL;
	line->buf[--line->len] = 0;

	return ref;
}

/*
 * Read f, which is a packed-refs file, into dir.
 *
 * A comment line of the form "# pack-refs with: " may contain zero or
 * more traits. We interpret the traits as follows:
 *
 *   No traits:
 *
 *      Probably no references are peeled. But if the file contains a
 *      peeled value for a reference, we will use it.
 *
 *   peeled:
 *
 *      References under "refs/tags/", if they *can* be peeled, *are*
 *      peeled in this file. References outside of "refs/tags/" are
 *      probably not peeled even if they could have been, but if we find
 *      a peeled value for such a reference we will use it.
 *
 *   fully-peeled:
 *
 *      All references in the file that can be peeled are peeled.
 *      Inversely (and this is more important), any references in the
 *      file for which no peeled value is recorded is not peelable. This
 *      trait should typically be written alongside "peeled" for
 *      compatibility with older clients, but we do not require it
 *      (i.e., "peeled" is a no-op if "fully-peeled" is set).
 */
static void read_packed_refs(FILE *f, struct ref_dir *dir)
{
	struct ref_entry *last = NULL;
	struct strbuf line = STRBUF_INIT;
	enum { PEELED_NONE, PEELED_TAGS, PEELED_FULLY } peeled = PEELED_NONE;

	while (strbuf_getwholeline(&line, f, '\n') != EOF) {
		unsigned char sha1[20];
		const char *refname;
		const char *traits;

		if (skip_prefix(line.buf, "# pack-refs with:", &traits)) {
			if (strstr(traits, " fully-peeled "))
				peeled = PEELED_FULLY;
			else if (strstr(traits, " peeled "))
				peeled = PEELED_TAGS;
			/* perhaps other traits later as well */
			continue;
		}

		refname = parse_ref_line(&line, sha1);
		if (refname) {
			int flag = REF_ISPACKED;

			if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
				if (!refname_is_safe(refname))
					die("packed refname is dangerous: %s", refname);
				hashclr(sha1);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			last = create_ref_entry(refname, sha1, flag, 0);
			if (peeled == PEELED_FULLY ||
			    (peeled == PEELED_TAGS && starts_with(refname, "refs/tags/")))
				last->flag |= REF_KNOWS_PEELED;
			add_ref(dir, last);
			continue;
		}
		if (last &&
		    line.buf[0] == '^' &&
		    line.len == PEELED_LINE_LENGTH &&
		    line.buf[PEELED_LINE_LENGTH - 1] == '\n' &&
		    !get_sha1_hex(line.buf + 1, sha1)) {
			hashcpy(last->u.value.peeled.hash, sha1);
			/*
			 * Regardless of what the file header said,
			 * we definitely know the value of *this*
			 * reference:
			 */
			last->flag |= REF_KNOWS_PEELED;
		}
	}

	strbuf_release(&line);
}

/*
 * Get the packed_ref_cache for the specified ref_cache, creating it
 * if necessary.
 */
static struct packed_ref_cache *get_packed_ref_cache(struct ref_cache *refs)
{
	char *packed_refs_file;

	if (*refs->name)
		packed_refs_file = git_pathdup_submodule(refs->name, "packed-refs");
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

static struct ref_dir *get_packed_refs(struct ref_cache *refs)
{
	return get_packed_ref_dir(get_packed_ref_cache(refs));
}

/*
 * Add a reference to the in-memory packed reference cache.  This may
 * only be called while the packed-refs file is locked (see
 * lock_packed_refs()).  To actually write the packed-refs file, call
 * commit_packed_refs().
 */
static void add_packed_ref(const char *refname, const unsigned char *sha1)
{
	struct packed_ref_cache *packed_ref_cache =
		get_packed_ref_cache(&ref_cache);

	if (!packed_ref_cache->lock)
		die("internal error: packed refs not locked");
	add_ref(get_packed_ref_dir(packed_ref_cache),
		create_ref_entry(refname, sha1, REF_ISPACKED, 1));
}

/*
 * Read the loose references from the namespace dirname into dir
 * (without recursing).  dirname must end with '/'.  dir must be the
 * directory entry corresponding to dirname.
 */
static void read_loose_refs(const char *dirname, struct ref_dir *dir)
{
	struct ref_cache *refs = dir->ref_cache;
	DIR *d;
	struct dirent *de;
	int dirnamelen = strlen(dirname);
	struct strbuf refname;
	struct strbuf path = STRBUF_INIT;
	size_t path_baselen;

	if (*refs->name)
		strbuf_git_path_submodule(&path, refs->name, "%s", dirname);
	else
		strbuf_git_path(&path, "%s", dirname);
	path_baselen = path.len;

	d = opendir(path.buf);
	if (!d) {
		strbuf_release(&path);
		return;
	}

	strbuf_init(&refname, dirnamelen + 257);
	strbuf_add(&refname, dirname, dirnamelen);

	while ((de = readdir(d)) != NULL) {
		unsigned char sha1[20];
		struct stat st;
		int flag;

		if (de->d_name[0] == '.')
			continue;
		if (ends_with(de->d_name, ".lock"))
			continue;
		strbuf_addstr(&refname, de->d_name);
		strbuf_addstr(&path, de->d_name);
		if (stat(path.buf, &st) < 0) {
			; /* silently ignore */
		} else if (S_ISDIR(st.st_mode)) {
			strbuf_addch(&refname, '/');
			add_entry_to_dir(dir,
					 create_dir_entry(refs, refname.buf,
							  refname.len, 1));
		} else {
			int read_ok;

			if (*refs->name) {
				hashclr(sha1);
				flag = 0;
				read_ok = !resolve_gitlink_ref(refs->name,
							       refname.buf, sha1);
			} else {
				read_ok = !read_ref_full(refname.buf,
							 RESOLVE_REF_READING,
							 sha1, &flag);
			}

			if (!read_ok) {
				hashclr(sha1);
				flag |= REF_ISBROKEN;
			} else if (is_null_sha1(sha1)) {
				/*
				 * It is so astronomically unlikely
				 * that NULL_SHA1 is the SHA-1 of an
				 * actual object that we consider its
				 * appearance in a loose reference
				 * file to be repo corruption
				 * (probably due to a software bug).
				 */
				flag |= REF_ISBROKEN;
			}

			if (check_refname_format(refname.buf,
						 REFNAME_ALLOW_ONELEVEL)) {
				if (!refname_is_safe(refname.buf))
					die("loose refname is dangerous: %s", refname.buf);
				hashclr(sha1);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			add_entry_to_dir(dir,
					 create_ref_entry(refname.buf, sha1, flag, 0));
		}
		strbuf_setlen(&refname, dirnamelen);
		strbuf_setlen(&path, path_baselen);
	}
	strbuf_release(&refname);
	strbuf_release(&path);
	closedir(d);
}

static struct ref_dir *get_loose_refs(struct ref_cache *refs)
{
	if (!refs->loose) {
		/*
		 * Mark the top-level directory complete because we
		 * are about to read the only subdirectory that can
		 * hold references:
		 */
		refs->loose = create_dir_entry(refs, "", 0, 0);
		/*
		 * Create an incomplete entry for "refs/":
		 */
		add_entry_to_dir(get_ref_dir(refs->loose),
				 create_dir_entry(refs, "refs/", 5, 1));
	}
	return get_ref_dir(refs->loose);
}

/* We allow "recursive" symbolic refs. Only within reason, though */
#define MAXDEPTH 5
#define MAXREFLEN (1024)

/*
 * Called by resolve_gitlink_ref_recursive() after it failed to read
 * from the loose refs in ref_cache refs. Find <refname> in the
 * packed-refs file for the submodule.
 */
static int resolve_gitlink_packed_ref(struct ref_cache *refs,
				      const char *refname, unsigned char *sha1)
{
	struct ref_entry *ref;
	struct ref_dir *dir = get_packed_refs(refs);

	ref = find_ref(dir, refname);
	if (ref == NULL)
		return -1;

	hashcpy(sha1, ref->u.value.oid.hash);
	return 0;
}

static int resolve_gitlink_ref_recursive(struct ref_cache *refs,
					 const char *refname, unsigned char *sha1,
					 int recursion)
{
	int fd, len;
	char buffer[128], *p;
	char *path;

	if (recursion > MAXDEPTH || strlen(refname) > MAXREFLEN)
		return -1;
	path = *refs->name
		? git_pathdup_submodule(refs->name, "%s", refname)
		: git_pathdup("%s", refname);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd < 0)
		return resolve_gitlink_packed_ref(refs, refname, sha1);

	len = read(fd, buffer, sizeof(buffer)-1);
	close(fd);
	if (len < 0)
		return -1;
	while (len && isspace(buffer[len-1]))
		len--;
	buffer[len] = 0;

	/* Was it a detached head or an old-fashioned symlink? */
	if (!get_sha1_hex(buffer, sha1))
		return 0;

	/* Symref? */
	if (strncmp(buffer, "ref:", 4))
		return -1;
	p = buffer + 4;
	while (isspace(*p))
		p++;

	return resolve_gitlink_ref_recursive(refs, p, sha1, recursion+1);
}

int resolve_gitlink_ref(const char *path, const char *refname, unsigned char *sha1)
{
	int len = strlen(path), retval;
	char *submodule;
	struct ref_cache *refs;

	while (len && path[len-1] == '/')
		len--;
	if (!len)
		return -1;
	submodule = xstrndup(path, len);
	refs = get_ref_cache(submodule);
	free(submodule);

	retval = resolve_gitlink_ref_recursive(refs, refname, sha1, 0);
	return retval;
}

/*
 * Return the ref_entry for the given refname from the packed
 * references.  If it does not exist, return NULL.
 */
static struct ref_entry *get_packed_ref(const char *refname)
{
	return find_ref(get_packed_refs(&ref_cache), refname);
}

/*
 * A loose ref file doesn't exist; check for a packed ref.  The
 * options are forwarded from resolve_safe_unsafe().
 */
static int resolve_missing_loose_ref(const char *refname,
				     int resolve_flags,
				     unsigned char *sha1,
				     int *flags)
{
	struct ref_entry *entry;

	/*
	 * The loose reference file does not exist; check for a packed
	 * reference.
	 */
	entry = get_packed_ref(refname);
	if (entry) {
		hashcpy(sha1, entry->u.value.oid.hash);
		if (flags)
			*flags |= REF_ISPACKED;
		return 0;
	}
	/* The reference is not a packed reference, either. */
	if (resolve_flags & RESOLVE_REF_READING) {
		errno = ENOENT;
		return -1;
	} else {
		hashclr(sha1);
		return 0;
	}
}

/* This function needs to return a meaningful errno on failure */
static const char *resolve_ref_unsafe_1(const char *refname,
					int resolve_flags,
					unsigned char *sha1,
					int *flags,
					struct strbuf *sb_path)
{
	int depth = MAXDEPTH;
	ssize_t len;
	char buffer[256];
	static char refname_buffer[256];
	int bad_name = 0;

	if (flags)
		*flags = 0;

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
		if (flags)
			*flags |= REF_BAD_NAME;

		if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
		    !refname_is_safe(refname)) {
			errno = EINVAL;
			return NULL;
		}
		/*
		 * dwim_ref() uses REF_ISBROKEN to distinguish between
		 * missing refs and refs that were present but invalid,
		 * to complain about the latter to stderr.
		 *
		 * We don't know whether the ref exists, so don't set
		 * REF_ISBROKEN yet.
		 */
		bad_name = 1;
	}
	for (;;) {
		const char *path;
		struct stat st;
		char *buf;
		int fd;

		if (--depth < 0) {
			errno = ELOOP;
			return NULL;
		}

		strbuf_reset(sb_path);
		strbuf_git_path(sb_path, "%s", refname);
		path = sb_path->buf;

		/*
		 * We might have to loop back here to avoid a race
		 * condition: first we lstat() the file, then we try
		 * to read it as a link or as a file.  But if somebody
		 * changes the type of the file (file <-> directory
		 * <-> symlink) between the lstat() and reading, then
		 * we don't want to report that as an error but rather
		 * try again starting with the lstat().
		 */
	stat_ref:
		if (lstat(path, &st) < 0) {
			if (errno != ENOENT)
				return NULL;
			if (resolve_missing_loose_ref(refname, resolve_flags,
						      sha1, flags))
				return NULL;
			if (bad_name) {
				hashclr(sha1);
				if (flags)
					*flags |= REF_ISBROKEN;
			}
			return refname;
		}

		/* Follow "normalized" - ie "refs/.." symlinks by hand */
		if (S_ISLNK(st.st_mode)) {
			len = readlink(path, buffer, sizeof(buffer)-1);
			if (len < 0) {
				if (errno == ENOENT || errno == EINVAL)
					/* inconsistent with lstat; retry */
					goto stat_ref;
				else
					return NULL;
			}
			buffer[len] = 0;
			if (starts_with(buffer, "refs/") &&
					!check_refname_format(buffer, 0)) {
				strcpy(refname_buffer, buffer);
				refname = refname_buffer;
				if (flags)
					*flags |= REF_ISSYMREF;
				if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
					hashclr(sha1);
					return refname;
				}
				continue;
			}
		}

		/* Is it a directory? */
		if (S_ISDIR(st.st_mode)) {
			errno = EISDIR;
			return NULL;
		}

		/*
		 * Anything else, just open it and try to use it as
		 * a ref
		 */
		fd = open(path, O_RDONLY);
		if (fd < 0) {
			if (errno == ENOENT)
				/* inconsistent with lstat; retry */
				goto stat_ref;
			else
				return NULL;
		}
		len = read_in_full(fd, buffer, sizeof(buffer)-1);
		if (len < 0) {
			int save_errno = errno;
			close(fd);
			errno = save_errno;
			return NULL;
		}
		close(fd);
		while (len && isspace(buffer[len-1]))
			len--;
		buffer[len] = '\0';

		/*
		 * Is it a symbolic ref?
		 */
		if (!starts_with(buffer, "ref:")) {
			/*
			 * Please note that FETCH_HEAD has a second
			 * line containing other data.
			 */
			if (get_sha1_hex(buffer, sha1) ||
			    (buffer[40] != '\0' && !isspace(buffer[40]))) {
				if (flags)
					*flags |= REF_ISBROKEN;
				errno = EINVAL;
				return NULL;
			}
			if (bad_name) {
				hashclr(sha1);
				if (flags)
					*flags |= REF_ISBROKEN;
			}
			return refname;
		}
		if (flags)
			*flags |= REF_ISSYMREF;
		buf = buffer + 4;
		while (isspace(*buf))
			buf++;
		refname = strcpy(refname_buffer, buf);
		if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
			hashclr(sha1);
			return refname;
		}
		if (check_refname_format(buf, REFNAME_ALLOW_ONELEVEL)) {
			if (flags)
				*flags |= REF_ISBROKEN;

			if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
			    !refname_is_safe(buf)) {
				errno = EINVAL;
				return NULL;
			}
			bad_name = 1;
		}
	}
}

const char *resolve_ref_unsafe(const char *refname, int resolve_flags,
			       unsigned char *sha1, int *flags)
{
	struct strbuf sb_path = STRBUF_INIT;
	const char *ret = resolve_ref_unsafe_1(refname, resolve_flags,
					       sha1, flags, &sb_path);
	strbuf_release(&sb_path);
	return ret;
}

char *resolve_refdup(const char *refname, int resolve_flags,
		     unsigned char *sha1, int *flags)
{
	return xstrdup_or_null(resolve_ref_unsafe(refname, resolve_flags,
						  sha1, flags));
}

/* The argument to filter_refs */
struct ref_filter {
	const char *pattern;
	each_ref_fn *fn;
	void *cb_data;
};

int read_ref_full(const char *refname, int resolve_flags, unsigned char *sha1, int *flags)
{
	if (resolve_ref_unsafe(refname, resolve_flags, sha1, flags))
		return 0;
	return -1;
}

int read_ref(const char *refname, unsigned char *sha1)
{
	return read_ref_full(refname, RESOLVE_REF_READING, sha1, NULL);
}

int ref_exists(const char *refname)
{
	unsigned char sha1[20];
	return !!resolve_ref_unsafe(refname, RESOLVE_REF_READING, sha1, NULL);
}

static int filter_refs(const char *refname, const struct object_id *oid,
			   int flags, void *data)
{
	struct ref_filter *filter = (struct ref_filter *)data;

	if (wildmatch(filter->pattern, refname, 0, NULL))
		return 0;
	return filter->fn(refname, oid, flags, filter->cb_data);
}

enum peel_status {
	/* object was peeled successfully: */
	PEEL_PEELED = 0,

	/*
	 * object cannot be peeled because the named object (or an
	 * object referred to by a tag in the peel chain), does not
	 * exist.
	 */
	PEEL_INVALID = -1,

	/* object cannot be peeled because it is not a tag: */
	PEEL_NON_TAG = -2,

	/* ref_entry contains no peeled value because it is a symref: */
	PEEL_IS_SYMREF = -3,

	/*
	 * ref_entry cannot be peeled because it is broken (i.e., the
	 * symbolic reference cannot even be resolved to an object
	 * name):
	 */
	PEEL_BROKEN = -4
};

/*
 * Peel the named object; i.e., if the object is a tag, resolve the
 * tag recursively until a non-tag is found.  If successful, store the
 * result to sha1 and return PEEL_PEELED.  If the object is not a tag
 * or is not valid, return PEEL_NON_TAG or PEEL_INVALID, respectively,
 * and leave sha1 unchanged.
 */
static enum peel_status peel_object(const unsigned char *name, unsigned char *sha1)
{
	struct object *o = lookup_unknown_object(name);

	if (o->type == OBJ_NONE) {
		int type = sha1_object_info(name, NULL);
		if (type < 0 || !object_as_type(o, type, 0))
			return PEEL_INVALID;
	}

	if (o->type != OBJ_TAG)
		return PEEL_NON_TAG;

	o = deref_tag_noverify(o);
	if (!o)
		return PEEL_INVALID;

	hashcpy(sha1, o->sha1);
	return PEEL_PEELED;
}

/*
 * Peel the entry (if possible) and return its new peel_status.  If
 * repeel is true, re-peel the entry even if there is an old peeled
 * value that is already stored in it.
 *
 * It is OK to call this function with a packed reference entry that
 * might be stale and might even refer to an object that has since
 * been garbage-collected.  In such a case, if the entry has
 * REF_KNOWS_PEELED then leave the status unchanged and return
 * PEEL_PEELED or PEEL_NON_TAG; otherwise, return PEEL_INVALID.
 */
static enum peel_status peel_entry(struct ref_entry *entry, int repeel)
{
	enum peel_status status;

	if (entry->flag & REF_KNOWS_PEELED) {
		if (repeel) {
			entry->flag &= ~REF_KNOWS_PEELED;
			oidclr(&entry->u.value.peeled);
		} else {
			return is_null_oid(&entry->u.value.peeled) ?
				PEEL_NON_TAG : PEEL_PEELED;
		}
	}
	if (entry->flag & REF_ISBROKEN)
		return PEEL_BROKEN;
	if (entry->flag & REF_ISSYMREF)
		return PEEL_IS_SYMREF;

	status = peel_object(entry->u.value.oid.hash, entry->u.value.peeled.hash);
	if (status == PEEL_PEELED || status == PEEL_NON_TAG)
		entry->flag |= REF_KNOWS_PEELED;
	return status;
}

int peel_ref(const char *refname, unsigned char *sha1)
{
	int flag;
	unsigned char base[20];

	if (current_ref && (current_ref->name == refname
			    || !strcmp(current_ref->name, refname))) {
		if (peel_entry(current_ref, 0))
			return -1;
		hashcpy(sha1, current_ref->u.value.peeled.hash);
		return 0;
	}

	if (read_ref_full(refname, RESOLVE_REF_READING, base, &flag))
		return -1;

	/*
	 * If the reference is packed, read its ref_entry from the
	 * cache in the hope that we already know its peeled value.
	 * We only try this optimization on packed references because
	 * (a) forcing the filling of the loose reference cache could
	 * be expensive and (b) loose references anyway usually do not
	 * have REF_KNOWS_PEELED.
	 */
	if (flag & REF_ISPACKED) {
		struct ref_entry *r = get_packed_ref(refname);
		if (r) {
			if (peel_entry(r, 0))
				return -1;
			hashcpy(sha1, r->u.value.peeled.hash);
			return 0;
		}
	}

	return peel_object(base, sha1);
}

struct warn_if_dangling_data {
	FILE *fp;
	const char *refname;
	const struct string_list *refnames;
	const char *msg_fmt;
};

static int warn_if_dangling_symref(const char *refname, const struct object_id *oid,
				   int flags, void *cb_data)
{
	struct warn_if_dangling_data *d = cb_data;
	const char *resolves_to;
	struct object_id junk;

	if (!(flags & REF_ISSYMREF))
		return 0;

	resolves_to = resolve_ref_unsafe(refname, 0, junk.hash, NULL);
	if (!resolves_to
	    || (d->refname
		? strcmp(resolves_to, d->refname)
		: !string_list_has_string(d->refnames, resolves_to))) {
		return 0;
	}

	fprintf(d->fp, d->msg_fmt, refname);
	fputc('\n', d->fp);
	return 0;
}

void warn_dangling_symref(FILE *fp, const char *msg_fmt, const char *refname)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = refname;
	data.refnames = NULL;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}

void warn_dangling_symrefs(FILE *fp, const char *msg_fmt, const struct string_list *refnames)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = NULL;
	data.refnames = refnames;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}

/*
 * Call fn for each reference in the specified ref_cache, omitting
 * references not in the containing_dir of base.  fn is called for all
 * references, including broken ones.  If fn ever returns a non-zero
 * value, stop the iteration and return that value; otherwise, return
 * 0.
 */
static int do_for_each_entry(struct ref_cache *refs, const char *base,
			     each_ref_entry_fn fn, void *cb_data)
{
	struct packed_ref_cache *packed_ref_cache;
	struct ref_dir *loose_dir;
	struct ref_dir *packed_dir;
	int retval = 0;

	/*
	 * We must make sure that all loose refs are read before accessing the
	 * packed-refs file; this avoids a race condition in which loose refs
	 * are migrated to the packed-refs file by a simultaneous process, but
	 * our in-memory view is from before the migration. get_packed_ref_cache()
	 * takes care of making sure our view is up to date with what is on
	 * disk.
	 */
	loose_dir = get_loose_refs(refs);
	if (base && *base) {
		loose_dir = find_containing_dir(loose_dir, base, 0);
	}
	if (loose_dir)
		prime_ref_dir(loose_dir);

	packed_ref_cache = get_packed_ref_cache(refs);
	acquire_packed_ref_cache(packed_ref_cache);
	packed_dir = get_packed_ref_dir(packed_ref_cache);
	if (base && *base) {
		packed_dir = find_containing_dir(packed_dir, base, 0);
	}

	if (packed_dir && loose_dir) {
		sort_ref_dir(packed_dir);
		sort_ref_dir(loose_dir);
		retval = do_for_each_entry_in_dirs(
				packed_dir, loose_dir, fn, cb_data);
	} else if (packed_dir) {
		sort_ref_dir(packed_dir);
		retval = do_for_each_entry_in_dir(
				packed_dir, 0, fn, cb_data);
	} else if (loose_dir) {
		sort_ref_dir(loose_dir);
		retval = do_for_each_entry_in_dir(
				loose_dir, 0, fn, cb_data);
	}

	release_packed_ref_cache(packed_ref_cache);
	return retval;
}

/*
 * Call fn for each reference in the specified ref_cache for which the
 * refname begins with base.  If trim is non-zero, then trim that many
 * characters off the beginning of each refname before passing the
 * refname to fn.  flags can be DO_FOR_EACH_INCLUDE_BROKEN to include
 * broken references in the iteration.  If fn ever returns a non-zero
 * value, stop the iteration and return that value; otherwise, return
 * 0.
 */
static int do_for_each_ref(struct ref_cache *refs, const char *base,
			   each_ref_fn fn, int trim, int flags, void *cb_data)
{
	struct ref_entry_cb data;
	data.base = base;
	data.trim = trim;
	data.flags = flags;
	data.fn = fn;
	data.cb_data = cb_data;

	if (ref_paranoia < 0)
		ref_paranoia = git_env_bool("GIT_REF_PARANOIA", 0);
	if (ref_paranoia)
		data.flags |= DO_FOR_EACH_INCLUDE_BROKEN;

	return do_for_each_entry(refs, base, do_one_ref, &data);
}

static int do_head_ref(const char *submodule, each_ref_fn fn, void *cb_data)
{
	struct object_id oid;
	int flag;

	if (submodule) {
		if (resolve_gitlink_ref(submodule, "HEAD", oid.hash) == 0)
			return fn("HEAD", &oid, 0, cb_data);

		return 0;
	}

	if (!read_ref_full("HEAD", RESOLVE_REF_READING, oid.hash, &flag))
		return fn("HEAD", &oid, flag, cb_data);

	return 0;
}

int head_ref(each_ref_fn fn, void *cb_data)
{
	return do_head_ref(NULL, fn, cb_data);
}

int head_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return do_head_ref(submodule, fn, cb_data);
}

int for_each_ref(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(&ref_cache, "", fn, 0, 0, cb_data);
}

int for_each_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(get_ref_cache(submodule), "", fn, 0, 0, cb_data);
}

int for_each_ref_in(const char *prefix, each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(&ref_cache, prefix, fn, strlen(prefix), 0, cb_data);
}

int for_each_ref_in_submodule(const char *submodule, const char *prefix,
		each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(get_ref_cache(submodule), prefix, fn, strlen(prefix), 0, cb_data);
}

int for_each_tag_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/tags/", fn, cb_data);
}

int for_each_tag_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/tags/", fn, cb_data);
}

int for_each_branch_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/heads/", fn, cb_data);
}

int for_each_branch_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/heads/", fn, cb_data);
}

int for_each_remote_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/remotes/", fn, cb_data);
}

int for_each_remote_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/remotes/", fn, cb_data);
}

int for_each_replace_ref(each_ref_fn fn, void *cb_data)
{
	return do_for_each_ref(&ref_cache, git_replace_ref_base, fn,
			       strlen(git_replace_ref_base), 0, cb_data);
}

int head_ref_namespaced(each_ref_fn fn, void *cb_data)
{
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;
	struct object_id oid;
	int flag;

	strbuf_addf(&buf, "%sHEAD", get_git_namespace());
	if (!read_ref_full(buf.buf, RESOLVE_REF_READING, oid.hash, &flag))
		ret = fn(buf.buf, &oid, flag, cb_data);
	strbuf_release(&buf);

	return ret;
}

int for_each_namespaced_ref(each_ref_fn fn, void *cb_data)
{
	struct strbuf buf = STRBUF_INIT;
	int ret;
	strbuf_addf(&buf, "%srefs/", get_git_namespace());
	ret = do_for_each_ref(&ref_cache, buf.buf, fn, 0, 0, cb_data);
	strbuf_release(&buf);
	return ret;
}

int for_each_glob_ref_in(each_ref_fn fn, const char *pattern,
	const char *prefix, void *cb_data)
{
	struct strbuf real_pattern = STRBUF_INIT;
	struct ref_filter filter;
	int ret;

	if (!prefix && !starts_with(pattern, "refs/"))
		strbuf_addstr(&real_pattern, "refs/");
	else if (prefix)
		strbuf_addstr(&real_pattern, prefix);
	strbuf_addstr(&real_pattern, pattern);

	if (!has_glob_specials(pattern)) {
		/* Append implied '/' '*' if not present. */
		if (real_pattern.buf[real_pattern.len - 1] != '/')
			strbuf_addch(&real_pattern, '/');
		/* No need to check for '*', there is none. */
		strbuf_addch(&real_pattern, '*');
	}

	filter.pattern = real_pattern.buf;
	filter.fn = fn;
	filter.cb_data = cb_data;
	ret = for_each_ref(filter_refs, &filter);
