		struct ref_entry *entry = dir->entries[i];
		if (entry->flag & REF_DIR)
			prime_ref_dir(get_ref_dir(entry));
	}
}

/*
 * A level in the reference hierarchy that is currently being iterated
 * through.
 */
struct cache_ref_iterator_level {
	/*
	 * The ref_dir being iterated over at this level. The ref_dir
	 * is sorted before being stored here.
	 */
	struct ref_dir *dir;

	/*
	 * The index of the current entry within dir (which might
	 * itself be a directory). If index == -1, then the iteration
	 * hasn't yet begun. If index == dir->nr, then the iteration
	 * through this level is over.
	 */
	int index;
};

/*
 * Represent an iteration through a ref_dir in the memory cache. The
 * iteration recurses through subdirectories.
 */
struct cache_ref_iterator {
	struct ref_iterator base;

	/*
	 * The number of levels currently on the stack. This is always
	 * at least 1, because when it becomes zero the iteration is
	 * ended and this struct is freed.
	 */
	size_t levels_nr;

	/* The number of levels that have been allocated on the stack */
	size_t levels_alloc;

	/*
	 * A stack of levels. levels[0] is the uppermost level that is
	 * being iterated over in this iteration. (This is not
	 * necessary the top level in the references hierarchy. If we
	 * are iterating through a subtree, then levels[0] will hold
	 * the ref_dir for that subtree, and subsequent levels will go
	 * on from there.)
	 */
	struct cache_ref_iterator_level *levels;
};

static int cache_ref_iterator_advance(struct ref_iterator *ref_iterator)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;

	while (1) {
		struct cache_ref_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];
		struct ref_dir *dir = level->dir;
		struct ref_entry *entry;

		if (level->index == -1)
			sort_ref_dir(dir);

		if (++level->index == level->dir->nr) {
			/* This level is exhausted; pop up a level */
			if (--iter->levels_nr == 0)
				return ref_iterator_abort(ref_iterator);

			continue;
		}

		entry = dir->entries[level->index];

		if (entry->flag & REF_DIR) {
			/* push down a level */
			ALLOC_GROW(iter->levels, iter->levels_nr + 1,
				   iter->levels_alloc);

			level = &iter->levels[iter->levels_nr++];
			level->dir = get_ref_dir(entry);
			level->index = -1;
		} else {
			iter->base.refname = entry->name;
			iter->base.oid = &entry->u.value.oid;
			iter->base.flags = entry->flag;
			return ITER_OK;
		}
	}
}

static enum peel_status peel_entry(struct ref_entry *entry, int repeel);

static int cache_ref_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;
	struct cache_ref_iterator_level *level;
	struct ref_entry *entry;

	level = &iter->levels[iter->levels_nr - 1];

	if (level->index == -1)
		die("BUG: peel called before advance for cache iterator");

	entry = level->dir->entries[level->index];

	if (peel_entry(entry, 0))
		return -1;
	hashcpy(peeled->hash, entry->u.value.peeled.hash);
	return 0;
}

static int cache_ref_iterator_abort(struct ref_iterator *ref_iterator)
{
	struct cache_ref_iterator *iter =
		(struct cache_ref_iterator *)ref_iterator;

	free(iter->levels);
	base_ref_iterator_free(ref_iterator);
	return ITER_DONE;
}

static struct ref_iterator_vtable cache_ref_iterator_vtable = {
	cache_ref_iterator_advance,
	cache_ref_iterator_peel,
	cache_ref_iterator_abort
};

static struct ref_iterator *cache_ref_iterator_begin(struct ref_dir *dir)
{
	struct cache_ref_iterator *iter;
	struct ref_iterator *ref_iterator;
	struct cache_ref_iterator_level *level;

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;
	base_ref_iterator_init(ref_iterator, &cache_ref_iterator_vtable);
	ALLOC_GROW(iter->levels, 10, iter->levels_alloc);

	iter->levels_nr = 1;
	level = &iter->levels[0];
	level->index = -1;
	level->dir = dir;

	return ref_iterator;
}

struct nonmatching_ref_data {
	const struct string_list *skip;
	const char *conflicting_refname;
};

static int nonmatching_ref_fn(struct ref_entry *entry, void *vdata)
