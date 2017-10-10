#include "../cache.h"
#include "../refs.h"
#include "refs-internal.h"
#include "ref-cache.h"
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

/*
 * Return true if refname, which has the specified oid and flags, can
 * be resolved to an object in the database. If the referred-to object
 * does not exist, emit a warning and return false.
 */
static int ref_resolves_to_object(const char *refname,
