#define NO_THE_INDEX_COMPATIBILITY_MACROS
#include "cache.h"
#include "exec_cmd.h"
#include "attr.h"
#include "dir.h"
#include "utf8.h"
#include "quote.h"
#include "thread-utils.h"

const char git_attr__true[] = "(builtin)true";
const char git_attr__false[] = "\0(builtin)false";
static const char git_attr__unknown[] = "(builtin)unknown";
#define ATTR__TRUE git_attr__true
#define ATTR__FALSE git_attr__false
#define ATTR__UNSET NULL
#define ATTR__UNKNOWN git_attr__unknown

#ifndef DEBUG_ATTR
#define DEBUG_ATTR 0
#endif

struct git_attr {
	int attr_nr; /* unique attribute number */
	char name[FLEX_ARRAY]; /* attribute name */
};

const char *git_attr_name(const struct git_attr *attr)
{
	return attr->name;
}

struct attr_hashmap {
	struct hashmap map;
#ifndef NO_PTHREADS
	pthread_mutex_t mutex;
#endif
};

static inline void hashmap_lock(struct attr_hashmap *map)
{
#ifndef NO_PTHREADS
	pthread_mutex_lock(&map->mutex);
#endif
}

static inline void hashmap_unlock(struct attr_hashmap *map)
{
#ifndef NO_PTHREADS
	pthread_mutex_unlock(&map->mutex);
#endif
}

/*
 * The global dictionary of all interned attributes.  This
 * is a singleton object which is shared between threads.
 * Access to this dictionary must be surrounded with a mutex.
 */
static struct attr_hashmap g_attr_hashmap;

/* The container for objects stored in "struct attr_hashmap" */
struct attr_hash_entry {
	struct hashmap_entry ent; /* must be the first member! */
	const char *key; /* the key; memory should be owned by value */
	size_t keylen; /* length of the key */
	void *value; /* the stored value */
};

/* attr_hashmap comparison function */
static int attr_hash_entry_cmp(const struct attr_hash_entry *a,
			       const struct attr_hash_entry *b,
			       void *unused)
{
	return (a->keylen != b->keylen) || strncmp(a->key, b->key, a->keylen);
}

/* Initialize an 'attr_hashmap' object */
static void attr_hashmap_init(struct attr_hashmap *map)
{
	hashmap_init(&map->map, (hashmap_cmp_fn) attr_hash_entry_cmp, 0);
}

/*
 * Retrieve the 'value' stored in a hashmap given the provided 'key'.
 * If there is no matching entry, return NULL.
 */
static void *attr_hashmap_get(struct attr_hashmap *map,
			      const char *key, size_t keylen)
{
	struct attr_hash_entry k;
	struct attr_hash_entry *e;

	if (!map->map.tablesize)
		attr_hashmap_init(map);

	hashmap_entry_init(&k, memhash(key, keylen));
	k.key = key;
	k.keylen = keylen;
	e = hashmap_get(&map->map, &k, NULL);

	return e ? e->value : NULL;
}

/* Add 'value' to a hashmap based on the provided 'key'. */
static void attr_hashmap_add(struct attr_hashmap *map,
			     const char *key, size_t keylen,
			     void *value)
{
	struct attr_hash_entry *e;

	if (!map->map.tablesize)
		attr_hashmap_init(map);

	e = xmalloc(sizeof(struct attr_hash_entry));
	hashmap_entry_init(e, memhash(key, keylen));
	e->key = key;
	e->keylen = keylen;
	e->value = value;

	hashmap_add(&map->map, e);
}

struct all_attrs_item {
	const struct git_attr *attr;
	const char *value;
	/*
	 * If 'macro' is non-NULL, indicates that 'attr' is a macro based on
	 * the current attribute stack and contains a pointer to the match_attr
	 * definition of the macro
	 */
	const struct match_attr *macro;
};

/*
 * Reallocate and reinitialize the array of all attributes (which is used in
 * the attribute collection process) in 'check' based on the global dictionary
 * of attributes.
 */
static void all_attrs_init(struct attr_hashmap *map, struct attr_check *check)
{
	int i;

	hashmap_lock(map);

	if (map->map.size < check->all_attrs_nr)
		die("BUG: interned attributes shouldn't be deleted");

	/*
	 * If the number of attributes in the global dictionary has increased
	 * (or this attr_check instance doesn't have an initialized all_attrs
	 * field), reallocate the provided attr_check instance's all_attrs
	 * field and fill each entry with its corresponding git_attr.
	 */
	if (map->map.size != check->all_attrs_nr) {
		struct attr_hash_entry *e;
		struct hashmap_iter iter;
		hashmap_iter_init(&map->map, &iter);

		REALLOC_ARRAY(check->all_attrs, map->map.size);
		check->all_attrs_nr = map->map.size;

		while ((e = hashmap_iter_next(&iter))) {
			const struct git_attr *a = e->value;
			check->all_attrs[a->attr_nr].attr = a;
		}
	}

	hashmap_unlock(map);

	/*
	 * Re-initialize every entry in check->all_attrs.
	 * This re-initialization can live outside of the locked region since
	 * the attribute dictionary is no longer being accessed.
	 */
	for (i = 0; i < check->all_attrs_nr; i++) {
		check->all_attrs[i].value = ATTR__UNKNOWN;
		check->all_attrs[i].macro = NULL;
	}
}

static int attr_name_valid(const char *name, size_t namelen)
{
	/*
	 * Attribute name cannot begin with '-' and must consist of
	 * characters from [-A-Za-z0-9_.].
	 */
	if (namelen <= 0 || *name == '-')
		return 0;
	while (namelen--) {
		char ch = *name++;
		if (! (ch == '-' || ch == '.' || ch == '_' ||
		       ('0' <= ch && ch <= '9') ||
		       ('a' <= ch && ch <= 'z') ||
		       ('A' <= ch && ch <= 'Z')) )
			return 0;
	}
	return 1;
}

static void report_invalid_attr(const char *name, size_t len,
				const char *src, int lineno)
{
	struct strbuf err = STRBUF_INIT;
	strbuf_addf(&err, _("%.*s is not a valid attribute name"),
		    (int) len, name);
	fprintf(stderr, "%s: %s:%d\n", err.buf, src, lineno);
	strbuf_release(&err);
}

/*
 * Given a 'name', lookup and return the corresponding attribute in the global
 * dictionary.  If no entry is found, create a new attribute and store it in
 * the dictionary.
 */
static const struct git_attr *git_attr_internal(const char *name, int namelen)
{
	struct git_attr *a;

	if (!attr_name_valid(name, namelen))
		return NULL;

	hashmap_lock(&g_attr_hashmap);

	a = attr_hashmap_get(&g_attr_hashmap, name, namelen);

	if (!a) {
		FLEX_ALLOC_MEM(a, name, name, namelen);
		a->attr_nr = g_attr_hashmap.map.size;

		attr_hashmap_add(&g_attr_hashmap, a->name, namelen, a);
		assert(a->attr_nr == (g_attr_hashmap.map.size - 1));
	}

	hashmap_unlock(&g_attr_hashmap);

	return a;
}

const struct git_attr *git_attr(const char *name)
{
	return git_attr_internal(name, strlen(name));
}

/* What does a matched pattern decide? */
struct attr_state {
	const struct git_attr *attr;
	const char *setto;
};

struct pattern {
	const char *pattern;
	int patternlen;
