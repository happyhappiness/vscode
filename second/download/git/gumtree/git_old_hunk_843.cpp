#define NO_THE_INDEX_COMPATIBILITY_MACROS
#include "cache.h"
#include "exec_cmd.h"
#include "attr.h"
#include "dir.h"
#include "utf8.h"

const char git_attr__true[] = "(builtin)true";
const char git_attr__false[] = "\0(builtin)false";
static const char git_attr__unknown[] = "(builtin)unknown";
#define ATTR__TRUE git_attr__true
#define ATTR__FALSE git_attr__false
#define ATTR__UNSET NULL
#define ATTR__UNKNOWN git_attr__unknown

/* This is a randomly chosen prime. */
#define HASHSIZE 257

#ifndef DEBUG_ATTR
#define DEBUG_ATTR 0
#endif

struct git_attr {
	struct git_attr *next;
	unsigned h;
	int attr_nr;
	int maybe_macro;
	int maybe_real;
	char name[FLEX_ARRAY];
};
static int attr_nr;
static int cannot_trust_maybe_real;

static struct git_attr_check *check_all_attr;
static struct git_attr *(git_attr_hash[HASHSIZE]);

char *git_attr_name(struct git_attr *attr)
{
	return attr->name;
}

static unsigned hash_name(const char *name, int namelen)
{
	unsigned val = 0, c;

	while (namelen--) {
		c = *name++;
		val = ((val << 7) | (val >> 22)) ^ c;
	}
	return val;
}

static int invalid_attr_name(const char *name, int namelen)
{
	/*
	 * Attribute name cannot begin with '-' and must consist of
	 * characters from [-A-Za-z0-9_.].
	 */
	if (namelen <= 0 || *name == '-')
		return -1;
	while (namelen--) {
		char ch = *name++;
		if (! (ch == '-' || ch == '.' || ch == '_' ||
		       ('0' <= ch && ch <= '9') ||
		       ('a' <= ch && ch <= 'z') ||
		       ('A' <= ch && ch <= 'Z')) )
			return -1;
	}
	return 0;
}

static struct git_attr *git_attr_internal(const char *name, int len)
{
	unsigned hval = hash_name(name, len);
	unsigned pos = hval % HASHSIZE;
	struct git_attr *a;

	for (a = git_attr_hash[pos]; a; a = a->next) {
		if (a->h == hval &&
		    !memcmp(a->name, name, len) && !a->name[len])
			return a;
	}

	if (invalid_attr_name(name, len))
		return NULL;

	FLEX_ALLOC_MEM(a, name, name, len);
	a->h = hval;
	a->next = git_attr_hash[pos];
	a->attr_nr = attr_nr++;
	a->maybe_macro = 0;
	a->maybe_real = 0;
	git_attr_hash[pos] = a;

	REALLOC_ARRAY(check_all_attr, attr_nr);
	check_all_attr[a->attr_nr].attr = a;
	check_all_attr[a->attr_nr].value = ATTR__UNKNOWN;
	return a;
}

struct git_attr *git_attr(const char *name)
{
	return git_attr_internal(name, strlen(name));
}

/* What does a matched pattern decide? */
struct attr_state {
	struct git_attr *attr;
	const char *setto;
};

struct pattern {
	const char *pattern;
	int patternlen;
