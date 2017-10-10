#include "tag.h"
#include "blob.h"
#include "refs.h"

static unsigned char current_commit_sha1[20];

void walker_say(struct walker *walker, const char *fmt, const char *hex)
{
	if (walker->get_verbosely)
		fprintf(stderr, fmt, hex);
}

static void report_missing(const struct object *obj)
{
	fprintf(stderr, "Cannot obtain needed %s %s\n",
		obj->type ? typename(obj->type): "object",
