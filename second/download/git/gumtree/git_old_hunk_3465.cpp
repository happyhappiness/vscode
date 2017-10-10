#include "commit.h"
#include "tree.h"
#include "blob.h"

const char *tag_type = "tag";

struct object *deref_tag(struct object *o, const char *warn, int warnlen)
{
	while (o && o->type == OBJ_TAG)
		if (((struct tag *)o)->tagged)
			o = parse_object(((struct tag *)o)->tagged->oid.hash);
		else
