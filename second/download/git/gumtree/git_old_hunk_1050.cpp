#include "../cache.h"
#include "../refs.h"
#include "refs-internal.h"
#include "../iterator.h"
#include "../dir-iterator.h"
#include "../lockfile.h"
#include "../object.h"
#include "../dir.h"

struct ref_lock {
	char *ref_name;
	struct lock_file *lk;
	struct object_id old_oid;
};

struct ref_entry;

/*
 * Information used (along with the information in ref_entry) to
 * describe a single cached reference.  This data structure only
 * occurs embedded in a union in struct ref_entry, and only when
 * (ref_entry->flag & REF_DIR) is zero.
 */
struct ref_value {
	/*
	 * The name of the object to which this reference resolves
	 * (which may be a tag object).  If REF_ISBROKEN, this is
	 * null.  If REF_ISSYMREF, then this is the name of the object
	 * referred to by the last reference in the symlink chain.
	 */
	struct object_id oid;

	/*
	 * If REF_KNOWS_PEELED, then this field holds the peeled value
	 * of this reference, or null if the reference is known not to
	 * be peelable.  See the documentation for peel_ref() for an
	 * exact definition of "peelable".
	 */
	struct object_id peeled;
};

struct files_ref_store;

/*
 * Information used (along with the information in ref_entry) to
 * describe a level in the hierarchy of references.  This data
 * structure only occurs embedded in a union in struct ref_entry, and
 * only when (ref_entry.flag & REF_DIR) is set.  In that case,
 * (ref_entry.flag & REF_INCOMPLETE) determines whether the references
 * in the directory have already been read:
 *
 *     (ref_entry.flag & REF_INCOMPLETE) unset -- a directory of loose
 *         or packed references, already read.
 *
 *     (ref_entry.flag & REF_INCOMPLETE) set -- a directory of loose
 *         references that hasn't been read yet (nor has any of its
 *         subdirectories).
 *
 * Entries within a directory are stored within a growable array of
 * pointers to ref_entries (entries, nr, alloc).  Entries 0 <= i <
 * sorted are sorted by their component name in strcmp() order and the
 * remaining entries are unsorted.
 *
 * Loose references are read lazily, one directory at a time.  When a
 * directory of loose references is read, then all of the references
 * in that directory are stored, and REF_INCOMPLETE stubs are created
 * for any subdirectories, but the subdirectories themselves are not
 * read.  The reading is triggered by get_ref_dir().
 */
struct ref_dir {
	int nr, alloc;

	/*
	 * Entries with index 0 <= i < sorted are sorted by name.  New
	 * entries are appended to the list unsorted, and are sorted
	 * only when required; thus we avoid the need to sort the list
	 * after the addition of every reference.
	 */
	int sorted;

	/* A pointer to the files_ref_store that contains this ref_dir. */
	struct files_ref_store *ref_store;

	struct ref_entry **entries;
};

/*
 * Bit values for ref_entry::flag.  REF_ISSYMREF=0x01,
 * REF_ISPACKED=0x02, REF_ISBROKEN=0x04 and REF_BAD_NAME=0x08 are
 * public values; see refs.h.
 */

/*
 * The field ref_entry->u.value.peeled of this value entry contains
 * the correct peeled value for the reference, which might be
 * null_sha1 if the reference is not a tag or if it is broken.
 */
#define REF_KNOWS_PEELED 0x10

/* ref_entry represents a directory of references */
#define REF_DIR 0x20

/*
 * Entry has not yet been read from disk (used only for REF_DIR
 * entries representing loose references)
 */
#define REF_INCOMPLETE 0x40

