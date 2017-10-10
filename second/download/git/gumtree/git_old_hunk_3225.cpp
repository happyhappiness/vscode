#include "utf8.h"
#include "git-compat-util.h"
#include "version.h"

typedef enum { FIELD_STR, FIELD_ULONG, FIELD_TIME } cmp_type;

static struct {
	const char *name;
	cmp_type cmp_type;
} valid_atom[] = {
	{ "refname" },
	{ "objecttype" },
	{ "objectsize", FIELD_ULONG },
	{ "objectname" },
	{ "tree" },
	{ "parent" },
	{ "numparent", FIELD_ULONG },
	{ "object" },
	{ "type" },
	{ "tag" },