/*
 * A ref_entry represents either a reference or a "subdirectory" of
 * references.
 *
 * Each directory in the reference namespace is represented by a
 * ref_entry with (flags & REF_DIR) set and containing a subdir member
 * that holds the entries in that directory that have been read so
 * far.  If (flags & REF_INCOMPLETE) is set, then the directory and
 * its subdirectories haven't been read yet.  REF_INCOMPLETE is only
 * used for loose reference directories.
 *
 * References are represented by a ref_entry with (flags & REF_DIR)
 * unset and a value member that describes the reference's value.  The
 * flag member is at the ref_entry level, but it is also needed to
 * interpret the contents of the value field (in other words, a
 * ref_value object is not very much use without the enclosing
 * ref_entry).
 *
 * Reference names cannot end with slash and directories' names are
 * always stored with a trailing slash (except for the top-level
 * directory, which is always denoted by "").  This has two nice
 * consequences: (1) when the entries in each subdir are sorted
 * lexicographically by name (as they usually are), the references in
 * a whole tree can be generated in lexicographic order by traversing
 * the tree in left-to-right, depth-first order; (2) the names of
 * references and subdirectories cannot conflict, and therefore the
 * presence of an empty subdirectory does not block the creation of a
 * similarly-named reference.  (The fact that reference names with the
 * same leading components can conflict *with each other* is a
 * separate issue that is regulated by verify_refname_available().)
 *
 * Please note that the name field contains the fully-qualified
 * reference (or subdirectory) name.  Space could be saved by only
 * storing the relative names.  But that would require the full names
 * to be generated on the fly when iterating in do_for_each_ref(), and
 * would break callback functions, who have always been able to assume
 * that the name strings that they are passed will not be freed during
 * the iteration.
 */
struct ref_entry {
	unsigned char flag; /* ISSYMREF? ISPACKED? */
	union {
		struct ref_value value; /* if not (flags&REF_DIR) */
		struct ref_dir subdir; /* if (flags&REF_DIR) */
	} u;
	/*
	 * The full name of the reference (e.g., "refs/heads/master")
	 * or the full name of the directory with a trailing slash
	 * (e.g., "refs/heads/"):
	 */
	char name[FLEX_ARRAY];
};

static void read_loose_refs(const char *dirname, struct ref_dir *dir);
static int search_ref_dir(struct ref_dir *dir, const char *refname, size_t len);
static struct ref_entry *create_dir_entry(struct files_ref_store *ref_store,
					  const char *dirname, size_t len,
					  int incomplete);
static void add_entry_to_dir(struct ref_dir *dir, struct ref_entry *entry);

static struct ref_dir *get_ref_dir(struct ref_entry *entry)
{
	struct ref_dir *dir;
	assert(entry->flag & REF_DIR);
	dir = &entry->u.subdir;
	if (entry->flag & REF_INCOMPLETE) {
		read_loose_refs(entry->name, dir);

		/*
		 * Manually add refs/bisect, which, being
		 * per-worktree, might not appear in the directory
		 * listing for refs/ in the main repo.
		 */
		if (!strcmp(entry->name, "refs/")) {
			int pos = search_ref_dir(dir, "refs/bisect/", 12);
			if (pos < 0) {
				struct ref_entry *child_entry;
				child_entry = create_dir_entry(dir->ref_store,
							       "refs/bisect/",
							       12, 1);
				add_entry_to_dir(dir, child_entry);
				read_loose_refs("refs/bisect",
						&child_entry->u.subdir);
			}
		}
		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}

static struct ref_entry *create_ref_entry(const char *refname,
					  const unsigned char *sha1, int flag,
					  int check_name)
{
	struct ref_entry *ref;

	if (check_name &&
	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL))
		die("Reference has invalid format: '%s'", refname);
	FLEX_ALLOC_STR(ref, name, refname);
	hashcpy(ref->u.value.oid.hash, sha1);
	oidclr(&ref->u.value.peeled);
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
static struct ref_entry *create_dir_entry(struct files_ref_store *ref_store,
					  const char *dirname, size_t len,
					  int incomplete)
{
	struct ref_entry *direntry;
	FLEX_ALLOC_MEM(direntry, name, dirname, len);
	direntry->u.subdir.ref_store = ref_store;
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
		entry = create_dir_entry(dir->ref_store, subdirname, len, 0);
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

	QSORT(dir->entries, dir->nr, ref_entry_cmp);

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

/*
 * Return true if refname, which has the specified oid and flags, can
 * be resolved to an object in the database. If the referred-to object
 * does not exist, emit a warning and return false.
 */
static int ref_resolves_to_object(const char *refname,
